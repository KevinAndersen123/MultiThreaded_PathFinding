#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <thread>
#include <queue>
#include <functional>

class ThreadPool {
public:
	ThreadPool();
	~ThreadPool();
	void addTask(std::function<void()>);
private:
	std::vector<std::thread> m_threads;
	std::queue<std::function<void()>> m_tasks;
};
#endif // !THREAD_POOL_H

