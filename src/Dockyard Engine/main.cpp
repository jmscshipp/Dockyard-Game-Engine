#include "Dockyard.h"

int CALLBACK WinMain(HINSTANCE , HINSTANCE ,  LPSTR , int)                  
{          
	// start the game
	try
	{
		Dockyard::Run();
	}
	catch (std::string exception)
	{
		Trace::out("%s", exception.c_str());
		return EXIT_FAILURE;
	}

	return 0;                                       
}

