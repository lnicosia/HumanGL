#include "HumanGL.hpp"
#include "Object/AssetManager.class.hpp"
#include "GLContext.class.hpp"

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

void LeftClickPress(mft::vec2i& mouseStart)
{
	//	Check UI

	//	If not on UI, move camera

	mouseStart = events.mousePos;
	SDL_ShowCursor(SDL_DISABLE);
}

void LeftClickPressed(mft::vec2i& mouseStart)
{
	//	Check UI

	//	If not on UI, move camera

	scene.setYaw(scene.getYaw()
		+ (float)(mouseStart.x - events.mousePos.x) * scene.getCamera().sensitivity);
	scene.setPitch(scene.getPitch()
		- (float)(mouseStart.y - events.mousePos.y) * scene.getCamera().sensitivity);
	mouseStart = events.mousePos;

}

void LeftClickRelease()
{
	//	Check UI

	//	If not on UI, move camera

	SDL_ShowCursor(SDL_ENABLE);
}

void ChangeDrawMode()
{
	if (scene.getDrawMode() != DrawMode::Wireframe)
		scene.setDrawMode(DrawMode::Wireframe);
	else
		scene.setDrawMode(DrawMode::Fill);
}

void PlayAnimation()
{
	if (selectedObject == nullptr)
		return ;
	AnimationState animState = selectedObject->getAnimationState();
	if (animState == AnimationState::Stopped)
	{
		selectedObject->playAnimation(selectedAnimation.get());
	}
	else if (animState == AnimationState::Playing)
	{
		selectedObject->pauseAnimation();
	}
	else if (animState == AnimationState::Paused)
	{
		selectedObject->resumeAnimation();
	}
}

void RenderBobby()
{
	renderingMode = Bobby;

	AssetManager& assetManager = AssetManager::getInstance();
	selectedObject = assetManager.getAssetByName<GLObject>("Bobby");
	selectedAnimation = bobbyAnimations[0];

	std::vector<std::shared_ptr<GLObject>> objects =
		assetManager.getAssetsOfType<GLObject>();

	for (auto& object: objects)
	{
		object->visible = false;
	}
	selectedObject->visible = true;
}

void SelectModel()
{
	AssetManager& assetManager = AssetManager::getInstance();
	selectedObject = assetManager.getAsset<GLObject>(modelPath);
	if (skeletalAnimations.empty())
		selectedAnimation = nullptr;
	else
		selectedAnimation = skeletalAnimations[0];

	std::vector<std::shared_ptr<GLObject>> objects =
		assetManager.getAssetsOfType<GLObject>();

	assetManager.getAssetByName<GLObject>("Bobby")->visible = false;
	std::shared_ptr<GLObject> rock =
		assetManager.getAsset<GLObject>("resources/objects/Rock/rock.dae");
	if (rock != nullptr)
		rock->visible = true;
	if (selectedObject != nullptr)
		selectedObject->visible = true;
}

void RenderModel()
{
	SelectModel();
	renderingMode = Model;
	if (selectedObject == nullptr)
		return ;
	if (scene.getLightingMode() == LightingMode::Lit)
		selectedObject->setShader(GLContext::getShader("default"));
	else
		selectedObject->setShader(GLContext::getShader("unlit"));
	selectedObject->bindBones();
}

void RenderBonesInfluence()
{
	SelectModel();
	renderingMode = BonesInfluence;
	if (selectedObject == nullptr)
		return ;
	selectedObject->setShader(GLContext::getShader("bonesInfluence"));
}

void NextAnim()
{
	std::vector<std::shared_ptr<Animation>> animations;
	if (renderingMode == Bobby)
	{
		animations = bobbyAnimations;
	}
	else if (renderingMode == Model || renderingMode == BonesInfluence)
	{
		animations = skeletalAnimations;
	}
	if (!animations.empty())
	{
		for (size_t i = 0; i < animations.size(); i++)
		{
			if (selectedAnimation == animations[i])
			{
				if (i == animations.size() - 1)
					selectedAnimation = animations[0];
				else
					selectedAnimation = animations[i + 1];
				break ;
			}
		}
	}
	else
		selectedAnimation = nullptr;
	if (selectedObject != nullptr && selectedAnimation != nullptr)
		selectedObject->setAnimation(selectedAnimation.get());
}

void Next()
{
	if (renderingMode == BonesInfluence)
	{

	}
	else
		NextAnim();
}

void PreviousAnim()
{
	std::vector<std::shared_ptr<Animation>> animations;
	if (renderingMode == Bobby)
	{
		animations = bobbyAnimations;
	}
	else if (renderingMode == Model || renderingMode == BonesInfluence)
	{
		animations = skeletalAnimations;
	}
	if (!animations.empty())
	{
		for (size_t i = 0; i < animations.size(); i++)
		{
			if (selectedAnimation == animations[i])
			{
				if (i == 0)
					selectedAnimation = animations.back();
				else
					selectedAnimation = animations[i - 1];
				break ;
			}
		}
	}
	else
		selectedAnimation = nullptr;
	if (selectedObject != nullptr && selectedAnimation != nullptr)
		selectedObject->setAnimation(selectedAnimation.get());
}

void Previous()
{
	if (renderingMode == BonesInfluence)
	{

	}
	else
		PreviousAnim();
}

void ChangeLightingMode()
{
	if (scene.getLightingMode() == LightingMode::Lit)
		scene.setLightingMode(LightingMode::Unlit);
	else
		scene.setLightingMode(LightingMode::Lit);
}

void ResetObjectPose()
{
	if (selectedObject != nullptr)
		selectedObject->resetPose();
}

//  Init

void InitBindings()
{

  //  Quit
	Binding b("Quit", SDLK_ESCAPE, 0, false);
	std::function<void()> func = Quit;
	b.onRelease = new Action(func);

	events.bindings.push_back(b);

  //  Left
  Binding b2("Left", SDLK_LEFT, SDLK_a, false);
  std::function<void()> func2 = Left;
  b2.whenPressed = new Action(func2);

  events.bindings.push_back(b2);

  //  Right
  Binding b3("Right", SDLK_RIGHT, SDLK_d, false);
  std::function<void()> func3 = Right;
  b3.whenPressed = new Action(func3);

  events.bindings.push_back(b3);

  //  Forward
  Binding b4("Forward", SDLK_UP, SDLK_w, false);
  std::function<void()> func4 = Forward;
  b4.whenPressed = new Action(func4);

  events.bindings.push_back(b4);

  //  Backward
  Binding b5("Backward", SDLK_DOWN, SDLK_s, false);
  std::function<void()> func5 = Backward;
  b5.whenPressed = new Action(func5);

  events.bindings.push_back(b5);

	//	Mouse
  MouseBinding b6("Mouse left", SDL_BUTTON_LEFT, 0, false);
	std::function<void(mft::vec2i&)> func6 = LeftClickPress;
  b6.onPress = new Action<mft::vec2i&>(func6, b6.start);
  std::function<void(mft::vec2i&)> func7 = LeftClickPressed;
  b6.whenPressed = new Action<mft::vec2i&>(func7, b6.start);
	std::function<void()> func8 = LeftClickRelease;
  b6.onRelease = new Action(func8);

  events.mouseBindings.push_back(b6);

	//  Draw mode: wireframe/fill
  Binding b7("Change draw mode", SDLK_z, 0, false);
  std::function<void()> func9 = ChangeDrawMode;
  b7.onRelease = new Action(func9);

  events.bindings.push_back(b7);

	//  Play/pause animation
  Binding b8("Play/Pause animation", SDLK_p, 0, false);
  std::function<void()> func10 = PlayAnimation;
  b8.onRelease = new Action(func10);

  events.bindings.push_back(b8);

	//	Render model
	Binding b9("Render model", SDLK_m, 0, false);
  std::function<void()> func11 = RenderModel;
  b9.onRelease = new Action(func11);

  events.bindings.push_back(b9);

	//	Render bones influence
	Binding b14("Render bones influence", SDLK_i, 0, false);
  std::function<void()> func16= RenderBonesInfluence;
  b14.onRelease = new Action(func16);

  events.bindings.push_back(b14);

	//	Render Bobby
	Binding b10("Render Bobby", SDLK_b, 0, false);
  std::function<void()> func12 = RenderBobby;
  b10.onRelease = new Action(func12);

  events.bindings.push_back(b10);

	//	Previous
	Binding b11("Previous", SDLK_KP_MINUS, 0, false);
  std::function<void()> func13 = Previous;
  b11.onRelease = new Action(func13);

  events.bindings.push_back(b11);

	//	Next
	Binding b12("Next", SDLK_KP_PLUS, 0, false);
  std::function<void()> func14 = Next;
  b12.onRelease = new Action(func14);

  events.bindings.push_back(b12);

	//	Change lighting
	Binding b13("Change lighting mode", SDLK_l, 0, false);
  std::function<void()> func15 = ChangeLightingMode;
  b13.onRelease = new Action(func15);

  events.bindings.push_back(b13);

	//	Reset pose
	Binding b15("Reset pose", SDLK_r, 0, false);
  std::function<void()> func17 = ResetObjectPose;
  b15.onRelease = new Action(func17);

  events.bindings.push_back(b15);
}
