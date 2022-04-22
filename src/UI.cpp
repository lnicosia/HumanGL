#include "HumanGL.hpp"
#include "UI/Button.class.hpp"

void UpdateTransformPannel( void )
{
    std::shared_ptr<UIElement> transformPannel = ui.elements[1]->getChild(3);
    if (transformPannel == nullptr)
        std::cout << "NULLPTR" << std::endl;
    transformPannel->clearChildren();
    //transform->
}

void SelectMesh(std::shared_ptr<Mesh> mesh)
{
    std::cout << "Selected mesh = " << mesh->getName() << std::endl;
    selectedMesh = mesh;
    UpdateTransformPannel();
}

void AddMeshToModelPannel(AssetManager& assetManager, std::shared_ptr<GLFont> font,
    std::shared_ptr<UIElement> modelPannel, std::shared_ptr<Mesh> mesh, mft::vec2i& pos)
{
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
    pos.y -= 20;
    for (auto child : children)
    {
        AddMeshToModelPannel(assetManager, font, modelPannel, child, pos);
    }
    pos.x -= 20;
}

void UpdateModelPannel( void )
{
  if (selectedObject == nullptr)
    return ;
  AssetManager& assetManager = AssetManager::getInstance();
  std::vector<std::shared_ptr<GLFont>> fonts =
    assetManager.getAssetsOfType<GLFont>();
  std::shared_ptr<GLFont> font = nullptr;
  if (!fonts.empty())
    font = fonts[0];

  std::shared_ptr<UIElement> modelPannel = ui.elements[1]->getChild(1)->getChild(1);
  modelPannel->clearChildren();

  mft::vec2i pos(20, 282);
  AddMeshToModelPannel(assetManager, font, modelPannel, selectedObject->getMeshes()[0], pos);
}

void InitUI()
{
  std::cout << "Initializing UI..." << std::endl;
  AssetManager& assetManager = AssetManager::getInstance();

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

  UIElement modelPannel(mft::vec2i(3, 518),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannel.setSize(mft::vec2i(316, 300));
  modelPannel.visible = false;

  //    Model pannel background
  UIElement modelPannelBackground(mft::vec2i(0, 0),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelBackground.setSize(mft::vec2i(316, 300));
  modelPannelBackground.visible = false;
  for (size_t i = 0; i < 15; i++)
  {
      UIElement slot(mft::vec2i(0, 1 + i * 20),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      slot.setSize(mft::vec2i(316, 19));
      modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(slot)));
  }
  UIElement modelPannelLeftBorder(mft::vec2i(0, 2),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelLeftBorder.setSize(mft::vec2i(20, 298));
  modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelLeftBorder)));
  UIElement modelPannelRightBorder(mft::vec2i(298, 2),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  modelPannelRightBorder.setSize(mft::vec2i(20, 298));
  modelPannelBackground.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannelRightBorder)));

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
  transformBorder.texts.push_back(UIText("Transform", mft::vec2i(90, 10), 16.0f));
  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformBorder)));

  //    Transform pannel
  UIElement transformPannel(mft::vec2i(3, 175),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
  transformPannel.setSize(mft::vec2i(316, 300));

  UIElement transformSlotsBackground(mft::vec2i(20, 100),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"));
  transformSlotsBackground.setSize(mft::vec2i(260, 98));
  for (size_t i = 0; i < 3; i++)
  {
      UIElement slot(mft::vec2i(5, 2 + i * 32),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      slot.setSize(mft::vec2i(98, 30));
      std::string str;
      if (i == 2)
          str = "Location";
      else if (i == 1)
          str = "Rotation";
      else if (i == 0)
          str = "Scale";
      slot.texts.push_back(UIText(str, mft::vec2i(20, 7), 16.0f));
      transformSlotsBackground.addChild(std::shared_ptr<UIElement>(new UIElement(slot)));

      UIElement slot2(mft::vec2i(105, 1 + i * 32),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      slot2.setSize(mft::vec2i(154, 30));

      UIElement X(mft::vec2i(6, 5),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-X.png", "UI"));
      X.setSize(mft::vec2i(40, 20));
      slot2.addChild(std::shared_ptr<UIElement>(new UIElement(X)));

      UIElement Y(mft::vec2i(56, 5),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-Y.png", "UI"));
      Y.setSize(mft::vec2i(40, 20));
      slot2.addChild(std::shared_ptr<UIElement>(new UIElement(Y)));

      UIElement Z(mft::vec2i(106, 5),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-Z.png", "UI"));
      Z.setSize(mft::vec2i(40, 20));
      slot2.addChild(std::shared_ptr<UIElement>(new UIElement(Z)));

      transformSlotsBackground.addChild(std::shared_ptr<UIElement>(new UIElement(slot2)));
  }
  transformPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformSlotsBackground)));

  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannel)));

  //    Right pannel pipe
  UIElement rightPannelRightPipe(mft::vec2i(-2, 180),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
  rightPannelRightPipe.setSize(mft::vec2i(4, 680));
  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(rightPannelRightPipe)));

  ui.registerElement(std::shared_ptr<UIElement>(new UIElement(rightPannel)));

  //  Bottom pannel

  UIElement bottomPannel(mft::vec2i(0, 0));
  bottomPannel.setSize(mft::vec2i(1280, 140));
  ui.registerElement(std::shared_ptr<UIElement>(new UIElement(bottomPannel)));

  UpdateModelPannel();
}
