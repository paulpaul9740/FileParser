#pragma once
#include "Reader.h"
class FileReader : public Reader
{
public:
	FileReader(const std::string& filename);
	std::string read() override;
	std::string getFileName() const;
private:
	std::string _filename;
};
