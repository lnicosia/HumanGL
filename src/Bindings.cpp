#include "HumanGL.hpp"

//  Input functions

void Quit()
{
	running = 0;
}

void Left()
{
  scene.left(timeSinceLastFrame);
}

void Right()
{
  scene.right(timeSinceLastFrame);
}

void Forward()
{
  scene.forward(timeSinceLastFrame);
}

void Backward()
{
  scene.backward(timeSinceLastFrame);
}


//  Init

void InitBindings()
{

  //  Quit
	Binding b("Quit", SDLK_ESCAPE, 0, false);
	std::function<void()> func = Quit;
	b.onRelease = new Action(func);

	events.AddBinding(b);

  //  Left
  Binding b2("Left", SDLK_LEFT, SDLK_a, false);
  std::function<void()> func2 = Left;
  b2.whenPressed = new Action(func2);

  events.AddBinding(b2);

  //  Right
  Binding b3("Right", SDLK_RIGHT, SDLK_d, false);
  std::function<void()> func3 = Right;
  b3.whenPressed = new Action(func3);

  events.AddBinding(b3);

  //  Forward
  Binding b4("Forward", SDLK_UP, SDLK_w, false);
  std::function<void()> func4 = Forward;
  b4.whenPressed = new Action(func4);

  events.AddBinding(b4);

  //  Backward
  Binding b5("Backward", SDLK_DOWN, SDLK_s, false);
  std::function<void()> func5 = Backward;
  b5.whenPressed = new Action(func5);

  events.AddBinding(b5);
}
