#include "HumanGL.hpp"
#include "UI/Button.class.hpp"
#include "UI.hpp"

void InitModelPannel( void )
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
        modelPannelBackground.addChild(std::make_shared<UIElement>(slot));
        UIElement modelPannelLeftBorder(mft::vec2i(0, 1 + i * 32),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
        modelPannelLeftBorder.setSize(mft::vec2i(23, 31));
        modelPannelBackground.addChild(std::make_shared<UIElement>(modelPannelLeftBorder));
        UIElement modelPannelRightBorder(mft::vec2i(288, 1 + i * 32),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
        modelPannelRightBorder.setSize(mft::vec2i(23, 31));
        modelPannelBackground.addChild(std::make_shared<UIElement>(modelPannelRightBorder));
    }
    UIElement modelPannelLeftBorder(mft::vec2i(0, 1),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
    modelPannelLeftBorder.setSize(mft::vec2i(12, 293));
    //modelPannelBackground.addChild(std::make_shared<UIElement>(modelPannelLeftBorder)));
    UIElement modelPannelRightBorder(mft::vec2i(301, 2),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
    modelPannelRightBorder.setSize(mft::vec2i(12, 292));
    //modelPannelBackground.addChild(std::make_shared<UIElement>(modelPannelRightBorder)));
    UIElement modelPannelLeftTop(mft::vec2i(0, 0),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
    modelPannelLeftTop.setSize(mft::vec2i(313, 10));
    //modelPannelBackground.addChild(std::make_shared<UIElement>(modelPannelLeftTop)));
    UIElement modelPannelBottomBorder(mft::vec2i(0, 284),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
    modelPannelBottomBorder.setSize(mft::vec2i(313, 10));
   // modelPannelBackground.addChild(std::make_shared<UIElement>(modelPannelBottomBorder)));

    modelPannel.addChild(std::make_shared<UIElement>(modelPannelBackground));

    UIElement modelPannelSlots(mft::vec2i(0, 0),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
    modelPannelSlots.visible = false;
    modelPannel.addChild(std::make_shared<UIElement>(modelPannelSlots));

    ui.elements[2]->addChild(std::make_shared<UIElement>(modelPannel));

    //  Model border
    UIElement modelBorder(mft::vec2i(2, 800),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
    modelBorder.setSize(mft::vec2i(291, 31));
    modelBorder.texts.push_back(UIText(">  Model", mft::vec2i(12, 6), 20.0f));

    UIElement detailsBorder(mft::vec2i(0, 32),
        assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear-cornered.png", "UI"));
    detailsBorder.setSize(mft::vec2i(100, 26));
    detailsBorder.texts.push_back(UIText("Details", mft::vec2i(14, 6), 16.0f));
    modelBorder.addChild(std::make_shared<UIElement>(detailsBorder));

    ui.elements[2]->addChild(std::make_shared<UIElement>(modelBorder));
}

void PrintArmature(Armature& armature, int& count)
{
    for (int i = 0; i < count; i++)
        std::cout << " ";
    std::cout << armature.name << std::endl;
    for (auto child : armature.children)
    {
        PrintArmature(child, ++count);
    }
    count--;
}

void PrintFullArmature()
{
    int count = 0;
    PrintArmature(rootArmature, count);
}

void FillArmature(Armature& armature, std::shared_ptr<Mesh> mesh)
{
    if (mesh == nullptr)
        return;
    armature = Armature(mesh);
    const std::vector<std::shared_ptr<Mesh>>& children = mesh->getChildren();
    for (const auto& child : children)
    {
        Armature a;
        FillArmature(a, child);
        armature.children.push_back(a);
    }
}

void PopulateArmature()
{
    if (selectedObject == nullptr)
        return;
    FillArmature(rootArmature, selectedObject->getMeshes()[0]);
}

void ClearArmature(Armature& armature)
{
    armature.mesh.reset();
    for (auto& child : armature.children)
    {
        ClearArmature(child);
    }
}

void OpenArmature(Armature& armature)
{
    armature.open = true;
    mustUpdateModelPannel = true;
}

void CloseArmature(Armature& armature)
{
    armature.open = false;
    mustUpdateModelPannel = true;
}

void AddMeshToModelPannel(AssetManager& assetManager, std::shared_ptr<GLFont> font,
    std::shared_ptr<UIElement> modelPannel, Armature& armature, mft::vec2i& pos, int& count)
{
  if (count >= 9)
    return ;
  Button button(pos,
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-rounded-bordered.png", "UI"),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer-rounded-bordered.png", "UI"),
      assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer-rounded-bordered.png", "UI"));
  button.setText(armature.name);
  button.setFont(font);
  button.setAllSizes(mft::vec2i(100, 29));
  std::function<void(std::shared_ptr<Mesh>)> func = SelectMesh;
  std::shared_ptr<ActionWrapper> action =
      std::shared_ptr<ActionWrapper>(new Action<std::shared_ptr<Mesh>>(func, armature.mesh));
  button.onRelease = action;

  modelPannel->addChild(std::make_shared<Button>(button));

  pos.x += 20;
  pos.y -= 32;
  if (armature.open == true && !armature.children.empty())
  {
      Button closeArmatureTabButton(mft::vec2i(pos.x + 80, pos.y + 32),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      closeArmatureTabButton.setText(armature.name);
      closeArmatureTabButton.setFont(font);
      closeArmatureTabButton.setText("-");
      closeArmatureTabButton.setAllSizes(mft::vec2i(30, 30));
      std::function<void(Armature&)> func2 = CloseArmature;
      action = std::shared_ptr<ActionWrapper>(new Action<Armature&>(func2, armature));
      closeArmatureTabButton.onRelease = action;
      modelPannel->addChild(std::make_shared<Button>(closeArmatureTabButton));
      for (auto& child : armature.children)
      {
          AddMeshToModelPannel(assetManager, font, modelPannel, child, pos, ++count);
      }
  }
  else if (armature.open == false)
  {
      Button openArmatureTabButton(mft::vec2i(pos.x + 80, pos.y + 32),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"),
          assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
      openArmatureTabButton.setText(armature.name);
      openArmatureTabButton.setFont(font);
      openArmatureTabButton.setText("+");
      openArmatureTabButton.setAllSizes(mft::vec2i(30, 30));
      std::function<void(Armature&)> func2 = OpenArmature;
      action = std::shared_ptr<ActionWrapper>(new Action<Armature&>(func2, armature));
      openArmatureTabButton.onRelease = action;
      modelPannel->addChild(std::make_shared<Button>(openArmatureTabButton));
  }
  pos.x -= 20;
}

void UpdateModelPannel( void )
{
  if (selectedObject == nullptr)
    return ;
  mustUpdateModelPannel = false;
  AssetManager& assetManager = AssetManager::getInstance();
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

  std::shared_ptr<UIElement> modelPannel = ui.elements[2]->getChild(0)->getChild(1);
  modelPannel->clearChildren();

  mft::vec2i pos(30, 258);
  int count = 0;
  AddMeshToModelPannel(assetManager, font, modelPannel, rootArmature, pos, count);
}
