#include "WriterThread.h"

#include <iostream>
#include <fstream>

#include <boost/asio/streambuf.hpp>

using namespace core;

WriterThread::WriterThread(moodycamel::ConcurrentQueue<Message>& conncurrent_queue,
		std::filesystem::path path)
	: conncurrent_queue(conncurrent_queue)
	, path(path)
{
}

WriterThread::~WriterThread()
{
	printf("fffffffffffffffffffffffffffffffffffffffffff\n");
	std::filesystem::remove_all(path);
}

void WriterThread::run()
{
	while (true)
	{
		Message message;
		bool found = conncurrent_queue.try_dequeue(message);

		if (found)
		{
			std::cout << "Message Received: " << message.buffer;
			const std::string file_name = std::to_string(message.unique_numerical_id)
					+ ".json";
			std::fstream fs;
			fs.open (path/file_name, std::fstream::out | std::fstream::app);
			fs << message.buffer;

			fs.close();
		}
	}
}
