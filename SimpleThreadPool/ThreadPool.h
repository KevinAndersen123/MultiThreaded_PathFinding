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
	//populates the threadpool based on the amount of threads you want in the pool
	ThreadPool();
	///clears the threaed pool
	~ThreadPool();
	std::vector<std::thread> m_threadPool;
	//Ads the task to queue of tasks
	void addTask(std::function<void()> t_task);
private:
	std::mutex m_taskMutex;
	std::queue<std::function<void()>> m_tasks;
	std::condition_variable m_taskCondition;

	bool m_terminatePool{ false };
	static void TaskWait(ThreadPool& t_threadpool);
};
#endif // !THREAD_POOL_H

