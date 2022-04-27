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

struct Armature
{
	std::string name;
	bool open;
	std::shared_ptr<Mesh> mesh;
	std::vector<Armature> children;
	Armature(): name(), open(false), mesh(), children()
	{}
	Armature(std::shared_ptr<Mesh> mesh)
		: name(mesh->getName()), open(true), mesh(mesh), children()
	{}
};

//	Set of essential global variables
extern mft::vec2i		screenSize;
extern RenderingMode	renderingMode;
extern bool 			renderBones;
extern SDLEvents		events;
extern bool				running;
extern bool				mustUpdateModelPannel;
extern Scene			scene;
extern uint32_t			timeSinceLastFrame;
extern uint32_t			timeOfLastFrame;
extern std::string		modelPath;
extern unsigned int		selectedBone;
extern uint32_t			fps;
extern uint32_t			lastFpsUpdate;
extern mft::vec3		selectedMeshRotation;
extern std::shared_ptr<GLObject> selectedObject;
extern std::shared_ptr<Mesh> selectedMesh;
extern std::shared_ptr<Animation> selectedAnimation;
extern std::vector<std::shared_ptr<Animation>> bobbyAnimations;
extern std::vector<std::shared_ptr<Animation>> skeletalAnimations;
extern Armature rootArmature;
extern UIManager ui;

#endif // !_HUMAN_GL_H_
