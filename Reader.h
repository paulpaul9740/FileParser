#pragma once
#include <string>
class Reader {
public:
	Reader() {}
	virtual std::string read() = 0;
	virtual ~Reader() {}
};
