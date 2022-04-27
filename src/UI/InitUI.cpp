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

void InitUI()
{
  std::cout << "Initializing UI..." << std::endl;
  AssetManager& assetManager = AssetManager::getInstance();

  std::vector<std::shared_ptr<GLFont>> fonts =
      assetManager.getAssetsOfType<GLFont>();
  std::shared_ptr<GLFont> font =
    assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");
  std::shared_ptr<GLFont> font12 =
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
  action =
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

  //  Right pannel

  UIElement rightPannel(mft::vec2i(1280, 0),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"));
  rightPannel.setSize(mft::vec2i(320, 860));

  //    Model pannel
  UIElement modelPannel(mft::vec2i(5, 511),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannel.setSize(mft::vec2i(316, 290));
  modelPannel.visible = false;

  //    Model pannel background
  UIElement modelPannelBackground(mft::vec2i(0, 0),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelBackground.setSize(mft::vec2i(316, 280));
  modelPannelBackground.visible = false;
  for (size_t i = 0; i < 10; i++)
  {
      UIElement slot(mft::vec2i(24, 1 + i * 32),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      slot.setSize(mft::vec2i(263, 31));
      modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(slot)));
      UIElement modelPannelLeftBorder(mft::vec2i(0, 1 + i * 32),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      modelPannelLeftBorder.setSize(mft::vec2i(23, 31));
      modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelLeftBorder)));
      UIElement modelPannelRightBorder(mft::vec2i(288, 1 + i * 32),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      modelPannelRightBorder.setSize(mft::vec2i(23, 31));
      modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelRightBorder)));
  }
  UIElement modelPannelLeftBorder(mft::vec2i(0, 1),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelLeftBorder.setSize(mft::vec2i(12, 293));
  //modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelLeftBorder)));
  UIElement modelPannelRightBorder(mft::vec2i(301, 2),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelRightBorder.setSize(mft::vec2i(12, 292));
  //modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelRightBorder)));
  UIElement modelPannelLeftTop(mft::vec2i(0, 0),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelLeftTop.setSize(mft::vec2i(313, 10));
  //modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelLeftTop)));
  UIElement modelPannelBottomBorder(mft::vec2i(0, 284),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelBottomBorder.setSize(mft::vec2i(313, 10));
 // modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelBottomBorder)));

  modelPannel.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelBackground)));

  UIElement modelPannelSlots(mft::vec2i(0, 0),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelSlots.visible = false;
  modelPannel.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelSlots)));



  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannel)));

  //  Model border
  UIElement modelBorder(mft::vec2i(2, 800),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
  modelBorder.setSize(mft::vec2i(290, 31));
  modelBorder.texts.push_back(UIText(">  Model", mft::vec2i(12, 6), 20.0f));

  UIElement detailsBorder(mft::vec2i(0, 32),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear-cornered.png", "UI"));
  detailsBorder.setSize(mft::vec2i(100, 26));
  detailsBorder.texts.push_back(UIText("Details", mft::vec2i(14, 6), 16.0f));
  modelBorder.addChild(std::shared_ptr<UIElement>(new UIElement(detailsBorder)));

  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(modelBorder)));

  //  Transform border

  //    Transform pannel
  UIElement transformPannel(mft::vec2i(4, 167),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"));
  transformPannel.setSize(mft::vec2i(312, 300));

  //    Design bars
  for (int i = 0; i < 8; i++)
  {
      UIElement transformPannelSlot1(mft::vec2i(1, i * 35 + 65),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      transformPannelSlot1.setSize(mft::vec2i(16, 34));
      transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot1)));
      UIElement transformPannelSlot2(mft::vec2i(17, i * 35 + 65),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      transformPannelSlot2.setSize(mft::vec2i(98, 34));
      if (i == 2)
          transformPannelSlot2.texts.push_back(UIText("Color", mft::vec2i(10, 10), 16.0f));
      transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot2)));
      UIElement transformPannelSlot3(mft::vec2i(116, i * 35 + 65),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      transformPannelSlot3.setSize(mft::vec2i(185, 34));
      transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot3)));
      UIElement transformPannelSlot3bis(mft::vec2i(302, i * 35 + 65),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      transformPannelSlot3bis.setSize(mft::vec2i(11, 34));
      transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot3bis)));
  }

  UIElement transformSlotsBackground(mft::vec2i(12, 169),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"));
  transformSlotsBackground.setSize(mft::vec2i(290, 105));
  for (size_t i = 0; i < 3; i++)
  {
      UIElement slot(mft::vec2i(5, 1 + i * 35),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
      slot.setSize(mft::vec2i(98, 34));
      std::string str;
      if (i == 2)
          str = "Location";
      else if (i == 1)
          str = "Rotation";
      else if (i == 0)
          str = "Scale";
      slot.texts.push_back(UIText(str, mft::vec2i(20, 10), 16.0f));
      transformSlotsBackground.addChild(std::shared_ptr<UIElement>(new UIElement(slot)));

      UIElement slot2(mft::vec2i(104, 1 + i * 35),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
      slot2.setSize(mft::vec2i(185, 34));

      for (size_t j = 0; j < 3; j++)
      {
          UIElement N(mft::vec2i(6 + j * 60, 5));
          if (j == 0)
              N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-X-Dark.png", "UI"));
          else if (j == 1)
              N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-Y-Dark.png", "UI"));
          else if (j == 2)
              N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-Z-Dark.png", "UI"));
          N.setSize(mft::vec2i(40, 24));
          slot2.addChild(std::shared_ptr<UIElement>(new UIElement(N)));

          Button button(mft::vec2i(49 + 60 * j, 17),
              assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"),
              assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"),
              assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
          button.setText("+");
          //button.setPos(mft::vec2i(49 + 60 * j, 16));
          button.setFont(font12);
          button.setAllSizes(mft::vec2i(15, 15));
          slot2.addChild(std::shared_ptr<Button>(new Button(button)));


          button.setPos(mft::vec2i(49 + 60 * j, 3));
          button.setText("-");
          button.setFont(font12);
          button.setAllSizes(mft::vec2i(15, 15));
          slot2.addChild(std::shared_ptr<Button>(new Button(button)));
      }
      transformSlotsBackground.addChild(std::shared_ptr<UIElement>(new UIElement(slot2)));
  }
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformSlotsBackground)));

  UIElement colorPannel(mft::vec2i(12, 100),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"));
  colorPannel.setSize(mft::vec2i(290, 34));

  UIElement colorPannelSlot(mft::vec2i(5, 0),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
  colorPannelSlot.setSize(mft::vec2i(284, 34));

  for (size_t j = 0; j < 4; j++)
  {
      UIElement N(mft::vec2i(10 + j * 68, 4));
      if (j == 0)
          N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-X-Dark.png", "UI"));
      else if (j == 1)
          N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-Y-Dark.png", "UI"));
      else if (j == 2)
          N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-Z-Dark.png", "UI"));
      else if (j == 3)
          N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-A-Dark.png", "UI"));
      N.setSize(mft::vec2i(40, 24));
      colorPannelSlot.addChild(std::shared_ptr<UIElement>(new UIElement(N)));

      Button button(mft::vec2i(53 + 68 * j, 16),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
      button.setText("+");
      button.setFont(font12);
      button.setAllSizes(mft::vec2i(14, 14));
      colorPannelSlot.addChild(std::shared_ptr<Button>(new Button(button)));


      button.setPos(mft::vec2i(53 + 68 * j, 2));
      button.setText("-");
      button.setFont(font12);
      button.setAllSizes(mft::vec2i(14, 14));
      colorPannelSlot.addChild(std::shared_ptr<Button>(new Button(button)));
  }
  colorPannel.addChild(std::shared_ptr<UIElement>(new UIElement(colorPannelSlot)));

  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(colorPannel)));

  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannel)));

  UIElement transformBorder(mft::vec2i(2, 477),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
  transformBorder.setSize(mft::vec2i(303, 34));
  transformBorder.texts.push_back(UIText(">  Mesh", mft::vec2i(12, 6), 20.0f));
  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformBorder)));

  //    Right pannel pipe
  UIElement rightPannelRightPipe(mft::vec2i(0, 22),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
  rightPannelRightPipe.setSize(mft::vec2i(4, 836));
  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(rightPannelRightPipe)));

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
  animationListBorder.setSize(mft::vec2i(288, 34));
  animationListBorder.texts.push_back(UIText(">  Animations", mft::vec2i(12, 6), 20.0f));

  animationListPannel.addChild(std::shared_ptr<UIElement>(new UIElement(animationListBorder)));

  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(animationListPannel)));

  ui.registerElement(std::shared_ptr<UIElement>(new UIElement(rightPannel)));

  //  Bottom pannel

  UIElement bottomPannel(mft::vec2i(0, 0));
  bottomPannel.setSize(mft::vec2i(1280, 140));
  ui.registerElement(std::shared_ptr<UIElement>(new UIElement(bottomPannel)));

  SelectMesh(selectedMesh);
}
