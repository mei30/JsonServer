#ifndef WRITERTHREAD_H
#define WRITERTHREAD_H

#include <filesystem>

#include "Thread.h"


#include "Message.h"
#include "ConcurrentQueue.h"

namespace core
{
class WriterThread: public Thread
{
public:
	WriterThread(moodycamel::ConcurrentQueue<Message>& conncurrent_queue,
			std::filesystem::path path);

	WriterThread(const WriterThread& other) = delete;
	WriterThread(WriterThread&& other) = default;

	WriterThread& operator=(const WriterThread& other) = delete;
	WriterThread& operator=(WriterThread&& other) = default;

	~WriterThread();

	void run() override;

private:
	moodycamel::ConcurrentQueue<Message>& conncurrent_queue;
	std::filesystem::path path;
};

}

#endif // WRITERTHREAD_H
