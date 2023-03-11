#ifndef SERVER_H
#define SERVER_H

#include <list>
#include <memory>

#include <boost/asio.hpp>

#include "WriterThread.h"
#include "ConcurrentQueue.h"
#include "Message.h"
#include "ConfigurationService.h"

namespace core
{
class ConfigurationService;
}

class Server
{
public:
	struct Session
	{
	public:
		Session(boost::asio::io_service& io_service,
				uint64_t unique_numerical_id);

		boost::asio::ip::tcp::socket socket;
		boost::asio::streambuf read_buffer;
		uint64_t unique_numerical_id;
	};

	~Server();

	static Server& instance();
	static void signal_handler(int sig_number);

	void init();
	void run();

private:
	Server();
	Server(const Server& other) = delete;
	Server(Server&& other) = default;

	Server& operator=(const Server& other) = delete;
	Server& operator=(Server&& other) = default;

	using SessionCollection = std::list<Session>;
	using SessionCollectionIterator = SessionCollection::iterator;

	bool listen();
	void start_accept();
	void handle_accept(SessionCollectionIterator session_iterator,
			boost::system::error_code const& err);
	void read_async(SessionCollectionIterator session_iterator);

	void handle_read(SessionCollectionIterator session_iterator,
			boost::system::error_code const& err, size_t bytes_transfered);
	void put_into_queue(SessionCollectionIterator session_iterator);

	void cleanup();

	core::ConfigurationService config_service;

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::acceptor acceptor;

	SessionCollection session_collection;

	uint64_t unique_numerical_id;

	std::unique_ptr<core::WriterThread> writer_thread;

	std::unique_ptr<moodycamel::ConcurrentQueue<Message>> concurrent_queue;
};

#endif
