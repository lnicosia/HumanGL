#include "HumanGL.hpp"
#include "Object/AssetManager.class.hpp"
#include "GLContext.class.hpp"
#include "UI/Button.class.hpp"
#include "UI.hpp"
#include "NotRealEngine.hpp"

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

	if (isMouseOnUI == true)
		return ;

	//	If not on UI, move camera

	mouseStart = events.mouseGlobalPos;
	SDL_ShowCursor(SDL_DISABLE);
}

void LeftClickPressed(mft::vec2i& mouseStart)
{
	//	Check UI

	if (SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE)
		return ;

	//	If not on UI, move camera

	scene.setYaw(scene.getYaw()
		+ (float)(mouseStart.x - events.mouseGlobalPos.x) * scene.getCamera().sensitivity);
	scene.setPitch(scene.getPitch()
		+ (float)(mouseStart.y - events.mouseGlobalPos.y) * scene.getCamera().sensitivity);
	mouseStart = events.mouseGlobalPos;
}

void LeftClickRelease()
{
	//	Check UI

	//	If not on UI, move camera

	SDL_ShowCursor(SDL_ENABLE);
}

void ChangeDrawMode()
{
	std::shared_ptr<Button> button =
		dynamic_pointer_cast<Button>(ui.elements[1]->getChild(0));
	if (scene.getDrawMode() != DrawMode::Wireframe)
	{
		scene.setDrawMode(DrawMode::Wireframe);
		button->setText("Wireframe");
	}
	else
	{
		scene.setDrawMode(DrawMode::Fill);
		button->setText("Filled");
	}
}

void PlayAnimation()
{
	if (selectedObject == nullptr)
		return ;
	AnimationState animState = selectedObject->getAnimationState();
	std::shared_ptr<UIElement> animationControlPannel =
		ui.elements[3]->getChild(0)->getChild(1);
	std::shared_ptr<Button> playButton =
		dynamic_pointer_cast<Button>(animationControlPannel->getChild(7)->getChild(0));
	if (animState == AnimationState::Stopped)
	{
		selectedObject->playAnimation(selectedAnimation.get());
		playButton->setText("Pause");
	}
	else if (animState == AnimationState::Playing)
	{
		selectedObject->pauseAnimation();
		playButton->setText("Play");
	}
	else if (animState == AnimationState::Paused)
	{
		selectedObject->resumeAnimation();
		playButton->setText("Pause");
	}
	UpdateAnimationStatusText();
}

void RenderBobby()
{
	renderingMode = Bobby;

	if (selectedObject != nullptr)
		selectedObject->pauseAnimation();
	AssetManager& assetManager = AssetManager::getInstance();
	selectedObject = assetManager.getAssetByName<GLObject>("Bobby");
	PopulateArmature();
	SelectMesh(selectedObject->getMeshes()[0]);
	std::shared_ptr<Button> bobbyButton =
		dynamic_pointer_cast<Button>(ui.elements[0]->getChild(0));
	if (bobbyButton)
		bobbyButton->setReleasedImg(assetManager.loadAsset<Texture>(
			"resources/UI/defaultUI-topRounded-clear.png", "UI"));
	std::shared_ptr<Button> modelButton =
		dynamic_pointer_cast<Button>(ui.elements[0]->getChild(1));
	if (modelButton)
		modelButton->setReleasedImg(assetManager.loadAsset<Texture>(
			"resources/UI/defaultUI-topRounded.png", "UI"));
	selectedAnimation = bobbyAnimations[0];
	if (selectedObject != nullptr && selectedAnimation != nullptr)
		selectedObject->setAnimation(selectedAnimation.get());

	std::vector<std::shared_ptr<GLObject>> objects =
		assetManager.getAssetsOfType<GLObject>();

	for (auto& object: objects)
	{
		object->visible = false;
	}
	selectedObject->visible = true;
	UpdateAnimationPannel();
}

void SelectModel()
{
	if (selectedObject != nullptr)
		selectedObject->pauseAnimation();
	AssetManager& assetManager = AssetManager::getInstance();
	selectedObject = assetManager.getAsset<GLObject>(modelPath);
	if (skeletalAnimations.empty())
		selectedAnimation = nullptr;
	else
		selectedAnimation = skeletalAnimations[0];
	if (selectedObject != nullptr && selectedAnimation != nullptr)
		selectedObject->setAnimation(selectedAnimation.get());

	assetManager.getAssetByName<GLObject>("Bobby")->visible = false;
	std::shared_ptr<GLObject> rock =
		assetManager.getAsset<GLObject>("resources/objects/Rock/rock.dae");
	if (rock != nullptr)
		rock->visible = true;
	if (selectedObject != nullptr)
	{
		PopulateArmature();
		selectedObject->visible = true;
		SelectMesh(selectedObject->getMeshes()[0]);
		std::shared_ptr<Button> bobbyButton =
			dynamic_pointer_cast<Button>(ui.elements[0]->getChild(0));
		if (bobbyButton)
			bobbyButton->setReleasedImg(assetManager.loadAsset<Texture>(
				"resources/UI/defaultUI-topRounded.png", "UI"));
		std::shared_ptr<Button> modelButton =
			dynamic_pointer_cast<Button>(ui.elements[0]->getChild(1));
		if (modelButton)
			modelButton->setReleasedImg(assetManager.loadAsset<Texture>(
				"resources/UI/defaultUI-topRounded-clear.png", "UI"));
	}
	UpdateAnimationPannel();
}

void RenderModel()
{
	renderingMode = Model;
	SelectModel();
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
	renderingMode = BonesInfluence;
	SelectModel();
	if (selectedObject == nullptr)
		return ;
	selectedObject->setShader(GLContext::getShader("bonesInfluence"));
	selectedObject->bindBones();
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
	UpdateAnimationPannel();
	UpdateAnimationList();
}

void Next()
{
	if (renderingMode == BonesInfluence)
	{
		if (selectedObject == nullptr)
			return ;
		selectedBone++;
		if (selectedBone > selectedObject->getNbBones())
			selectedBone = 0;
		bindInt(GLContext::getShader("bonesInfluence")->programID, "selectedBone", selectedBone);
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
	UpdateAnimationPannel();
	UpdateAnimationList();
}

void Previous()
{
	if (renderingMode == BonesInfluence)
	{
		if (selectedObject == nullptr)
			return ;
		if (selectedBone == 0)
			selectedBone = selectedObject->getNbBones() - 1;
		else
			selectedBone--;
		bindInt(GLContext::getShader("bonesInfluence")->programID, "selectedBone", selectedBone);
	}
	else
		PreviousAnim();
}

void ChangeLightingMode()
{
	std::shared_ptr<Button> button =
		dynamic_pointer_cast<Button>(ui.elements[1]->getChild(1));
	if (scene.getLightingMode() == LightingMode::Lit)
	{
		scene.setLightingMode(LightingMode::Unlit);
		button->setText("Unlit");
	}
	else
	{
		scene.setLightingMode(LightingMode::Lit);
		button->setText("Lit");
	}
}

void ResetObjectPose()
{
	if (selectedObject != nullptr)
		selectedObject->resetPose();
	std::shared_ptr<UIElement> animationControlPannel =
		ui.elements[3]->getChild(0)->getChild(1);
	std::shared_ptr<Button> playButton =
		dynamic_pointer_cast<Button>(animationControlPannel->getChild(7)->getChild(0));
	playButton->setText("Play");
	UpdateAnimationStatusText();
}

void ObjectLeft()
{
	if (selectedMesh == nullptr)
		return ;
	selectedMesh->localTransform.move(mft::vec3(-0.05f, 0.0f, 0.0f));
}

void ObjectRight()
{
	if (selectedMesh == nullptr)
		return ;
	selectedMesh->localTransform.move(mft::vec3(0.05f, 0.0f, 0.0f));
}

void ObjectForward()
{
	if (selectedMesh == nullptr)
		return ;
	selectedMesh->localTransform.move(mft::vec3(0.0f, 0.0f, -0.05f));
}

void ObjectBackward()
{
	if (selectedMesh == nullptr)
		return ;
	selectedMesh->localTransform.move(mft::vec3(0.0f, 0.0f, 0.05f));
}

void ThirdPersonMode()
{
	if (renderingMode == ThirdPerson)
	{
		renderingMode = Bobby;
	}
	else
	{
		RenderBobby();
		renderingMode = ThirdPerson;
		mft::vec3 angle = mft::quat::euler(selectedObject->transform.getRotation());

		scene.setCameraPos(selectedObject->transform.getPos()
			+ mft::vec3(0.0f, 2.0f * selectedObject->transform.getScale().y, 0.0f));
		scene.setYaw(angle.y + 90.0f);
		scene.setPitch(0.0f);
		scene.backward(3.0f * selectedObject->transform.getScale().z);
		scene.setPitch(15.0f);
	}
}

//  Init

void AddBinding(std::string name, uint32_t key1, uint32_t key2, bool editable,
	std::shared_ptr<ActionWrapper> whenPressed, std::shared_ptr<ActionWrapper> onPress,
	std::shared_ptr<ActionWrapper> whenReleased, std::shared_ptr<ActionWrapper> onRelease)
{
	Binding b(name, key1, key2, editable);
	if (whenPressed)
		b.whenPressed = whenPressed;
	if (onPress)
		b.onPress = onPress;
	if (whenReleased)
		b.whenReleased = whenReleased;
	if (onRelease)
		b.onRelease = onRelease;
	events.bindings.push_back(b);
}

void AddMouseBinding(std::string name, uint32_t key1, uint32_t key2, bool editable,
	std::shared_ptr<ActionWrapper> whenPressed, std::shared_ptr<ActionWrapper> onPress,
	std::shared_ptr<ActionWrapper> whenReleased, std::shared_ptr<ActionWrapper> onRelease)
{
	MouseBinding b(name, key1, key2, editable);
	if (whenPressed)
		b.whenPressed = whenPressed;
	if (onPress)
		b.onPress = onPress;
	if (whenReleased)
		b.whenReleased = whenReleased;
	if (onRelease)
		b.onRelease = onRelease;
	events.mouseBindings.push_back(b);
}

void InitBindings()
{
	//  Quit
	AddBinding("Quit", SDLK_ESCAPE, 0, false,
		nullptr, nullptr, nullptr,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(Quit))));

	//  Left
	AddBinding("Left", 0, SDLK_a, false,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(Left))),
		nullptr, nullptr, nullptr);

	//  Right
	AddBinding("Right", 0, SDLK_d, false,
		std::shared_ptr<ActionWrapper>( new Action(std::function<void()>(Right))),
		nullptr, nullptr, nullptr);

	//  Forward
	AddBinding("Forward", 0, SDLK_w, false,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(Forward))),
		nullptr, nullptr, nullptr);

	//  Backward
	AddBinding("Backward", 0, SDLK_s, false,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(Backward))),
		nullptr, nullptr, nullptr);

	//	Mouse

	MouseBinding b6("Mouse left", SDL_BUTTON_LEFT, 0, false);
	events.mouseBindings.push_back(b6);
	MouseBinding& ref = events.mouseBindings.back();
	std::function<void(mft::vec2i&)> func6 = LeftClickPress;
	ref.onPress = std::shared_ptr<ActionWrapper>(new Action<mft::vec2i&>(func6, ref.start));
	std::function<void(mft::vec2i&)> func7 = LeftClickPressed;
	ref.whenPressed = std::shared_ptr<ActionWrapper>(new Action<mft::vec2i&>(func7, ref.start));
	std::function<void()> func8 = LeftClickRelease;
	ref.onRelease = std::shared_ptr<ActionWrapper>(new Action(func8));

	//  Draw mode: wireframe/fill
	AddBinding("Change draw mode", SDLK_z, 0, false,
		nullptr, nullptr, nullptr,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(ChangeDrawMode))));

	//  Play/pause animation
	AddBinding("Play/Pause animation", SDLK_p, 0, false,
		nullptr, nullptr, nullptr,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(PlayAnimation))));

	//	Render model
	AddBinding("Render model", SDLK_m, SDLK_2, false,
		nullptr, nullptr, nullptr,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(RenderModel))));

	//	Render bones influence
	AddBinding("Render bones influence", SDLK_i, SDLK_3, false,
		nullptr, nullptr, nullptr,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(RenderBonesInfluence))));

	//	Render Bobby
	AddBinding("Render Bobby", SDLK_b, SDLK_1, false,
		nullptr, nullptr, nullptr,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(RenderBobby))));

	//	Previous
	AddBinding("Previous", SDLK_KP_MINUS, 0, false,
		nullptr, nullptr, nullptr,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(Previous))));

	//	Next
	AddBinding("Next", SDLK_KP_PLUS, 0, false,
		nullptr, nullptr, nullptr,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(Next))));

	//	Change lighting
	AddBinding("Change lighting mode", SDLK_l, 0, false,
		nullptr, nullptr, nullptr,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(ChangeLightingMode))));

	//	Reset pose
	AddBinding("Reset pose", SDLK_r, 0, false,
		nullptr, nullptr, nullptr,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(ResetObjectPose))));

	//  Move object left
	AddBinding("Left", SDLK_LEFT, 0, false,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(ObjectLeft))),
		nullptr, nullptr, nullptr);

	//  Move object right
	AddBinding("Right", SDLK_RIGHT, 0, false,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(ObjectRight))),
		nullptr, nullptr, nullptr);

	//  Move object forward
	AddBinding("Forward", SDLK_UP, 0, false,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(ObjectForward))),
		nullptr, nullptr, nullptr);

	//  Move object backward
	AddBinding("Backward", SDLK_DOWN, 0, false,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(ObjectBackward))),
		nullptr, nullptr, nullptr);

	//  Third person mode
	AddBinding("Third person", SDLK_RETURN, 0, false,
		nullptr, nullptr, nullptr,
		std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(ThirdPersonMode))));

}
