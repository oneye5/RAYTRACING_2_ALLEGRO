#include "programEntry.h"
#include <iostream>
int main()
{
	std::cout << "initialization \n";
	windowManager.initWindow();
 	windowManager.initRenderer();
	std::cout << "initialization done\n";
	windowManager.windowLoop();
}