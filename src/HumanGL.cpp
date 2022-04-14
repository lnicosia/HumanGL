#include "SDL.h"
#include "mft/mft.hpp"
#include "notrealengine/notrealengine.hpp"
#include "Object/GLObject.class.hpp"
#include "Object/Animation.class.hpp"
#include "Object/AssetManager.class.hpp"
#include "Object/Light.class.hpp"
#include "Object/Scene.class.hpp"
#include "Object/InitBobby.hpp"
#include "ColladaParser/ColladaSceneBuilder.class.hpp"
#include "LXML/LXML.class.hpp"
#include "GLShaderProgram.class.hpp"
#include "TextRendering/GLFont.class.hpp"
#include "Camera.class.hpp"
#include "Inputs/SDLEvents.class.hpp"
#include "Tests/RunTests.hpp"
#include "UI/Button.class.hpp"
#include "UI/UIManager.class.hpp"
#include "UsingExternalLibs.hpp"
#include <vector>
#include <string.h>

enum RenderingMode
{
	Object,
	Bob,
	Bones
};

using namespace notrealengine;

int		program(int ac, char** av, GLContext_SDL& context, SDLWindow& window)
{
	return 0;
}

//	Load/init all the wanted resources

void	InitResources(int ac, char **av)
{
	//	Objects

	std::shared_ptr<GLObject> bobby = InitBobby();
	
	GLObject test = GLObject(av[1]);

	std::shared_ptr<GLObject> obj =
		AssetManager::getInstance().loadAsset<GLObject>(av[1]);
	obj->transform.rotate(mft::quat::rotation(mft::vec3(0.0f, 1.0f, 0.0f), mft::radians(180.0f)));
	
	std::shared_ptr<GLObject> rock =
		AssetManager::getInstance().loadAsset<GLObject>("resources/objects/Rock/rock.dae");
	rock->transform.move(mft::vec3(5.0f, 0.0f, 5.0f));

	//	Animations

	std::shared_ptr<Animation> bobbyWalking = InitBobbyWalking();
	std::shared_ptr<Animation> bobbyJumping = InitBobbyJumping();
	std::shared_ptr<Animation> bobbyIdle = InitBobbyIdle();
	std::shared_ptr<Animation> bobbyAnim = bobbyIdle;

	std::shared_ptr<Animation>	anim;
	if (ac == 3)
		anim = AssetManager::getInstance().loadAsset<Animation>(av[2], 0);
	else if (ac >= 2)
		anim = AssetManager::getInstance().loadAsset<Animation>(av[1], 0);

	//	Light

	std::shared_ptr<Light>	light1(new Light(LightType::Directional));
	light1->move(mft::vec3(0.0f, 4.0f, -5.0f));

	return ;
}

int		HumanGL(int ac, char** av)
{
	
	SDLWindow window("HumanGL", std::pair<int, int>(1600, 900));
	GLContext_SDL context(window.getContext(), window.getWindow());
	context.makeCurrent();
	
	//	Write OpenGL version

	const char* glVersion = (char*)GLCallThrow(glGetString, GL_VERSION);
	std::cout << "GL Version: " << glVersion << std::endl;

	//	Enable some OpenGL params

	GLCallThrow(glEnable, GL_DEPTH_TEST);
	GLCallThrow(glEnable, GL_BLEND);
	GLCallThrow(glEnable, GL_CULL_FACE);
	GLCallThrow(glBlendFunc, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	

	InitResources(ac, av);

	

	//Render
	//RenderScene();
	//RenderUI();

	AssetManager::getInstance().clear();

	return 0;
}
