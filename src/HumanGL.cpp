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
uint32_t			fps;
uint32_t			lastFpsUpdate;
std::shared_ptr<GLObject> selectedObject;
std::shared_ptr<Animation> selectedAnimation;
std::vector<std::shared_ptr<Animation>> bobbyAnimations;
std::vector<std::shared_ptr<Animation>> skeletalAnimations;
UIManager ui;

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
		if (!skeletalAnimations.empty())
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
			assetManager.loadAsset<GLFont>("resources/fonts/Times-New-Roman-16.bff");
	#endif
}

void UpdateTimers(uint32_t& fpsCount)
{
	uint32_t newTime = SDL_GetTicks();
	timeSinceLastFrame = newTime - timeOfLastFrame;
	timeOfLastFrame = newTime;
	fpsCount++;
	if (newTime - lastFpsUpdate >= 1000)
	{
		lastFpsUpdate = newTime;
		fps = fpsCount;
		ui.elements[0]->texts[0].text = std::string("FPS: " + std::to_string(fps));
		fpsCount = 0;
	}
}

void RenderLoop(GLContext_SDL& context)
{
	//	Timers

	uint32_t	fpsCount = 0;

	timeSinceLastFrame = SDL_GetTicks();
	lastFpsUpdate = 0;
	timeOfLastFrame = 0;

	while (running)
	{
		UpdateTimers(fpsCount);

		SDL_GetGlobalMouseState(&events.mousePos.x, &events.mousePos.y);
		if (events.handle() == NRE_QUIT)
			break ;

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.render();
		if (renderBones == true)
			scene.renderBones();

		ui.update(events.mousePos, events.mouseState);
		ui.draw();

		context.swapWindow();
	}
}

void	Render(char* loadedObject, GLContext_SDL& context)
{
	AssetManager& assetManager = AssetManager::getInstance();

	//	Scene setup
	scene = Scene("Scene");

	scene.drawGrid = true;

	scene.setCameraSpeed(0.005f);

	std::shared_ptr<GLObject> obj =
		assetManager.getAsset<GLObject>(loadedObject);
	if (obj != nullptr)
		scene.addObject(obj);
	std::shared_ptr<GLObject> rock =
		assetManager.getAsset<GLObject>("resources/objects/Rock/rock.dae");
	if (rock != nullptr)
		scene.addObject(rock);
	scene.addObject(assetManager.getAssetByName<GLObject>("Bobby")); // Bobby

	//	Light

	std::shared_ptr<Light>	light1(new Light(LightType::Point));
	assetManager.addAsset(light1);
	light1->move(mft::vec3(0.0f, 3.0f, -5.0f));

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
	GLCallThrow(glBlendFunc, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//	Global variables init

	renderingMode = Bobby;
	renderBones = false;
	events = SDLEvents();
	running = true;

	InitResources(ac, av);
	InitBindings();
	InitUI();

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
