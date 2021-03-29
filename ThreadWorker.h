#pragma once
#include <string>
#include <queue>
#include <mutex>
class ThreadWorker
{
public:
	ThreadWorker(std::queue<std::string>& taskQueue, std::queue<std::string>& outQueue, std::mutex& taskMutex, std::mutex& outMutex, std::condition_variable& cond);
	void start();
private:
	std::queue<std::string>& _taskQueue;
	std::queue<std::string>& _outQueue;
	std::mutex& _taskMutex;
	std::mutex& _outMutex;
	std::condition_variable& _cond;
};

