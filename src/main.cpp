#include "GLException.class.hpp"

#include <iostream>

int		HumanGL(int ac, char **av);

int		main(int ac, char **av)
{
	try
	{
		HumanGL(ac, av);
	}
	catch (notrealengine::GLException& e)
	{
		std::cerr << std::endl << "GL Exception: " << e.what() << std::endl;
		return -1;
	}
	catch (std::exception& e)
	{
		std::cerr << std::endl << "STD Exception: " << e.what() << std::endl;
		return -1;
	}
	return 0;
}
