#include "FileReader.h"

void FileReader::read(std::string &output) {
	if (!this->file.is_open()) {
		std::cout << "Failed to open file" << std::endl;
		throw 1;
	}
	std::string line;
	while (std::getline(this->file, line)) {
		output += line + "\n";
	}

	this->file.close();
}

