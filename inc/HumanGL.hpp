#ifndef _HUMAN_GL_H_
#define _HUMAN_GL_H_

#include "Inputs/SDLEvents.class.hpp"

using namespace notrealengine;

enum RenderingMode
{
	Object,
	Bobby,
	Bones
};

extern RenderingMode renderingMode;
extern bool 					renderBones;
extern SDLEvents			events;
extern bool					running;

#endif // !_HUMAN_GL_H_
