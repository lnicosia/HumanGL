#include "HumanGL.hpp"
#include "UI/Button.class.hpp"
#include "UI.hpp"

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

  modelPannel->addChild(std::shared_ptr<Button>(new Button(button)));

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
      modelPannel->addChild(std::shared_ptr<Button>(new Button(closeArmatureTabButton)));
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
      modelPannel->addChild(std::shared_ptr<Button>(new Button(openArmatureTabButton)));
  }
  pos.x -= 20;
}

void UpdateModelPannel( void )
{
  if (selectedObject == nullptr)
    return ;
  mustUpdateModelPannel = false;
  AssetManager& assetManager = AssetManager::getInstance();
  std::shared_ptr<GLFont> font =
    assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");

  std::shared_ptr<UIElement> modelPannel = ui.elements[2]->getChild(0)->getChild(1);
  modelPannel->clearChildren();

  mft::vec2i pos(30, 258);
  int count = 0;
  AddMeshToModelPannel(assetManager, font, modelPannel, rootArmature, pos, count);
}
