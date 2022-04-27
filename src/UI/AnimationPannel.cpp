#include "HumanGL.hpp"
#include "UI/Button.class.hpp"
#include "UI.hpp"

void SelectAnimation(std::shared_ptr<Animation> anim,
    std::shared_ptr<Button> sourceButton)
{
    //  Select anim
    selectedAnimation = anim;
    if (selectedObject != nullptr && selectedAnimation != nullptr)
		selectedObject->setAnimation(selectedAnimation.get());

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
}

void UpdateAnimationList( void )
{
    std::shared_ptr<UIElement> animationListPannel = ui.elements[2]->getChild(5);
    std::vector<std::shared_ptr<Animation>> animations;
	if (renderingMode == Bobby)
	{
		animations = bobbyAnimations;
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

void UpdateAnimationPannel( void )
{
    UpdateAnimationList();
}
