#ifndef THREAD_H
#define THREAD_H

#include <thread>
#include <atomic>

namespace core
{
class Thread
{
public:
	Thread()
	: stopped(false)
	{}

	void start()
	{
		thread = std::thread([this]{this->run();});
	}

	void stop()
	{
		stopped = true;
	}

	void join()
	{
		thread.join();
	}

	virtual void run()  = 0;

protected:
	std::atomic<bool> stopped;
	std::thread thread;
};

}

#endif // THREAD_H
