#include "FilesCheck.h"

void FilesCheck::checkDirectory(const std::filesystem::path& p, std::string file_type, int n)
{
	if (!std::filesystem::exists(p))
	{
		std::filesystem::create_directory(p);
		std::cout << "ERROR: " << p.filename() << " did not exist and now is empty\n";
		this->isOk = false;
	}

	if (this->isOk)
	{
		int file_count = 0;
		for (auto const& file : std::filesystem::directory_iterator(p))
		{
			if (file.path().extension() != file_type)
			{
				std::cout << "ERROR: wrong type of file in " << p.filename() << " directory\n";
				this->isOk = false;
			}
			else file_count++;
		}
		if (file_count < n && this->isOk)
		{
			std::cout << "ERROR: not enough files in" << p.filename() << " directory\n";
			this->isOk = false;
		}
	}
}

void FilesCheck::checkDirectories()
{
	std::filesystem::path curr = std::filesystem::current_path();
	this->checkDirectory(curr / "Textures", ".png", 6);
	this->checkDirectory(curr / "Fonts", ".ttf", 1);
}

void FilesCheck::checkHighscores()
{
	std::filesystem::path curr = std::filesystem::current_path();
	if (!std::filesystem::exists(curr / "highscores.txt"))
	{
		std::ofstream{ curr / "highscores.txt" };
	}

	std::ifstream ifs("highscores.txt");
	std::string line;
	const std::regex score_template("#[1-9]0? <[0-9]+>");
	
	if (ifs.is_open())
	{
		while (getline(ifs, line))
		{
			if (!std::regex_match(line, score_template))
			{
				std::cout << "ERROR: there is an error in file 'highscores.txt'\n";
				this->isOk = false;
				break;
			}
		}
	}

}

void FilesCheck::runCheck()
{
	this->checkDirectories();
	this->checkHighscores();
}

const bool FilesCheck::getIsOk() const
{
	return this->isOk;
}
