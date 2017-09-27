#ifndef FILE_READER_H
#define FILE_READER_H

#include <iostream>
#include <fstream>

class FileReader {
private:
	std::ifstream file;
public:
	FileReader(const char* path) : file(std::ifstream(path)) {};
	~FileReader() { this->file.close(); }
	void read(std::string &output);
};

#endif
