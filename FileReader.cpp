#include "FileReader.h"
#include <iostream>
#include <fstream>
#include <unordered_set>
FileReader::FileReader(const std::string& filename) : _filename{ filename } {
}

std::string FileReader::read()
{
	std::ifstream file{ getFileName(), std::ios_base::in };

	if (not file.is_open())
	{
		std::cout << "Warning! Can't open input file " << getFileName() << std::endl;
		return "";
	}
	std::string content, result;
	std::unordered_set<unsigned char> delimiters;
	std::getline(file, content);
	// additionalSize:  ':'after filename, '/n' after filename , '\n'  after str if no delimiters found at all
	size_t additionalSize = 3;
	result.reserve(getFileName().size() + content.size() + additionalSize); // to prevent unnecessary copying.
	std::string delimiter;
	while (std::getline(file, delimiter))
	{
		if (delimiter.empty()) // empty lines handling
		{
			continue;
		}
		delimiters.emplace(delimiter[0]);
	}
	auto addToResult = [&result](const std::string::const_iterator& i1, const std::string::const_iterator& i2)
	{
		if (i1 != i2)
		{
			result.append(i1, i2);
			result.push_back('\n');
		}
	};
	auto subStringItStart = content.begin();
	result.append(getFileName() + ":\n");
	for (auto it = content.begin(); it != content.end(); ++it)
	{
		if (delimiters.find(*it) != delimiters.end())
		{
			addToResult(subStringItStart, it);
			subStringItStart = it;
			++subStringItStart;
		}
	}
	addToResult(subStringItStart, content.end()); // adding last part
	return result;
}
std::string FileReader::getFileName() const
{
	return _filename;
}