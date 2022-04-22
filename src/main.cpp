#include "GLException.class.hpp"
#include "Object/AssetManager.class.hpp"
#include "HumanGL.hpp"
#include "SDL.h"

#include <iostream>

int		HumanGL(int ac, char **av);

int		main(int ac, char **av)
{
	if (ac < 2 || ac > 5)
	{
		std::cout << "Usage: humangl [OBJECT-FILE] [UP TO 3 ANIMATIONS]..." << std::endl;
		std::cout << "3D Engine demo for playing animation" << std::endl;
		return 1;
	}
	try
	{
		return HumanGL(ac, av);
	}
	catch (std::runtime_error& e)
	{
		std::cerr << "Runtime error: " << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "STD Exception: " << e.what() << std::endl;
	}
}
