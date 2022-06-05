
#include <ctime>
#include "Menu.h"
#include "FilesCheck.h"

int main()
{

	FilesCheck fc;

	fc.runCheck();

	if (fc.getIsOk())
	{

		srand(static_cast<unsigned>(time(0)));

		Menu menu;

		menu.run();

	}

	return 0;
}