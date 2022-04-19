#ifndef _HUMAN_GL_H_
#define _HUMAN_GL_H_

#include "Inputs/SDLEvents.class.hpp"
#include "Object/Scene.class.hpp"

using namespace notrealengine;

enum RenderingMode
{
	Model,
	Bobby,
	BonesInfluence
};

//	Set of essential global variables
extern RenderingMode  renderingMode;
extern bool 				  renderBones;
extern SDLEvents			events;
extern bool					  running;
extern Scene          scene;
extern uint32_t       timeSinceLastFrame;
extern uint32_t       timeOfLastFrame;
extern char*					modelPath;
extern unsigned int		selectedBone;
extern uint32_t				fps;
extern uint32_t				lastFpsUpdate;
extern std::shared_ptr<GLObject> selectedObject;
extern std::shared_ptr<Animation> selectedAnimation;
extern std::vector<std::shared_ptr<Animation>> bobbyAnimations;
extern std::vector<std::shared_ptr<Animation>> skeletalAnimations;

#endif // !_HUMAN_GL_H_
