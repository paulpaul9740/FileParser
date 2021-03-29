#include "Writer.h"
#include <iostream>
	Writer::Writer(const std::string& filename, std::queue<std::string>& outQueue, std::mutex& outMutex, std::condition_variable& cond) :
		_file{ filename,std::ios_base::out }, _outQueue{ outQueue }, _outMutex{ outMutex }, _cond{ cond }
	{
		if (not _file.is_open())
		{
			throw std::runtime_error("Can't open file " + filename);
		}
		std::cout << "Writer created" << std::endl;
	}
	void Writer::writeThread(bool &work)
	{

		while (work)
		{
			std::string data;
			std::unique_lock<std::mutex> lock{ _outMutex };
			_cond.wait(lock);
			
			while (not _outQueue.empty())
			{
				data = std::move(_outQueue.front());
				_outQueue.pop();
				lock.unlock();
				_file << data;
				lock.lock();
			}
		}
	}
	Writer::~Writer() {
		_file.close();
	}
