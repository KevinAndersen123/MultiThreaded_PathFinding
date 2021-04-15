#include "ThreadPool.h"

ThreadPool::ThreadPool() {
	int cores = std::thread::hardware_concurrency() - 1;
	for (int i = 0; i < cores; i++)
	{
		m_threads.push_back(std::thread());
		// Need to add a function thats listens for 
		// Tasks to be added to the queue
	}
}

ThreadPool::~ThreadPool() {}


void ThreadPool::addTask(std::function<void()> task) 
{
	m_tasks.push(task);
}