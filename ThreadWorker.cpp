#include "ThreadWorker.h"
#include "FileReader.h"
#pragma once
ThreadWorker::ThreadWorker(std::queue<std::string>& taskQueue, std::queue<std::string>& outQueue, std::mutex& taskMutex, std::mutex& outMutex, std::condition_variable& cond) :
		_taskQueue{ taskQueue }, _taskMutex{ taskMutex }, _outQueue{ outQueue }, _outMutex{ outMutex }, _cond{ cond }
	{
	}
	void ThreadWorker::start()
	{
		while (true) {
			std::string data;
			{
				std::lock_guard<std::mutex> lock{ _taskMutex };
				if (_taskQueue.empty())
				{
					return;
				}
				data = std::move(_taskQueue.front());
				_taskQueue.pop();
			}
			std::unique_ptr<Reader> reader = std::make_unique<FileReader>(data);
			auto content = reader->read();
			{
				std::lock_guard<std::mutex> lock{ _outMutex };
				_outQueue.push(content);
			}
			_cond.notify_one();
		}
	}


