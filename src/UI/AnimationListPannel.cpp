#include "HumanGL.hpp"
#include "UI/Button.class.hpp"
#include "UI.hpp"

void InitAnimationListPannel( void )
{
    AssetManager& assetManager = AssetManager::getInstance();

    std::vector<std::shared_ptr<GLFont>> fonts =
        assetManager.getAssetsOfType<GLFont>();
    std::shared_ptr<GLFont> font =
      assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");
    std::shared_ptr<GLFont> font12 =
        assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");

    // Animation list pannel
      UIElement animationListPannel(mft::vec2i(5, 0),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"));
      animationListPannel.visible = false;
      animationListPannel.setSize(mft::vec2i(312, 200));

    //    Design bars
    for (int i = 0; i < 6; i++)
    {
        UIElement left(mft::vec2i(0, 22 + i * 35),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
        left.setSize(mft::vec2i(23, 34));
        animationListPannel.addChild(std::shared_ptr<UIElement>(new UIElement(left)));
        Button center(mft::vec2i(24, 22 + i * 35),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"),
              assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"),
              assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
        center.setSize(mft::vec2i(263, 34));
        center.active = false;
        center.setFont(font);
        animationListPannel.addChild(std::shared_ptr<Button>(new Button(center)));
        UIElement right(mft::vec2i(288, 22 + i * 35),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
        right.setSize(mft::vec2i(23, 34));
        animationListPannel.addChild(std::shared_ptr<UIElement>(new UIElement(right)));
    }

    UIElement animationListBorder(mft::vec2i(-1, 5 * 35 + 22),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
    animationListBorder.setSize(mft::vec2i(289, 34));
    animationListBorder.texts.push_back(UIText(">  Animations", mft::vec2i(12, 6), 20.0f));

    animationListPannel.addChild(std::shared_ptr<UIElement>(new UIElement(animationListBorder)));

    ui.elements[2]->addChild(std::shared_ptr<UIElement>(new UIElement(animationListPannel)));
}

void SelectAnimation(std::shared_ptr<Animation> anim,
    std::shared_ptr<Button> sourceButton)
{
    //  Select anim
    selectedAnimation = anim;
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
        button->setReleasedImg(AssetManager::getInstance().loadAsset<Texture>(
            "resources/UI/defaultUI-clear.png", "UI"));
    }
    sourceButton->setReleasedImg(AssetManager::getInstance().loadAsset<Texture>(
        "resources/UI/defaultUI.png", "UI"));

    UpdateAnimationPannel();
}

void UpdateAnimationList( void )
{
    std::shared_ptr<UIElement> animationListPannel = ui.elements[2]->getChild(5);
    std::vector<std::shared_ptr<Animation>> animations;
	if (renderingMode == Bobby)
	{
		animations = bobbyAnimations;
	}
    else if (renderingMode == BobbyPlus)
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
                animationListPannel->getChild(18 - (2 + i) * 3 + 1));
        button->active = true;
        button->setText(animations[i]->getName());
        if (selectedAnimation != nullptr && selectedAnimation == animations[i])
            button->setReleasedImg(AssetManager::getInstance().loadAsset<Texture>(
            "resources/UI/defaultUI.png", "UI"));
        std::function<void(std::shared_ptr<Animation>, std::shared_ptr<Button>)>
            func = SelectAnimation;
        std::shared_ptr<ActionWrapper> action =
            std::shared_ptr<ActionWrapper>(
                new Action<std::shared_ptr<Animation>, std::shared_ptr<Button>>(
                    func, animations[i], button));
        button->onRelease = action;
    }
}
