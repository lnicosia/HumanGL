#include "HumanGL.hpp"
#include "UI/Button.class.hpp"

void SetSelectedMeshColor(mft::vec4 color)
{
  mft::vec4 clamped = selectedMesh->getColor() + color;
  clamped.r = std::clamp(clamped.r, 0.0f, 1.0f);
  clamped.g = std::clamp(clamped.g, 0.0f, 1.0f);
  clamped.b = std::clamp(clamped.b, 0.0f, 1.0f);
  clamped.a = std::clamp(clamped.a, 0.0f, 1.0f);
  selectedMesh->setColor(clamped);
  UpdateColorPannel();
}

void MoveSelectedMesh(mft::vec3 move)
{
  selectedMesh->localTransform.move(move);
  UpdateTransformPannel();
}

void ScaleSelectedMesh(mft::vec3 scale)
{
  selectedMesh->localTransform.scale(scale);
  UpdateTransformPannel();
}

void RotateSelectedMesh(mft::vec3 axis, float degrees)
{
  selectedMesh->localTransform.rotate(mft::quat::rotation(axis, mft::radians(degrees)));
  UpdateTransformPannel();
}

void UpdateColorPannelButtons( void )
{
  //  Color
  std::shared_ptr<UIElement> colorPannel = ui.elements[1]->getChild(3)->getChild(15)->getChild(0);

  //  Red
  std::shared_ptr<ActionWrapper> action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec4>(SetSelectedMeshColor,
      mft::vec4(10.0f / 255.0f, 0.0f, 0.0f, 0.0f)));
  std::shared_ptr<Button> button =
    dynamic_pointer_cast<Button>(colorPannel->getChild(1));
  button->setOnRelease(action);
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec4>(SetSelectedMeshColor,
      mft::vec4(-10.0f / 255.0f, 0.0f, 0.0f, 0.0f)));
  button = dynamic_pointer_cast<Button>(colorPannel->getChild(2));
  button->setOnRelease(action);

  //  Green
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec4>(SetSelectedMeshColor,
      mft::vec4(0.0f, 10.0f / 255.0f, 0.0f, 0.0f)));
  button = dynamic_pointer_cast<Button>(colorPannel->getChild(4));
  button->setOnRelease(action);
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec4>(SetSelectedMeshColor,
      mft::vec4(0.0f, -10.0f / 255.0f, 0.0f, 0.0f)));
  button = dynamic_pointer_cast<Button>(colorPannel->getChild(5));
  button->setOnRelease(action);

  //  Blue
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec4>(SetSelectedMeshColor,
      mft::vec4(0.0f, 0.0f, 10.0f / 255.0f, 0.0f)));
  button = dynamic_pointer_cast<Button>(colorPannel->getChild(7));
  button->setOnRelease(action);
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec4>(SetSelectedMeshColor,
      mft::vec4(0.0f, 0.0f, -10.0f / 255.0f, 0.0f)));
  button = dynamic_pointer_cast<Button>(colorPannel->getChild(8));
  button->setOnRelease(action);

  //  Alpha
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec4>(SetSelectedMeshColor,
      mft::vec4(0.0f, 0.0f, 0.0f, 10.0f / 255.0f)));
  button = dynamic_pointer_cast<Button>(colorPannel->getChild(10));
  button->setOnRelease(action);
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec4>(SetSelectedMeshColor,
      mft::vec4(0.0f, 0.0f, 0.0f, -10.0f / 255.0f)));
  button = dynamic_pointer_cast<Button>(colorPannel->getChild(11));
  button->setOnRelease(action);
}

void UpdateTransformPannelButtons( void )
{
  std::shared_ptr<UIElement> transformPannel = ui.elements[1]->getChild(3)->getChild(10);

  //  Scale
  //    X
  std::shared_ptr<ActionWrapper> action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3>(ScaleSelectedMesh,
      mft::vec3(0.1f, 0.0f, 0.0f)));
  std::shared_ptr<Button> button =
    dynamic_pointer_cast<Button>(transformPannel->getChild(1)->getChild(1));
  button->setOnRelease(action);
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3>(ScaleSelectedMesh,
      mft::vec3(-0.1f, 0.0f, 0.0f)));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(1)->getChild(2));
  button->setOnRelease(action);

  //    Y
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3>(ScaleSelectedMesh,
      mft::vec3(0.0f, 0.1f, 0.0f)));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(1)->getChild(4));
  button->setOnRelease(action);
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3>(ScaleSelectedMesh,
      mft::vec3(0.0f, -0.1f, 0.0f)));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(1)->getChild(5));
  button->setOnRelease(action);

  //    Z
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3>(ScaleSelectedMesh,
      mft::vec3(0.0f, 0.0f, 0.1f)));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(1)->getChild(7));
  button->setOnRelease(action);
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3>(ScaleSelectedMesh,
      mft::vec3(0.0f, 0.0f, -0.1f)));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(1)->getChild(8));
  button->setOnRelease(action);

  //  Rotation
  //    X
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3, float>(RotateSelectedMesh,
      mft::vec3(1.0f, 0.0f, 0.0f), 10.0f));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(3)->getChild(1));
  button->setOnRelease(action);
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3, float>(RotateSelectedMesh,
      mft::vec3(1.0f, 0.0f, 0.0f), -10.0f));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(3)->getChild(2));
  button->setOnRelease(action);

  //    Y
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3, float>(RotateSelectedMesh,
      mft::vec3(0.0f, 1.0f, 0.0f), 10.0f));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(3)->getChild(4));
  button->setOnRelease(action);
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3, float>(RotateSelectedMesh,
      mft::vec3(0.0f, 1.0f, 0.0f), -10.0f));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(3)->getChild(5));
  button->setOnRelease(action);

  //    Z
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3, float>(RotateSelectedMesh,
      mft::vec3(0.0f, 0.0f, 1.0f), 10.0f));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(3)->getChild(7));
  button->setOnRelease(action);
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3, float>(RotateSelectedMesh,
      mft::vec3(0.0f, 0.0f, 1.0f), -10.0f));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(3)->getChild(8));
  button->setOnRelease(action);

  //  Pos
  //    X
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3>(MoveSelectedMesh,
      mft::vec3(0.1f, 0.0f, 0.0f)));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(5)->getChild(1));
  button->setOnRelease(action);
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3>(MoveSelectedMesh,
      mft::vec3(-0.1f, 0.0f, 0.0f)));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(5)->getChild(2));
  button->setOnRelease(action);

  //    Y
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3>(MoveSelectedMesh,
      mft::vec3(0.0f, 0.1f, 0.0f)));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(5)->getChild(4));
  button->setOnRelease(action);
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3>(MoveSelectedMesh,
      mft::vec3(0.0f, -0.1f, 0.0f)));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(5)->getChild(5));
  button->setOnRelease(action);

  //    Z
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3>(MoveSelectedMesh,
      mft::vec3(0.0f, 0.0f, 0.1f)));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(5)->getChild(7));
  button->setOnRelease(action);
  action =
    std::shared_ptr<ActionWrapper>(new Action<mft::vec3>(MoveSelectedMesh,
      mft::vec3(0.0f, 0.0f, -0.1f)));
  button = dynamic_pointer_cast<Button>(transformPannel->getChild(5)->getChild(8));
  button->setOnRelease(action);

}

void UpdateColorPannel( void )
{
  //  Color
  std::shared_ptr<UIElement> colorPannel = ui.elements[1]->getChild(3)->getChild(15)->getChild(0);
  const mft::vec4& color = selectedMesh->getColor();
  std::stringstream str;
  str << std::fixed << std::setprecision(1);

  //  Red
  colorPannel->getChild(0)->texts.clear();
  str.str("");
  str << color.r * 255;
  colorPannel->getChild(0)->texts.push_back(
    UIText(str.str(), mft::vec2i(8, 4), 16.0f));

  //  Green
  colorPannel->getChild(3)->texts.clear();
  str.str("");
  str << color.g * 255;
  colorPannel->getChild(3)->texts.push_back(
    UIText(str.str(), mft::vec2i(8, 4), 16.0f));

  //  Blue
  colorPannel->getChild(6)->texts.clear();
  str.str("");
  str << color.b * 255;
  colorPannel->getChild(6)->texts.push_back(
    UIText(str.str(), mft::vec2i(8, 4), 16.0f));

  //  Alpha
  colorPannel->getChild(9)->texts.clear();
  str.str("");
  str << color.a * 255;
  colorPannel->getChild(9)->texts.push_back(
    UIText(str.str(), mft::vec2i(8, 4), 16.0f));
}

void UpdateTransformPannel( void )
{                                                // rightP     / transformP / backgroundP
    std::shared_ptr<UIElement> transformPannel = ui.elements[1]->getChild(3)->getChild(10);
    ui.elements[1]->getChild(3)->getChild(2)->texts.clear();
    ui.elements[1]->getChild(3)->getChild(2)->texts.push_back(
      UIText(selectedMesh->getName(), mft::vec2i(10, 10), 16.0f));
    const mft::vec3& pos = selectedMesh->localTransform.getPos();
    mft::quat rot = selectedMesh->localTransform.getRotation();
    mft::vec3 rotV = mft::quat::euler(mft::quat::normalized(rot));
    //std::cout << "Quat = " << rot << std::endl;
    //std::cout << "Euler radians = " << rotV << std::endl;
    rotV.x = mft::degrees(rotV.x);
    rotV.y = mft::degrees(rotV.y);
    rotV.z = mft::degrees(rotV.z);
    //std::cout << "Euler degrees = " << rotV << std::endl;
    const mft::vec3& scale = selectedMesh->localTransform.getScale();
    std::stringstream str;
    str << std::fixed << std::setprecision(1);
    mft::vec2i textPos(12, 4);

    //  Scale
    transformPannel->getChild(1)->getChild(0)->texts.clear();
                   // slot2 1   // X
    str << scale.x;
    transformPannel->getChild(1)->getChild(0)->texts.push_back(
        UIText(str.str(), mft::vec2i(8, 4), 16.0f));

    transformPannel->getChild(1)->getChild(3)->texts.clear();
               // slot2 1   // Y
    str.str("");
    str << scale.y;
    transformPannel->getChild(1)->getChild(3)->texts.push_back(
        UIText(str.str(), mft::vec2i(8, 4), 16.0f));

    transformPannel->getChild(1)->getChild(6)->texts.clear();
                    // slot2 1    // Z
    str.str("");
    str << scale.z;
    transformPannel->getChild(1)->getChild(6)->texts.push_back(
    UIText(str.str(), mft::vec2i(8, 4), 16.0f));

    //  Rotation
    transformPannel->getChild(3)->getChild(0)->texts.clear();
                    // slot2 3   // X
    str.str("");
    str << rotV.x;
    transformPannel->getChild(3)->getChild(0)->texts.push_back(
        UIText(str.str(), mft::vec2i(8, 4), 16.0f));

    transformPannel->getChild(3)->getChild(3)->texts.clear();
                    // slot2 3   // Y
    str.str("");
    str << rotV.y;
    transformPannel->getChild(3)->getChild(3)->texts.push_back(
        UIText(str.str(), mft::vec2i(8, 4), 16.0f));
    transformPannel->getChild(3)->getChild(6)->texts.clear();
                 // slot2 3    // Z
    str.str("");
    str << rotV.z;
    transformPannel->getChild(3)->getChild(6)->texts.push_back(
        UIText(str.str(), mft::vec2i(8, 4), 16.0f));

    //  Location
    transformPannel->getChild(5)->getChild(0)->texts.clear();
                    // slot2 5   // X
    str.str("");
    str << pos.x;
    transformPannel->getChild(5)->getChild(0)->texts.push_back(
        UIText(str.str(), mft::vec2i(8, 4), 16.0f));

    transformPannel->getChild(5)->getChild(3)->texts.clear();
                    // slot2 5   // Y
    str.str("");
    str << pos.y;
    transformPannel->getChild(5)->getChild(3)->texts.push_back(
        UIText(str.str(), mft::vec2i(8, 4), 16.0f));

    transformPannel->getChild(5)->getChild(6)->texts.clear();
                    // slot2 5    // Z
    str.str("");
    str << pos.z;
    transformPannel->getChild(5)->getChild(6)->texts.push_back(
        UIText(str.str(), mft::vec2i(8, 4), 16.0f));
}

void SelectMesh(std::shared_ptr<Mesh> mesh)
{
    selectedMesh = mesh;
    UpdateModelPannel();
    UpdateTransformPannel();
    UpdateTransformPannelButtons();
    UpdateColorPannel();
    UpdateColorPannelButtons();
}

void AddMeshToModelPannel(AssetManager& assetManager, std::shared_ptr<GLFont> font,
    std::shared_ptr<UIElement> modelPannel, std::shared_ptr<Mesh> mesh, mft::vec2i& pos, int& count)
{
  if (count >= 11)
    return ;
  Button button(pos,
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-rounded-bordered.png", "UI"),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer-rounded-bordered.png", "UI"),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer-rounded-bordered.png", "UI"));
  button.setText(mesh->getName());
  button.setFont(font);
  button.setAllSizes(mft::vec2i(100, 18));
  std::function<void(std::shared_ptr<Mesh>)> func = SelectMesh;
  std::shared_ptr<ActionWrapper> action =
      std::shared_ptr<ActionWrapper>(new Action<std::shared_ptr<Mesh>>(func, mesh));
  button.onRelease = action;

  modelPannel->addChild(std::shared_ptr<Button>(new Button(button)));
  std::vector<std::shared_ptr<Mesh>> children = mesh->getChildren();
  pos.x += 20;
  pos.y -= 21;
  for (auto child : children)
  {
      AddMeshToModelPannel(assetManager, font, modelPannel, child, pos, ++count);
  }
  pos.x -= 20;
}

void UpdateModelPannel( void )
{
  if (selectedObject == nullptr)
    return ;
  AssetManager& assetManager = AssetManager::getInstance();
  std::shared_ptr<GLFont> font =
    assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");

  std::shared_ptr<UIElement> modelPannel = ui.elements[1]->getChild(1)->getChild(1);
  modelPannel->clearChildren();

  mft::vec2i pos(30, 254);
  int count = 0;
  AddMeshToModelPannel(assetManager, font, modelPannel, selectedObject->getMeshes()[0], pos, count);
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

  //  Top pannel

  UIElement topPannel(mft::vec2i(0, 860));
  topPannel.setSize(mft::vec2i(1600, 40));
  topPannel.texts.push_back(UIText("FPS:", mft::vec2i(10, -20), 16.0f));
  UIElement topPannel2(mft::vec2i(0, 2),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
  topPannel2.setSize(mft::vec2i(1600, 38));
  topPannel2.texts.push_back(UIText("Bobby", mft::vec2i(780, 10), 16.0f));
  topPannel.addChild(std::shared_ptr<UIElement>(new UIElement(topPannel2)));
  ui.registerElement(std::shared_ptr<UIElement>(new UIElement(topPannel)));

  //  Right pannel

  UIElement rightPannel(mft::vec2i(1280, 0),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"));
  rightPannel.setSize(mft::vec2i(320, 860));

  //  Model border and pannel
  UIElement modelBorder(mft::vec2i(2, 820),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer-cornered.png", "UI"));
  modelBorder.setSize(mft::vec2i(260, 40));
  modelBorder.texts.push_back(UIText("Model", mft::vec2i(105, 10), 16.0f));
  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(modelBorder)));

  UIElement modelPannel(mft::vec2i(3, 524),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannel.setSize(mft::vec2i(316, 290));
  modelPannel.visible = false;

  //    Model pannel background
  UIElement modelPannelBackground(mft::vec2i(0, 0),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelBackground.setSize(mft::vec2i(316, 290));
  modelPannelBackground.visible = false;
  for (size_t i = 0; i < 14; i++)
  {
      UIElement slot(mft::vec2i(24, 1 + i * 21),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      slot.setSize(mft::vec2i(263, 20));
      modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(slot)));
      UIElement modelPannelLeftBorder(mft::vec2i(0, 1 + i * 21),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      modelPannelLeftBorder.setSize(mft::vec2i(23, 20));
      modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelLeftBorder)));
      UIElement modelPannelRightBorder(mft::vec2i(288, 1 + i * 21),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      modelPannelRightBorder.setSize(mft::vec2i(23, 20));
      modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelRightBorder)));
  }
  UIElement modelPannelLeftBorder(mft::vec2i(0, 1),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelLeftBorder.setSize(mft::vec2i(12, 293));
  modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelLeftBorder)));
  UIElement modelPannelRightBorder(mft::vec2i(301, 2),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelRightBorder.setSize(mft::vec2i(12, 292));
  modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelRightBorder)));
  UIElement modelPannelLeftTop(mft::vec2i(0, 0),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelLeftTop.setSize(mft::vec2i(313, 10));
  modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelLeftTop)));
  UIElement modelPannelBottomBorder(mft::vec2i(0, 284),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelBottomBorder.setSize(mft::vec2i(313, 10));
  modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelBottomBorder)));

  modelPannel.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelBackground)));

  UIElement modelPannelSlots(mft::vec2i(0, 0),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelSlots.visible = false;
  modelPannel.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelSlots)));

  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannel)));

  //  Transform border
  UIElement transformBorder(mft::vec2i(2, 477),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
  transformBorder.setSize(mft::vec2i(260, 40));
  transformBorder.texts.push_back(UIText("Mesh", mft::vec2i(90, 10), 16.0f));
  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformBorder)));

  //    Transform pannel
  UIElement transformPannel(mft::vec2i(3, 175),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannel.setSize(mft::vec2i(312, 300));

  UIElement transformPannelSlot(mft::vec2i(0, 0),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"));
  transformPannelSlot.setSize(mft::vec2i(312, 300));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot)));

  UIElement transformPannelSlot1(mft::vec2i(1, 266),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot1.setSize(mft::vec2i(15, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot1)));
  UIElement transformPannelSlot2(mft::vec2i(17, 266),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot2.setSize(mft::vec2i(98, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot2)));
  UIElement transformPannelSlot3(mft::vec2i(116, 266),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot3.setSize(mft::vec2i(185, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot3)));
  UIElement transformPannelSlot3bis(mft::vec2i(302, 266),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot3bis.setSize(mft::vec2i(11, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot3bis)));

  UIElement transformPannelSlot4(mft::vec2i(1, 170),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot4.setSize(mft::vec2i(312, 95));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot4)));

  UIElement transformPannelSlot5(mft::vec2i(1, 135),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot5.setSize(mft::vec2i(15, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot5)));
  UIElement transformPannelSlot6(mft::vec2i(17, 135),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot6.setSize(mft::vec2i(98, 34));
  transformPannelSlot6.texts.push_back(UIText("Color", mft::vec2i(10, 10), 16.0f));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot6)));
  UIElement transformPannelSlot7(mft::vec2i(116, 135),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot7.setSize(mft::vec2i(185, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot7)));
  UIElement transformPannelSlot7bis(mft::vec2i(302, 135),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot7bis.setSize(mft::vec2i(11, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot7bis)));

  UIElement transformSlotsBackground(mft::vec2i(12, 169),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"));
  transformSlotsBackground.setSize(mft::vec2i(290, 96));
  for (size_t i = 0; i < 3; i++)
  {
      UIElement slot(mft::vec2i(5, 1 + i * 32),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
      slot.setSize(mft::vec2i(98, 31));
      std::string str;
      if (i == 2)
          str = "Location";
      else if (i == 1)
          str = "Rotation";
      else if (i == 0)
          str = "Scale";
      slot.texts.push_back(UIText(str, mft::vec2i(20, 7), 16.0f));
      transformSlotsBackground.addChild(std::shared_ptr<UIElement>(new UIElement(slot)));

      UIElement slot2(mft::vec2i(104, 1 + i * 32),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
      slot2.setSize(mft::vec2i(185, 31));

      for (size_t j = 0; j < 3; j++)
      {
          UIElement N(mft::vec2i(6 + j * 60, 3));
          if (j == 0)
              N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-X.png", "UI"));
          else if (j == 1)
              N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-Y.png", "UI"));
          else if (j == 2)
              N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-Z.png", "UI"));
          N.setSize(mft::vec2i(40, 24));
          slot2.addChild(std::shared_ptr<UIElement>(new UIElement(N)));

          Button button(mft::vec2i(49 + 60 * j, 15),
              assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"),
              assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"),
              assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
          button.setText("+");
          //button.setPos(mft::vec2i(49 + 60 * j, 16));
          button.setFont(font12);
          button.setAllSizes(mft::vec2i(14, 14));
          slot2.addChild(std::shared_ptr<Button>(new Button(button)));


          button.setPos(mft::vec2i(49 + 60 * j, 1));
          button.setText("-");
          button.setFont(font12);
          button.setAllSizes(mft::vec2i(14, 14));
          slot2.addChild(std::shared_ptr<Button>(new Button(button)));
      }
      transformSlotsBackground.addChild(std::shared_ptr<UIElement>(new UIElement(slot2)));
  }
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformSlotsBackground)));

  UIElement transformPannelSlot8(mft::vec2i(1, 100),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot8.setSize(mft::vec2i(15, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot8)));
  UIElement transformPannelSlot9(mft::vec2i(17, 100),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot9.setSize(mft::vec2i(98, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot9)));
  UIElement transformPannelSlot10(mft::vec2i(116, 100),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot10.setSize(mft::vec2i(185, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot10)));
  UIElement transformPannelSlot11(mft::vec2i(302, 100),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot11.setSize(mft::vec2i(11, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot11)));

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
          N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-X.png", "UI"));
      else if (j == 1)
          N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-Y.png", "UI"));
      else if (j == 2)
          N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-Z.png", "UI"));
      else if (j == 3)
          N.setImage(assetManager.loadAsset<Texture>("resources/UI/defaultUI-Z.png", "UI"));
      N.setSize(mft::vec2i(40, 24));
      colorPannelSlot.addChild(std::shared_ptr<UIElement>(new UIElement(N)));

      Button button(mft::vec2i(53 + 68 * j, 16),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
      button.setText("+");
      //button.setPos(mft::vec2i(49 + 60 * j, 16));
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

  UIElement transformPannelSlot12(mft::vec2i(1, 65),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot12.setSize(mft::vec2i(15, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot12)));
  UIElement transformPannelSlot13(mft::vec2i(17, 65),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot13.setSize(mft::vec2i(98, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot13)));
  UIElement transformPannelSlot14(mft::vec2i(116, 65),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot14.setSize(mft::vec2i(185, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot14)));
  UIElement transformPannelSlot15(mft::vec2i(302, 65),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannelSlot15.setSize(mft::vec2i(11, 34));
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannelSlot15)));

  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannel)));

  //    Right pannel pipe
  UIElement rightPannelRightPipe(mft::vec2i(-2, 140),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
  rightPannelRightPipe.setSize(mft::vec2i(4, 720));
  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(rightPannelRightPipe)));

  ui.registerElement(std::shared_ptr<UIElement>(new UIElement(rightPannel)));

  //  Bottom pannel

  UIElement bottomPannel(mft::vec2i(0, 0));
  bottomPannel.setSize(mft::vec2i(1280, 140));
  ui.registerElement(std::shared_ptr<UIElement>(new UIElement(bottomPannel)));

  UpdateModelPannel();
  SelectMesh(selectedMesh);
}
