#include "HumanGL.hpp"
#include "UI/Button.class.hpp"

void AddMeshToModelPannel(AssetManager& assetManager, std::shared_ptr<GLFont> font,
    std::shared_ptr<UIElement> modelPannel, std::shared_ptr<Mesh> mesh, mft::vec2i& pos)
{
    Button node(pos,
        assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
    node.setText(mesh->getName());
    node.setFont(font);
    node.setAllSizes(mft::vec2i(100, 20));

    modelPannel->addChild(std::shared_ptr<Button>(new Button(node)));
    std::vector<std::shared_ptr<Mesh>> children = mesh->getChildren();
    pos.x += 20;
    pos.y -= 22;
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

  std::shared_ptr<UIElement> modelPannel = ui.elements[1]->getChild(1);
  if (modelPannel == nullptr)
      std::cout << "NULLPTR" << std::endl;
  modelPannel->clearChildren();

  mft::vec2i pos(2, 278);
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

  UIElement rightPannel(mft::vec2i(1280, 0));
  rightPannel.setSize(mft::vec2i(320, 860));
  //  Model border and pannel
  UIElement modelBorder(mft::vec2i(2, 820),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
  modelBorder.setSize(mft::vec2i(260, 40));
  modelBorder.texts.push_back(UIText("Model", mft::vec2i(105, 10), 16.0f));
  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(modelBorder)));
  UIElement modelPannel(mft::vec2i(2, 518),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
  modelPannel.setSize(mft::vec2i(316, 300));
  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(modelPannel)));
  //  Transform border and pannel
  UIElement transformBorder(mft::vec2i(2, 476),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
  transformBorder.setSize(mft::vec2i(260, 40));
  transformBorder.texts.push_back(UIText("Transform", mft::vec2i(90, 10), 16.0f));
  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformBorder)));
  UIElement transformPannel(mft::vec2i(2, 174),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
  transformPannel.setSize(mft::vec2i(316, 300));
  rightPannel.addChild(std::shared_ptr<UIElement>(new UIElement(transformPannel)));
  ui.registerElement(std::shared_ptr<UIElement>(new UIElement(rightPannel)));

  //  Bottom pannel

  UIElement bottomPannel(mft::vec2i(0, 0));
  bottomPannel.setSize(mft::vec2i(1280, 140));
  ui.registerElement(std::shared_ptr<UIElement>(new UIElement(bottomPannel)));

  UpdateModelPannel();
}
