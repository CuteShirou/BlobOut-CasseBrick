#include "pch.h"
#include "main.h"
#include "Window.h"

#include<iostream>


int main()
{
	Window window;

	window.createWindow(800, 600);
	while (true) {
		window.pollEvents();
		std::cout << "test" << std::endl;
	}




#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
