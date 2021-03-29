#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <fstream>
#include <condition_variable>
class Writer
{
public:
	Writer(const std::string& filename, std::queue<std::string>& outQueue, std::mutex& outMutex, std::condition_variable& cond);
	void writeThread();
	~Writer();

private:
	std::mutex& _outMutex;
	std::queue<std::string>& _outQueue;
	std::ofstream _file;
	std::condition_variable& _cond;
};
