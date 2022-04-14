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

std::string	str = "Value = " + std::to_string(0);
int	value = 0;
int		updateText(void)
{
	value++;
	str = "Value = " + std::to_string(value);
	return 0;
}

using namespace notrealengine;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
# define PROJECT_DIR "./"
#else
# define PROJECT_DIR "./"
#endif

int		program(int ac, char** av, GLContext_SDL& context, SDLWindow& window)
{
	const char* glVersion = (char*)GLCallThrow(glGetString, GL_VERSION);
	std::cout << "GL Version: " << glVersion << std::endl;
	SDL_Event	e;
	int	running = 1;
	int	mode = Object;
	int selectedBone = 0;

	std::shared_ptr<GLObject>	obj = AssetManager::getInstance().loadAsset<GLObject>(av[1]);
	std::shared_ptr<Animation>	anim;
	if (ac == 3 && av[2][0] != '-')
		anim = AssetManager::getInstance().loadAsset<Animation>(av[2], 0);
	else if (ac >= 2)
		anim = AssetManager::getInstance().loadAsset<Animation>(av[1], 0);
	std::shared_ptr<GLObject>	rock = AssetManager::getInstance().loadAsset<GLObject>(PROJECT_DIR "resources/objects/Rock/rock.dae");
	std::shared_ptr<Animation> bobbyWalking = InitBobbyWalking();
	std::shared_ptr<Animation> bobbyJumping = InitBobbyJumping();
	std::shared_ptr<Animation> bobbyIdle = InitBobbyIdle();
	std::shared_ptr<Animation> bobbyAnim = bobbyIdle;
	std::shared_ptr<Light>	light1(new Light(LightType::Directional));
	light1->move(mft::vec3(0.0f, 4.0f, -5.0f));

	obj->transform.rotate(mft::quat::rotation(mft::vec3(0.0f, 1.0f, 0.0f), mft::radians(180.0f)));
	rock->transform.move(mft::vec3(5.0f, 0.0f, 5.0f));
	//obj->localTransform.move(mft::vec3(0.0f, -5.0f, 10.0f));
	//obj->setShader(context.getShader("color"));

	GLCallThrow(glEnable, GL_DEPTH_TEST);
	GLCallThrow(glEnable, GL_BLEND);
	//glEnable(GL_CULL_FACE);
	GLCallThrow(glBlendFunc, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::shared_ptr<GLObject>	bobby = InitBobby();


	//upperLeftArm.localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 0.2f));
	//head.localTransform.rotate(mft::quat::rotation(mft::vec3(mft::radians(90.0f), 0.0f, 0.0f));

	Scene	scene;
	scene.drawGrid = true;

#ifdef USING_EXTERNAL_LIBS
	std::shared_ptr<GLFont>	font = AssetManager::getInstance().loadAsset<GLFont>(PROJECT_DIR "resources/fonts/arial.ttf");
#else
	std::shared_ptr<GLFont>	font = AssetManager::getInstance().loadAsset<GLFont>(PROJECT_DIR "resources/fonts/pt-sans-48.bff");
#endif

	uint32_t	newTime = 0;
	uint32_t	fpsCount = 0;
	uint32_t	frameTime = 0;
	uint32_t	fps = 0;

	uint32_t	moveTime = 0;

	scene.setCameraSpeed(0.05f);

	scene.addObject(obj);
	scene.addObject(rock);
	scene.addObject(bobby);

	std::shared_ptr<Mesh> mesh(new Mesh(GLContext::cube));
	mesh->setName("Mesh");
	mesh->setColor(mft::vec3(0.9f, 0.9f, 0.9f));
	//mesh->localTransform.scale(mft::vec3(0.5f, 0.75f, 0.15f));
	mesh->addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
	mesh->getChildren()[0]->setColor(mft::vec3(0.9f, 0.5f, 0.9f));
	mesh->getChildren()[0]->localTransform.move(mft::vec3(0.75f, 0.2f, 0.0f));
	//mesh->getChildren()[0]->localTransform.scale(mft::vec3(0.35f, 0.475f, 1.0f));
	mesh->getChildren()[0]->setName("Mesh 2");
	mesh->getChildren()[0]->addMesh(std::shared_ptr<Mesh>(new Mesh(GLContext::cube)));
	mesh->getChildren()[0]->getChildren()[0]->localTransform.move(mft::vec3(0.0f, -1.0f, 0.0f));
	mesh->getChildren()[0]->getChildren()[0]->setName("Mesh 3");
	std::vector<std::shared_ptr<Mesh>> meshes;
	meshes.push_back(mesh);
	std::shared_ptr<GLObject>	object(new GLObject(meshes));
	object->setShader(GLContext::getShader("color"));

	scene.addObject(object);
	bobby->visible = false;
	obj->visible = true;
	object->visible = false;
	//rock->visble = false;
	//obj->setAnimation(anim.get());
	scene.addLight(light1);

	InputState	mouseState = InputState::NRE_RELEASED;

	vec2i	mousePos, mouseStart;

	int frame = 0;

	scene.setLightingMode(LightingMode::Unlit);

	//std::shared_ptr<Mesh> selectedMesh = object->getMeshes()[0];
	std::shared_ptr<Mesh> selectedMesh = bobby->getMeshes()[0];

	std::map<std::string, std::shared_ptr<Mesh>>::iterator bobbyMeshesIt =
		bobby->getMeshesMap().begin();

	UIManager	ui;
	Button		testButton(context.getShader("2d"));
	testButton.setPos(mft::vec2i(800, 450));
	testButton.setFont(font);
	testButton.setText("Coucou");
	testButton.setTextColor(mft::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	testButton.setReleaseFunc(updateText);
	int i = 0;
	std::shared_ptr<Button>		buttonPtr(new Button(testButton));
	Button		testButton2(context.getShader("2d"));
	testButton2.setFont(font);
	testButton2.setTextColor(mft::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	testButton2.setPos(mft::vec2i(800, 550));
	testButton2.setText(str);
	//testButton2.setText("Bouton de test");
	std::shared_ptr<Button>		buttonPtr2(new Button(testButton2));
	//UIElement	testUI(context.getShader("2d"));
	//testUI.setPos(mft::vec2(800, 450));
	//std::shared_ptr<UIElement>		uiPtr(new UIElement(testUI));
	ui.registerElement(buttonPtr);
	ui.registerElement(buttonPtr2);

	std::shared_ptr<Texture> texture = AssetManager::getInstance().loadAsset<Texture>(PROJECT_DIR "resources/objects/Graves Pool Party/graves_skin05_TX_CM.png", "UI");

	std::cout << "Asset manager content:" << std::endl;
	AssetManager::getInstance().printContent();

	while (running)
	{
		uint32_t	deltaTime = SDL_GetTicks() - moveTime;
		moveTime = SDL_GetTicks();
		if (mouseState == InputState::NRE_PRESS)
			mouseState = InputState::NRE_PRESSED;
		if (mouseState == InputState::NRE_RELEASE)
			mouseState = InputState::NRE_RELEASED;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		if (mouseState == InputState::NRE_PRESSED)
		{
			scene.setYaw(scene.getYaw() + (float)(mouseStart.x - mousePos.x) * scene.getCamera().sensitivity);
			scene.setPitch(scene.getPitch() - (float)(mouseStart.y - mousePos.y) * scene.getCamera().sensitivity);
			mouseStart = mousePos;
		}
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
			{
				running = 0;
				break;
			}
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					running = 0;
				}
				if (e.key.keysym.sym == SDLK_LEFT)
				{
					selectedMesh->localTransform.move(mft::vec3(-0.05f, 0.0f, 0.0f));
					std::cout << selectedMesh->getName() << ": pos = ";
					std::cout << selectedMesh->localTransform.getPos();
					std::cout << ", scale = " << selectedMesh->localTransform.getScale() << std::endl;
				}
				if (e.key.keysym.sym == SDLK_RIGHT)
				{
					selectedMesh->localTransform.move(mft::vec3(0.05f, 0.0f, 0.0f));
					std::cout << selectedMesh->getName() << ": pos = ";
					std::cout << selectedMesh->localTransform.getPos();
					std::cout << ", scale = " << selectedMesh->localTransform.getScale() << std::endl;
				}
				if (e.key.keysym.sym == SDLK_UP)
				{
					selectedMesh->localTransform.move(mft::vec3(0.0f, 0.05f, 0.0f));
					std::cout << selectedMesh->getName() << ": pos = ";
					std::cout << selectedMesh->localTransform.getPos();
					std::cout << ", scale = " << selectedMesh->localTransform.getScale() << std::endl;
				}
				if (e.key.keysym.sym == SDLK_DOWN)
				{
					selectedMesh->localTransform.move(mft::vec3(0.0f, -0.05f, 0.0f));
					std::cout << selectedMesh->getName() << ": pos = ";
					std::cout << selectedMesh->localTransform.getPos();
					std::cout << ", scale = " << selectedMesh->localTransform.getScale() << std::endl;
				}
				if (e.key.keysym.sym == SDLK_a)
				{
					scene.left(deltaTime / 2.0);
				}
				if (e.key.keysym.sym == SDLK_d)
				{
					scene.right(deltaTime / 2.0);
				}
				if (e.key.keysym.sym == SDLK_w)
				{
					scene.forward(deltaTime / 2.0);
				}
				if (e.key.keysym.sym == SDLK_s)
				{
					scene.backward(deltaTime / 2.0);
				}
				if (e.key.keysym.sym == SDLK_z)
				{
					if (scene.getDrawMode() != DrawMode::Wireframe)
						scene.setDrawMode(DrawMode::Wireframe);
					else
						scene.setDrawMode(DrawMode::Fill);
				}
				if (e.key.keysym.sym == SDLK_8)
				{
					//obj->localTransform.move(mft::vec3(-1.0f, 0.0f, 0.0f));
					//character->localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, -0.2f), mft::radians(90.0f)));
					selectedMesh->localTransform.scale(mft::vec3(1.05f, 1.0f, 1.0f));
					std::cout << selectedMesh->getName() << ": pos = ";
					std::cout << selectedMesh->localTransform.getPos();
					std::cout << ", scale = " << selectedMesh->localTransform.getScale() << std::endl;
				}
				if (e.key.keysym.sym == SDLK_6)
				{
					selectedMesh->localTransform.scale(mft::vec3(0.95f, 1.0f, 1.0f));
					std::cout << selectedMesh->getName() << ": pos = ";
					std::cout << selectedMesh->localTransform.getPos();
					std::cout << ", scale = " << selectedMesh->localTransform.getScale() << std::endl;
					//obj->localTransform.move(mft::vec3(1.0f, 0.0f, 0.0f));
					//character->localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.0f, 0.2f), mft::radians(90.0f)));
				}
				if (e.key.keysym.sym == SDLK_4)
				{
					selectedMesh->localTransform.scale(mft::vec3(1.0f, 1.05f, 1.0f));
					std::cout << selectedMesh->getName() << ": pos = ";
					std::cout << selectedMesh->localTransform.getPos();
					std::cout << ", scale = " << selectedMesh->localTransform.getScale() << std::endl;
					//obj->localTransform.move(mft::vec3(0.0f, 0.0f, 1.0f));
					//character->localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 0.2f, 0.0f), mft::radians(90.0f)));
				}
				if (e.key.keysym.sym == SDLK_2)
				{
					selectedMesh->localTransform.scale(mft::vec3(1.0f, 0.95f, 1.0f));
					std::cout << selectedMesh->getName() << ": pos = ";
					std::cout << selectedMesh->localTransform.getPos();
					std::cout << ", scale = " << selectedMesh->localTransform.getScale() << std::endl;
					//obj->localTransform.move(mft::vec3(0.0f, 0.0f, -1.0f));
					//character->localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, -0.2f, 0.0f), mft::radians(90.0f)));
				}
				if (e.key.keysym.sym == SDLK_KP_4)
				{
					selectedMesh->localTransform.rotate(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(10.0f)));
					std::cout << selectedMesh->getName() << ": rotation = ";
					std::cout << selectedMesh->localTransform.getRotation() << std::endl;
				}
				if (e.key.keysym.sym == SDLK_KP_6)
				{
					selectedMesh->localTransform.rotate(mft::quat::rotation(mft::vec3(1.0f, 0.0f, 0.0f), mft::radians(-10.0f)));
					std::cout << selectedMesh->getName() << ": rotation = ";
					std::cout << selectedMesh->localTransform.getRotation() << std::endl;
				}
				if (e.key.keysym.sym == SDLK_KP_8)
				{
					selectedMesh->localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 1.0f, 0.0f), mft::radians(10.0f)));
					std::cout << selectedMesh->getName() << ": rotation = ";
					std::cout << selectedMesh->localTransform.getRotation() << std::endl;
				}
				if (e.key.keysym.sym == SDLK_KP_2)
				{
					selectedMesh->localTransform.rotate(mft::quat::rotation(mft::vec3(0.0f, 1.0f, 0.0f), mft::radians(-10.0f)));
					std::cout << selectedMesh->getName() << ": rotation = ";
					std::cout << selectedMesh->localTransform.getRotation() << std::endl;
				}
				if (e.key.keysym.sym == SDLK_p)
				{
					std::shared_ptr<GLObject> object;
					std::shared_ptr<Animation> animation;
					if (mode == Object || mode == Bones)
					{
						object = obj;
						animation = anim;
					}
					else if (mode == Bob)
					{
						object = bobby;
						animation = bobbyAnim;
					}
					AnimationState animState = object->getAnimationState();
					if (animState == AnimationState::Stopped)
					{
						object->playAnimation(animation.get());
					}
					else if (animState == AnimationState::Playing)
					{
						object->pauseAnimation();
					}
					else if (animState == AnimationState::Paused)
					{
						object->resumeAnimation();
					}
				}
				if (e.key.keysym.sym == SDLK_l)
				{
					if (scene.getLightingMode() == LightingMode::Lit)
						scene.setLightingMode(LightingMode::Unlit);
					else
						scene.setLightingMode(LightingMode::Lit);
				}
				if (e.key.keysym.sym == SDLK_o)
				{
					mode = Object;
					if (scene.getLightingMode() == LightingMode::Lit)
						obj->setShader(context.getShader("default"));
					else
						obj->setShader(context.getShader("unlit"));
					obj->bindBones();
					obj->visible = true;
					rock->visible = true;
					bobby->visible = false;
				}
				if (e.key.keysym.sym == SDLK_v)
				{
					mode = Bones;
					obj->setShader(context.getShader("bonesInfluence"));
				}
				if (e.key.keysym.sym == SDLK_b)
				{
					mode = Bob;
					obj->visible = false;
					rock->visible = false;
					bobby->visible = true;
				}
				if (e.key.keysym.sym == SDLK_r)
				{
					if (mode == Object || mode == Bones)
						obj->resetPose();
					else if (mode == Bob)
						bobby->resetPose();
				}
				if (e.key.keysym.sym == SDLK_KP_PLUS)
				{
					selectedBone++;
					if (selectedBone > obj->getNbBones())
						selectedBone = 0;
					bindInt(context.getShader("bonesInfluence")->programID, "selectedBone", selectedBone);
					frame += 1;
					obj->setToKeyFrame(frame);
					if (bobbyAnim == bobbyIdle)
						bobbyAnim = bobbyWalking;
					else if (bobbyAnim == bobbyWalking)
						bobbyAnim = bobbyJumping;
					else if (bobbyAnim == bobbyJumping)
						bobbyAnim = bobbyIdle;
					bobby->setAnimation(bobbyAnim.get());
					if (selectedMesh == object->getMeshes()[0])
					{
						selectedMesh = selectedMesh->getChildren()[0];
					}
					else if (selectedMesh == object->getMeshes()[0]->getChildren()[0])
					{
						selectedMesh = selectedMesh->getChildren()[0];
					}
					else if (selectedMesh == object->getMeshes()[0]->getChildren()[0]->getChildren()[0])
					{
						selectedMesh = object->getMeshes()[0];
					}
					else if (selectedMesh->getName() == "Torso")
					{
						selectedMesh = bobby->getMeshes()[0]->getChildren()[0];
					}
					else if (selectedMesh->getName() == "Head")
					{
						selectedMesh = bobby->getMeshes()[0]->getChildren()[1];
					}
					else if (selectedMesh->getName() == "Upper left arm")
					{
						selectedMesh = bobby->getMeshes()[0]->getChildren()[1]->getChildren()[0];
					}
					else if (selectedMesh->getName() == "Lower left arm")
					{
						selectedMesh = bobby->getMeshes()[0]->getChildren()[2];
					}
					else if (selectedMesh->getName() == "Upper right arm")
					{
						selectedMesh = bobby->getMeshes()[0]->getChildren()[2]->getChildren()[0];
					}
					else if (selectedMesh->getName() == "Lower right arm")
					{
						selectedMesh = bobby->getMeshes()[0]->getChildren()[3];
					}
					else if (selectedMesh->getName() == "Left thigh")
					{
						selectedMesh = bobby->getMeshes()[0]->getChildren()[3]->getChildren()[0];
					}
					else if (selectedMesh->getName() == "Left calf")
					{
						selectedMesh = bobby->getMeshes()[0]->getChildren()[4];
					}
					else if (selectedMesh->getName() == "Right thigh")
					{
						selectedMesh = bobby->getMeshes()[0]->getChildren()[4]->getChildren()[0];
					}
					else if (selectedMesh->getName() == "Right calf")
					{
						selectedMesh = bobby->getMeshes()[0];
					}
					bobbyMeshesIt++;
					if (bobbyMeshesIt == bobby->getMeshesMap().end())
						bobbyMeshesIt = bobby->getMeshesMap().begin();
					//selectedMesh = bobbyMeshesIt->second;
				}
				if (e.key.keysym.sym == SDLK_KP_MINUS)
				{
					selectedBone--;
					if (selectedBone < 0)
						selectedBone = obj->getNbBones() - 1;
					bindInt(context.getShader("bonesInfluence")->programID, "selectedBone", selectedBone);
					frame -= 1;
					if (frame < 0)
						frame = 0;
					obj->setToKeyFrame(frame);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					if (mouseState == InputState::NRE_RELEASED)
					{
						mouseState = InputState::NRE_PRESS;
						mouseStart = mousePos;
						SDL_ShowCursor(SDL_DISABLE);
					}
				}
				else if (e.button.button == SDL_BUTTON_RIGHT)
				{

				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					if (mouseState == InputState::NRE_PRESSED)
					{
						mouseState = InputState::NRE_RELEASE;
						SDL_ShowCursor(SDL_ENABLE);
					}
				}
				else if (e.button.button == SDL_BUTTON_RIGHT)
				{

				}
				break;
			}
		}
		newTime = SDL_GetTicks();
		fpsCount++;
		if (newTime - frameTime >= 1000)
		{
			frameTime = newTime;
			fps = fpsCount;
			fpsCount = 0;
		}
		GLCallThrow(glClearColor, 0.2f, 0.2f, 0.2f, 1.0f);
		GLCallThrow(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::shared_ptr<GLObject> currentObj;
		if (mode == Bob)
			currentObj = bobby;
		else if (mode == Object || mode == Bones)
			currentObj = obj;

		buttonPtr2->setText(str);
		scene.render();
		scene.renderBones();
		ui.update(mousePos, mouseState);
		texture->draw(mft::vec2i(0, 600), mft::vec2i(1200, 0), 0.0f, mft::vec4(1.0f));
		font->RenderText("Anim time (ms) = " + std::to_string(currentObj->getCurrentTime()), mft::vec2i(10, 850), 0.5f, mft::vec4(1.0));
		font->RenderText("Anim speed = " + std::to_string(currentObj->animationSpeed), mft::vec2i(10, 800), 0.5f, mft::vec4(1.0));
		font->RenderText("Anim state: " + currentObj->getAnimationStateStr(), mft::vec2i(10, 750), 0.5f, mft::vec4(1.0));
		font->RenderText(std::to_string(fps), mft::vec2i(50, 50), 0.5f, mft::vec4(1.0));
		font->RenderText("Selected Mesh = " + selectedMesh->getName(), mft::vec2i(1200, 850), 0.5f, mft::vec4(1.0));
		font->RenderText("Current anim = " + bobbyAnim->getName(), mft::vec2i(1200, 800), 0.5f, mft::vec4(1.0));
		context.swapWindow();
	}
	AssetManager::getInstance().clear();
	return 0;
}

int		HumanGL2(int ac, char** av)
{
	if (ac < 2)
	{
		std::cout << "Not enough arguments" << std::endl;
		return 1;
	}

	std::cout << "Current directory = " << std::filesystem::current_path() << std::endl;

	bool shouldRunTests = true;
	for (int i = 1; i < ac; i++)
	{
		if (strcmp(av[i], "-noTests") == 0)
			shouldRunTests = false;
	}
	if (shouldRunTests == true)
		runTests(PROJECT_DIR "test/testList.txt");
	SDLWindow window("Not real engine", std::pair<int, int>(1600, 900));
	GLContext_SDL	context(window.getContext(), window.getWindow());
	context.makeCurrent();
	return program(ac, av, context, window);
}
