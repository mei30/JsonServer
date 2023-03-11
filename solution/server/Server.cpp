#include "Server.h"

#include <iostream>
#include <sstream>
#include <csignal>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "ConfigurationService.h"
#include "Logger.h"

using core::CPlusPlusLogging::Logger;

using namespace boost::asio;

Server::Session::Session(boost::asio::io_service& io_service,
				uint64_t unique_numerical_id)
	: socket(io_service)
	, read_buffer()
	, unique_numerical_id(unique_numerical_id)
{
}

Server::Server()
	: io_service()
	, acceptor(io_service)
	, unique_numerical_id(0)
{
	signal(SIGINT, Server::signal_handler);
}

Server::~Server()
{
	writer_thread->join();
}

Server& Server::instance()
{
	static Server server;
	return server;
}

void Server::signal_handler(int sig_number)
{
	instance().cleanup();

	std::exit(sig_number);
}

void Server::cleanup()
{
	writer_thread->join();
}

void Server::init()
{
	config_service.read("configuration.proto");

	concurrent_queue.reset(new moodycamel::ConcurrentQueue<Message>(
			config_service.get_writer_configuration().get_queue_size()));
	writer_thread.reset(new core::WriterThread(*concurrent_queue,
			config_service.get_writer_configuration().get_path()));

	listen();

	writer_thread->start();
}

bool Server::listen()
{
	auto endpoint = ::ip::tcp::endpoint(boost::asio::ip::address::from_string(
			config_service.get_server_configuration().get_server_address()),
			config_service.get_server_configuration().get_server_port());

	try
	{
		acceptor.open(endpoint.protocol());
		acceptor.set_option(ip::tcp::acceptor::reuse_address(true));
		acceptor.bind(endpoint);
		acceptor.listen();
	}
	catch(...)
	{
		LOG_ERROR("Server::listen: Server couldn't start listening");
		return false;
	}

	std::ostringstream os;
	os << "Server::listen: Server start listening on ";
	os << config_service.get_server_configuration().get_server_address() << " and ";
	os << config_service.get_server_configuration().get_server_port();

	LOG_INFO(os);

	start_accept();

	return true;
}

void Server::run()
{
	io_service.run();
}

void Server::start_accept()
{
	auto session_iterator = session_collection.emplace( session_collection.begin( ),
			io_service, unique_numerical_id++);
	auto handler = boost::bind(&Server::handle_accept, this, session_iterator,
			boost::asio::placeholders::error);
	acceptor.async_accept(session_iterator->socket, handler);
}

void Server::handle_accept(SessionCollectionIterator session_iterator,
			boost::system::error_code const& err)
{
	std::ostringstream os;
	if(!err)
	{
		os << "New connection from: "
				<< session_iterator->socket.remote_endpoint().address().to_string() << "\n";
		LOG_INFO(os);

		read_async(session_iterator);
	}
	else
	{
		os << "Error on incomming connections: " << err.message() << "\n";

		LOG_ERROR(os);

		session_collection.erase(session_iterator);
	}

	start_accept();
}

void Server::read_async(SessionCollectionIterator session_iterator) {
		auto handler = boost::bind(&Server::handle_read, this, session_iterator,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred);
		boost::asio::async_read(session_iterator->socket, session_iterator->read_buffer,
				handler);
	}

void Server::handle_read(SessionCollectionIterator session_iterator,
		boost::system::error_code const& err, size_t bytes_transfered)
{
		if(bytes_transfered > 0)
			put_into_queue(session_iterator);

		if(!err)
			read_async(session_iterator);
		else
		{
			if (err != boost::asio::error::eof)
			{
				std::ostringstream os;
				os << "Error on Reading connection request: " << err.message() << "\n";

				LOG_ERROR(os);

				return;
			}

			// TODO: Validate data

			session_collection.erase(session_iterator);
		}
}

void Server::put_into_queue(SessionCollectionIterator session_iterator)
{
	Message message{{buffers_begin(session_iterator->read_buffer.data()),
			buffers_end(session_iterator->read_buffer.data())},
			session_iterator->unique_numerical_id};

	concurrent_queue->try_enqueue(message);
}
