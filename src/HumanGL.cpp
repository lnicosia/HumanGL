#include "NotRealEngine.hpp"
#include "mft/mft.hpp"
#include "InitBobby.hpp"
#include "Bindings.hpp"
#include "HumanGL.hpp"

using namespace notrealengine;

//	Set of essential global variables
RenderingMode renderingMode;
bool 					renderBones;
SDLEvents			events;
bool					running;
Scene					scene;
uint32_t			timeSinceLastFrame;
uint32_t			timeOfLastFrame;
char*					modelPath;
unsigned int	selectedBone;
std::shared_ptr<GLObject> selectedObject;
std::shared_ptr<Animation> selectedAnimation;
std::vector<std::shared_ptr<Animation>> bobbyAnimations;
std::vector<std::shared_ptr<Animation>> skeletalAnimations;

//	Load/init all the wanted resources

void	InitResources(int ac, char **av)
{
	AssetManager& assetManager = AssetManager::getInstance();

	//	Objects

	std::shared_ptr<GLObject> bobby = InitBobby();
	//bobby->visible = false;

	std::shared_ptr<GLObject> obj =
		assetManager.loadAsset<GLObject>(av[1]);

	//	Import animation given in the arguments
	std::vector<std::shared_ptr<Animation>> readAnimations;
	if (ac == 2)
	{
		readAnimations = LoadAnimations(av[1]);

	}
	else
	{
		for (int i = 1; i < ac; i++)
			readAnimations = LoadAnimations(av[i]);
	}
	//	Copy read animations into our global skeletal animations array
	skeletalAnimations.insert(skeletalAnimations.end(),
		readAnimations.begin(), readAnimations.end());
	selectedBone = 0;

	if (obj != nullptr)
	{
		obj->transform.rotate(mft::quat::rotation(mft::vec3(0.0f, 1.0f, 0.0f), mft::radians(180.0f)));
		obj->visible = false;
		obj->setAnimation(skeletalAnimations[0].get());
	}


	std::shared_ptr<GLObject> rock =
		assetManager.loadAsset<GLObject>("resources/objects/Rock/rock.dae");
	if (rock != nullptr)
	{
		rock->transform.move(mft::vec3(5.0f, 0.0f, 5.0f));
		rock->visible = false;
	}

	//	Animations

	std::shared_ptr<Animation> bobbyWalking = InitBobbyWalking();
	std::shared_ptr<Animation> bobbyJumping = InitBobbyJumping();
	std::shared_ptr<Animation> bobbyIdle = InitBobbyIdle();
	selectedAnimation = bobbyIdle;
	selectedObject = bobby;
	bobby->setAnimation(bobbyIdle.get());
	bobbyAnimations.push_back(bobbyIdle);
	bobbyAnimations.push_back(bobbyWalking);
	bobbyAnimations.push_back(bobbyJumping);

	//	Fonts

	#ifdef USING_EXTERNAL_LIBS
		std::shared_ptr<GLFont>	font =
			assetManager.loadAsset<GLFont>("resources/fonts/arial.ttf");
	#else
		std::shared_ptr<GLFont>	font =
			assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");
	#endif

}

void RenderLoop(GLContext_SDL& context)
{
	//	Timers

	uint32_t	newTime = 0;
	uint32_t	fpsCount = 0;
	uint32_t	frameTime = 0;
	uint32_t	fps = 0;

	uint32_t	moveTime = 0;

	timeSinceLastFrame = 0;
	timeOfLastFrame = SDL_GetTicks();

	while (running)
	{
		timeSinceLastFrame = SDL_GetTicks() - moveTime;
		timeOfLastFrame = SDL_GetTicks();

		SDL_GetGlobalMouseState(&events.mousePos.x, &events.mousePos.y);
		if (events.handle() == NRE_QUIT)
			break ;

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
	scene = Scene("Scene");

	scene.drawGrid = true;

	scene.setCameraSpeed(0.00005f);

	scene.addObject(assetManager.getAsset<GLObject>(loadedObject));
	scene.addObject(assetManager.getAsset<GLObject>("resources/objects/Rock/rock.dae"));
	scene.addObject(assetManager.getAssetByName<GLObject>("Bobby")); // Bobby

	//	Light

	std::shared_ptr<Light>	light1(new Light(LightType::Directional));
	assetManager.addAsset(light1);
	light1->move(mft::vec3(0.0f, 4.0f, -5.0f));

	scene.addLight(light1);
	scene.setLightingMode(LightingMode::Unlit);

	std::cout << "Asset manager content:" << std::endl;
	assetManager.printContent();

	RenderLoop(context);
}

void ReleasePointers()
{
	AssetManager::getInstance().clear();
	scene.clear();
	selectedObject.reset();
	selectedAnimation.reset();
	bobbyAnimations.clear();
	skeletalAnimations.clear();
}

int		LaunchHumanGL(int ac, char **av, SDLWindow& window, GLContext_SDL& context)
{
	modelPath = av[1];

	//	Write OpenGL version

	const char* glVersion = (char*)GLCallThrow(glGetString, GL_VERSION);
	std::cout << "GL Version: " << glVersion << std::endl;

	//	Enable some OpenGL params

	GLCallThrow(glEnable, GL_DEPTH_TEST);
	GLCallThrow(glEnable, GL_BLEND);
	//GLCallThrow(glEnable, GL_CULL_FACE);
	//GLCallThrow(glCullFace, GL_BACK);
	GLCallThrow(glBlendFunc, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//	Global variables init

	renderingMode = Bobby;
	renderBones = false;
	events = SDLEvents();
	running = true;

	InitResources(ac, av);
	InitBindings();

	Render(av[1], context);

	ReleasePointers();
	return 0;
}

int		HumanGL(int ac, char** av)
{

	SDLWindow window("HumanGL", std::pair<int, int>(1600, 900));
	GLContext_SDL context(window.getContext(), window.getWindow());
	context.makeCurrent();

	try
	{
		LaunchHumanGL(ac, av, window, context);
	}
	catch (notrealengine::GLException& e)
	{
		std::cerr << std::endl << "GL Exception: " << e.what() << std::endl;
		ReleasePointers();
		return -1;
	}
	catch (std::exception& e)
	{
		std::cerr << std::endl << "STD Exception: " << e.what() << std::endl;
		ReleasePointers();
		return -1;
	}
	return 0;
}
