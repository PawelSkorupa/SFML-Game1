#pragma once

#include <iostream>
#include <filesystem>
#include <regex>
#include <string>
#include <fstream>

class FilesCheck
{
private:
	bool isOk = true;

	void checkDirectory(const std::filesystem::path& p, std::string file_type, int n);
	void checkDirectories();
	void checkHighscores();
public:
	void runCheck();

	const bool getIsOk() const;
};

