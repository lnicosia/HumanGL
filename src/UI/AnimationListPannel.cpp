#include "HumanGL.hpp"
#include "UI/Button.class.hpp"
#include "UI.hpp"

void InitAnimationListPannel( void )
{
    AssetManager& assetManager = AssetManager::getInstance();

    std::vector<std::shared_ptr<GLFont>> fonts =
        assetManager.getAssetsOfType<GLFont>();
#ifdef USING_EXTERNAL_LIBS
    std::shared_ptr<GLFont> font =
        assetManager.loadAsset<GLFont>("resources/fonts/arial.ttf");
    std::shared_ptr<GLFont> font12 =
        assetManager.loadAsset<GLFont>("resources/fonts/arial.ttf");
#else
    std::shared_ptr<GLFont> font =
      assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");
    std::shared_ptr<GLFont> font12 =
        assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");
#endif

    // Animation list pannel
      UIElement animationListPannel(mft::vec2i(5, 0),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"));
      animationListPannel.visible = false;
      animationListPannel.setSize(mft::vec2i(312, 200));

    //    Design bars
    for (int i = 0; i < 7; i++)
    {
        UIElement left(mft::vec2i(0, 1 + i * 33),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
        left.setSize(mft::vec2i(23, 32));
        animationListPannel.addChild(std::make_shared<UIElement>(left));
        Button center(mft::vec2i(24, 1 + i * 33),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"),
              assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"),
              assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
        center.setSize(mft::vec2i(263, 32));
        center.active = false;
        center.setFont(font);
        animationListPannel.addChild(std::make_shared<Button>(center));
        UIElement right(mft::vec2i(288, 1 + i * 33),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
        right.setSize(mft::vec2i(23, 32));
        animationListPannel.addChild(std::make_shared<UIElement>(right));
    }

    UIElement animationListBorder(mft::vec2i(-1, 6 * 33 + 1),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
    animationListBorder.setSize(mft::vec2i(289, 32));
    animationListBorder.texts.push_back(UIText(">  Animations", mft::vec2i(12, 6), 16.0f));

    animationListPannel.addChild(std::make_shared<UIElement>(animationListBorder));

    ui.elements[2]->addChild(std::make_shared<UIElement>(animationListPannel));
}

void SelectAnimation(size_t id)
{
    //  Select anim
    std::vector<std::shared_ptr<Animation>> animations;
	if (renderingMode == Bobby || renderingMode == Roundy)
	{
		animations = bobbyAnimations;
	}
    else if (renderingMode == BobbyPlus || renderingMode == RoundyPlus)
    {
        animations = bobbyPlusAnimations;
    }
	else if (renderingMode == Model || renderingMode == BonesInfluence)
	{
		animations = skeletalAnimations;
	}
    selectedAnimation = animations[id];
    if (selectedObject != nullptr && selectedAnimation != nullptr)
    {
        if (selectedObject->getAnimationState() == AnimationState::Stopped
            || selectedObject->getAnimationState() == AnimationState::Paused)
            selectedObject->setAnimation(selectedAnimation);
        else
        {
            selectedObject->resetPose();
            selectedObject->playAnimation(selectedAnimation);
        }
    }

    //  Set buttons to released and this one to pressed
    std::shared_ptr<UIElement> animationListPannel = ui.elements[2]->getChild(5);
    for (int i = 0; i < 6; i++)
    {
        std::shared_ptr<Button> button =
            dynamic_pointer_cast<Button>(
                animationListPannel->getChild(i * 3 + 1));
        if (i == id)
            button->setReleasedImg(AssetManager::getInstance().loadAsset<Texture>(
                "resources/UI/defaultUI.png", "UI"));
        else
            button->setReleasedImg(AssetManager::getInstance().loadAsset<Texture>(
                "resources/UI/defaultUI-clear.png", "UI"));
    }

    UpdateAnimationPannel();
}

void UpdateAnimationList( void )
{
    std::shared_ptr<UIElement> animationListPannel = ui.elements[2]->getChild(5);
    std::vector<std::shared_ptr<Animation>> animations;
	if (renderingMode == Bobby || renderingMode == Roundy)
	{
		animations = bobbyAnimations;
	}
    else if (renderingMode == BobbyPlus || renderingMode == RoundyPlus)
    {
        animations = bobbyPlusAnimations;
    }
	else if (renderingMode == Model || renderingMode == BonesInfluence)
	{
		animations = skeletalAnimations;
	}
    for (int i = 0; i < 6; i++)
    {
        std::shared_ptr<Button> button =
            dynamic_pointer_cast<Button>(animationListPannel->getChild(i * 3 + 1));
        button->active = false;
        button->setText("");
        button->setReleasedImg(AssetManager::getInstance().loadAsset<Texture>(
            "resources/UI/defaultUI-clear.png", "UI"));
    }
    for (size_t i = 0; i < animations.size(); i++)
    {
        std::shared_ptr<Button> button =
            dynamic_pointer_cast<Button>(
                animationListPannel->getChild(18 - (1 + i) * 3 + 1));
        button->active = true;
        button->setText(animations[i]->getName());
        if (selectedAnimation != nullptr && selectedAnimation == animations[i])
            button->setReleasedImg(AssetManager::getInstance().loadAsset<Texture>(
            "resources/UI/defaultUI.png", "UI"));
        std::function<void(size_t)>func = SelectAnimation;
        button->onRelease = std::shared_ptr<ActionWrapper>(
            new Action<size_t>(func, i));
    }
}
