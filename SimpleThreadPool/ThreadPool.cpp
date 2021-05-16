#include "ThreadPool.h"

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
		{
			std::unique_lock<std::mutex> lock(t_threadpool.m_taskMutex);
			t_threadpool.m_taskCondition.wait(lock, [&] {return !t_threadpool.m_tasks.empty() || t_threadpool.m_terminatePool; });
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
