#include "HumanGL.hpp"

//  Input functions

void Quit()
{
	running = 0;
}

void InitBindings()
{
	Binding b("Quit", SDLK_ESCAPE, 0, false);
	std::function<void()> func = Quit;
	b.onRelease = new Action(func);

	events.AddBinding(b);
}
