#include "NotRealEngine.hpp"
#include "mft/mft.hpp"
#include "InitBobby.hpp"

using namespace notrealengine;

enum RenderingMode
{
	Object,
	Bobby,
	Bones
};

RenderingMode renderingMode = Bobby;
bool 					renderBones = false;
SDLEvents			events;

//	Load/init all the wanted resources

void	InitResources(int ac, char **av)
{
	AssetManager& assetManager = AssetManager::getInstance();

	//	Objects

	std::shared_ptr<GLObject> bobby = InitBobby();

	std::shared_ptr<GLObject> obj =
		assetManager.loadAsset<GLObject>(av[1]);
	obj->transform.rotate(mft::quat::rotation(mft::vec3(0.0f, 1.0f, 0.0f), mft::radians(180.0f)));

	std::shared_ptr<GLObject> rock =
		assetManager.loadAsset<GLObject>("resources/objects/Rock/rock.dae");
	rock->transform.move(mft::vec3(5.0f, 0.0f, 5.0f));

	//	Animations

	std::shared_ptr<Animation> bobbyWalking = InitBobbyWalking();
	std::shared_ptr<Animation> bobbyJumping = InitBobbyJumping();
	std::shared_ptr<Animation> bobbyIdle = InitBobbyIdle();
	std::shared_ptr<Animation> bobbyAnim = bobbyIdle;

	std::shared_ptr<Animation>	anim;
	if (ac == 3)
		anim = assetManager.loadAsset<Animation>(av[2], 0);
	else if (ac >= 2)
		anim = assetManager.loadAsset<Animation>(av[1], 0);

	//	Light

	std::shared_ptr<Light>	light1(new Light(LightType::Directional));
	light1->move(mft::vec3(0.0f, 4.0f, -5.0f));

	//	Fonts

	#ifdef USING_EXTERNAL_LIBS
		std::shared_ptr<GLFont>	font =
			assetManager.loadAsset<GLFont>("resources/fonts/arial.ttf");
	#else
		std::shared_ptr<GLFont>	font =
			assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");
	#endif

	std::cout << "Asset manager content:" << std::endl;
	assetManager.printContent();

	return ;
}

void HandleInputs(int& running)
{
	events.handle();
}

void RenderLoop(Scene& scene, GLContext_SDL& context)
{
	int	running = 1;
	while (running)
	{
		HandleInputs(running);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.render();
		if (renderBones == true)
			scene.renderBones();

		context.swapWindow();
	}
}

void	Render(char* loadedObject, GLContext_SDL& context)
{
	AssetManager& assetManager = AssetManager::getInstance();
	//	Scene setup
	Scene scene;
	scene.drawGrid = true;

	scene.setCameraSpeed(0.05f);

	scene.addObject(assetManager.getAsset<GLObject>(loadedObject));
	scene.addObject(assetManager.getAsset<GLObject>("resources/objects/Rock/rock.dae"));
	//scene.addObject(bobby);

	//	Timers

	uint32_t	newTime = 0;
	uint32_t	fpsCount = 0;
	uint32_t	frameTime = 0;
	uint32_t	fps = 0;

	uint32_t	moveTime = 0;

	RenderLoop(scene, context);
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

	Render(av[1], context);

	AssetManager::getInstance().clear();

	return 0;
}
