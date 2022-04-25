#ifndef _HUMAN_GL_H_
#define _HUMAN_GL_H_

#include "Inputs/SDLEvents.class.hpp"
#include "Object/Scene.class.hpp"
#include "UI/UIManager.class.hpp"

using namespace notrealengine;

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

enum RenderingMode
{
	Model,
	Bobby,
	BonesInfluence
};

//	Set of essential global variables
extern mft::vec2i screenSize;
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
extern mft::vec3			selectedMeshRotation;
extern std::shared_ptr<GLObject> selectedObject;
extern std::shared_ptr<Mesh> selectedMesh;
extern std::shared_ptr<Animation> selectedAnimation;
extern std::vector<std::shared_ptr<Animation>> bobbyAnimations;
extern std::vector<std::shared_ptr<Animation>> skeletalAnimations;
extern UIManager ui;

/**	Init all the UI
*/
void InitUI( void );

/**	Update the model pannel hierarchical view with the current object
*/
void UpdateModelPannel( void );

/**	Update the transform pannel printed data
*/
void UpdateTransformPannel( void );

/**	Update the color pannel printed data
*/
void UpdateColorPannel( void );

#endif // !_HUMAN_GL_H_
