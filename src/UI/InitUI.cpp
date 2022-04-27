#include "HumanGL.hpp"
#include "UI/Button.class.hpp"
#include "UI.hpp"

void SelectMesh(std::shared_ptr<Mesh> mesh)
{
    selectedMesh = mesh;
    UpdateModelPannel();
    UpdateTransformPannel();
    UpdateColorPannel();
    UpdateAnimationPannel();
}

void IncreaseCameraSpeed(void)
{
    float cameraSpeed = scene.getCameraSpeed();
    if (cameraSpeed >= 4.9f)
        return;
    scene.setCameraSpeed(cameraSpeed + 0.1f);
    std::stringstream str;
    str << std::fixed << std::setprecision(1) << scene.getCameraSpeed();
    ui.elements[1]->getChild(2)->texts[0] = UIText("Camera speed " + str.str(), mft::vec2i(10, 4), 16.0f);
}

void DecreaseCameraSpeed(void)
{
    float cameraSpeed = scene.getCameraSpeed();
    if (cameraSpeed <= 0.1f)
        return;
    scene.setCameraSpeed(cameraSpeed - 0.1f);
    std::stringstream str;
    str << std::fixed << std::setprecision(1) << scene.getCameraSpeed();
    ui.elements[1]->getChild(2)->texts[0] = UIText("Camera speed " + str.str(), mft::vec2i(10, 4), 16.0f);
}

void InitTopPannel( void )
{
    AssetManager& assetManager = AssetManager::getInstance();

    std::vector<std::shared_ptr<GLFont>> fonts =
        assetManager.getAssetsOfType<GLFont>();
    std::shared_ptr<GLFont> font =
      assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");

    //  Top pannel (Bobby, Object etc tabs)

    UIElement topPannel(mft::vec2i(0, 860),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-dark.png", "UI"));
    topPannel.setSize(mft::vec2i(1600, 40));

    //    Bobby
    Button bobbyTab(mft::vec2i(32, 0),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-topRounded-clear.png", "UI"),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-topRounded-clearer.png", "UI"),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-topRounded-clearer.png", "UI"));
    bobbyTab.setAllSizes(mft::vec2i(100, 32));
    bobbyTab.setText("Bobby");
    bobbyTab.setFont(font);
    std::shared_ptr<ActionWrapper> action =
        std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(RenderBobby)));
    bobbyTab.onRelease = action;
    topPannel.addChild(std::shared_ptr<Button>(new Button(bobbyTab)));

    //    Object
    std::shared_ptr<GLObject> obj = assetManager.getAsset<GLObject>(modelPath);
    if (obj != nullptr)
    {
        Button objectTab(mft::vec2i(136, 0),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-topRounded.png", "UI"),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-topRounded-clearer.png", "UI"),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-topRounded-clearer.png", "UI"));
        objectTab.setAllSizes(mft::vec2i(100, 32));
        objectTab.setText(obj->getName());
        objectTab.setFont(font);
        action =
            std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(RenderModel)));
        objectTab.onRelease = action;
        topPannel.addChild(std::shared_ptr<Button>(new Button(objectTab)));
    }

    ui.registerElement(std::shared_ptr<UIElement>(new UIElement(topPannel)));
}

void InitScenePannel( void )
{
    AssetManager& assetManager = AssetManager::getInstance();

    std::vector<std::shared_ptr<GLFont>> fonts =
        assetManager.getAssetsOfType<GLFont>();
    std::shared_ptr<GLFont> font =
      assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");
    std::shared_ptr<GLFont> font12 =
        assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");

    UIElement scenePannel(mft::vec2i(0, 830));
    scenePannel.visible = false;
    scenePannel.setSize(mft::vec2i(1600, 38));
    scenePannel.texts.push_back(UIText("FPS:", mft::vec2i(330, 4), 16.0f));

    //    Draw mode button
    Button button(mft::vec2i(10, 0),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-rounded-bordered.png", "UI"),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer-rounded-bordered.png", "UI"),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer-rounded-bordered.png", "UI"));
    button.setText("Filled");
    button.setFont(font);
    button.setAllSizes(mft::vec2i(64, 24));
    std::shared_ptr<ActionWrapper> action =
        std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(ChangeDrawMode)));
    button.onRelease = action;
    scenePannel.addChild(std::shared_ptr<Button>(new Button(button)));

    //    Light button
    button.setPos(mft::vec2i(84, 0));
    button.setText("Unlit");
    button.setAllSizes(mft::vec2i(64, 24));
    action =
        std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(ChangeLightingMode)));
    button.onRelease = action;
    scenePannel.addChild(std::shared_ptr<Button>(new Button(button)));

    //    Camera speed
    UIElement cameraPannel(mft::vec2i(158, 0),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-rounded-bordered.png", "UI"));
    cameraPannel.setSize(mft::vec2i(162, 24));
    std::stringstream str;
    str << std::fixed << std::setprecision(1) << scene.getCameraSpeed();
    cameraPannel.texts.push_back(UIText("Camera speed " + str.str(), mft::vec2i(10, 4), 16.0f));

    //    Increase speed button
    Button buttonPlus(mft::vec2i(116, 3),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-dark.png", "UI"),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-dark.png", "UI"));
    buttonPlus.setText("+");
    buttonPlus.setFont(font);
    buttonPlus.setAllSizes(mft::vec2i(18, 18));
    action =
        std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(IncreaseCameraSpeed)));
    buttonPlus.onRelease = action;
    cameraPannel.addChild(std::shared_ptr<Button>(new Button(buttonPlus)));

    //    Decrease speed button
    Button buttonLess(mft::vec2i(136, 3),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-dark.png", "UI"),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-dark.png", "UI"));
    buttonLess.setText("-");
    buttonLess.setFont(font);
    buttonLess.setAllSizes(mft::vec2i(18, 18));
    action =
        std::shared_ptr<ActionWrapper>(new Action(std::function<void()>(DecreaseCameraSpeed)));
    buttonLess.onRelease = action;
    cameraPannel.addChild(std::shared_ptr<Button>(new Button(buttonLess)));

    scenePannel.addChild(std::shared_ptr<UIElement>(new UIElement(cameraPannel)));

    ui.registerElement(std::shared_ptr<UIElement>(new UIElement(scenePannel)));
}

void InitUI()
{
  std::cout << "Initializing UI..." << std::endl;

  AssetManager& assetManager = AssetManager::getInstance();

      ui.freeZones.push_back(Rectangle(mft::vec2i(0, 140), mft::vec2i(1280, 720)));

  InitTopPannel();
  InitScenePannel();

  //  Right pannel

  UIElement rightPannel(mft::vec2i(1280, 0),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"));
  rightPannel.setSize(mft::vec2i(320, 860));
  ui.registerElement(std::shared_ptr<UIElement>(new UIElement(rightPannel)));

  InitModelPannel();

  InitTransformPannel();

  //    Right pannel left pipe
  UIElement rightPannelLeftPipe(mft::vec2i(0, 22),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
  rightPannelLeftPipe.setSize(mft::vec2i(4, 836));
  ui.elements[2]->addChild(std::shared_ptr<UIElement>(new UIElement(rightPannelLeftPipe)));

  InitAnimationListPannel();

  //    Right pannel right pipe
  UIElement rightPannelRightPipe(mft::vec2i(312, 22),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  rightPannelRightPipe.setSize(mft::vec2i(6, 809));
  ui.elements[2]->addChild(std::shared_ptr<UIElement>(new UIElement(rightPannelRightPipe)));

  InitAnimationPannel();

  SelectMesh(selectedMesh);
}
