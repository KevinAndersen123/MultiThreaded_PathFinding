#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
#include <queue>
#include <mutex>
#include <functional>
#include <vector>
#include <memory>
#include <condition_variable>

class ThreadPool {
public:
	ThreadPool();
	~ThreadPool();
	std::vector<std::thread> m_threadPool;
	void addTask(std::function<void()> t_task);
private:
	std::mutex m_taskMutex;
	std::queue<std::function<void()>> m_tasks;
	std::condition_variable m_taskCondition;

	bool m_terminatePool{ false };
	static void infiniteSpin(ThreadPool& t_threadpool);
};
#endif // !THREAD_POOL_H

