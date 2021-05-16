#include "ThreadPool.h"
/// <summary>
/// For an efficient threadpool implementation, once threads are created, 
/// it's better not to create new ones, or destroy old ones (by joining).
///  There will be performance penalty, might even make your application goes slower than the serial version.
///
///Each C++11 thread should be running in their function with an infinite loop, constantly waiting for new tasks to grab and run.
/// </summary>

ThreadPool::ThreadPool() 
{
	int threads = 4;

	for (int i = 0; i < threads; i++)
	{
		m_threadPool.push_back(std::thread(TaskWait, std::ref(*this)));
	}
}

ThreadPool::~ThreadPool() 
{
	m_terminatePool = true; 
	m_taskCondition.notify_all();
	for (std::thread& every_thread : m_threadPool)
	{
		every_thread.join();
	}

	m_threadPool.clear();
}


void ThreadPool::addTask(std::function<void()> t_task)
{
	{
		std::unique_lock<std::mutex> lock(m_taskMutex);
		m_tasks.push(t_task);
	}
	m_taskCondition.notify_all();
}

void ThreadPool::TaskWait(ThreadPool& t_threadpool)
{
	while (true)
	{
		std::function<void()> task = std::function<void()>();
		bool receivedTask = false;
		//seperate scope to not block other threads on the pool
		{
			std::unique_lock<std::mutex> lock(t_threadpool.m_taskMutex);
			t_threadpool.m_taskCondition.wait(lock, [&] {return !t_threadpool.m_tasks.empty() || t_threadpool.m_terminatePool; });
			//if task queue is not empty, and the pool is not terminated. do the task
			if (!t_threadpool.m_terminatePool && !t_threadpool.m_tasks.empty())
			{
				task = t_threadpool.m_tasks.front();
				t_threadpool.m_tasks.pop();
				receivedTask = true;
			}
		}
		if (receivedTask)
		{
			task();
		}
	}
}
