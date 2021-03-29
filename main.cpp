#include "Writer.h"
#include "FileReader.h"
#include "ThreadWorker.h"
#include <filesystem>
#include <iostream>
#include <thread>
namespace fs = std::filesystem;
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "Usage: appname pathToInputDirs outputFile" << std::endl;
		exit(1);
	}
	std::string dirs{ argv[1] }, outFileName{ argv[2] };
	std::vector<std::thread> threadPool;
	int threadCount = std::thread::hardware_concurrency() == 0 ? 4 : std::thread::hardware_concurrency();
	std::queue<std::string> outQueue, taskQueue;
	std::mutex taskMutex, outMutex;
	std::condition_variable cond;
	std::cout << "Creating tasks...";
	for (const auto & entry : fs::directory_iterator(dirs))
	{
		taskQueue.push(entry.path().string());
	}
	std::cout << "Done!" << std::endl;
	Writer writer{ outFileName, outQueue, outMutex, cond };
	std::thread writerThread{ &Writer::writeThread, &writer };
	ThreadWorker worker{ taskQueue, outQueue, taskMutex, outMutex, cond};
	std::cout << "Creating worker threads, threadCount = " << threadCount << std::endl;
	for (int i = 0 ; i < threadCount; ++i)
	{
		threadPool.push_back(std::thread{ &ThreadWorker::start, &worker });
	}
	std::cout << "Workers are running..." << std::endl;
	for (auto it = threadPool.begin(); it != threadPool.end(); ++it)
	{
		it->join();
	}
	std::cout << "Workers stopped" << std::endl;
	writerThread.join();
	std::cout << "Writer stopped, check the " <<outFileName << " for results." << std::endl;
	return 0;
}
