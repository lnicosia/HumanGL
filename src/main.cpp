#include "GLException.class.hpp"
#include "Object/AssetManager.class.hpp"
#include "HumanGL.hpp"
#include "SDL.h"

#include <iostream>

int		HumanGL(int ac, char **av);

int		main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout << "Usage: humangl [OBJECT-FILE] [ANIMATION]..." << std::endl;
		std::cout << "3D Engine demo for playing animation" << std::endl;
		return 1;
	}
	return HumanGL(ac, av);
}
