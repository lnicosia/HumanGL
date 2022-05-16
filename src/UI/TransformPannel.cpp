#include "HumanGL.hpp"
#include "UI/Button.class.hpp"
#include "UI.hpp"

void InitTransformPannel( void )
{
    AssetManager& assetManager = AssetManager::getInstance();

    std::vector<std::shared_ptr<GLFont>> fonts =
        assetManager.getAssetsOfType<GLFont>();
#ifdef USING_EXTERNAL_LIBS
    std::shared_ptr<GLFont> font =
        assetManager.loadAsset<GLFont>("resources/fonts/arial.tff");
    std::shared_ptr<GLFont> font12 =
        assetManager.loadAsset<GLFont>("resources/fonts/arial.tff");
#else
    std::shared_ptr<GLFont> font =
        assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");
    std::shared_ptr<GLFont> font12 =
        assetManager.loadAsset<GLFont>("resources/fonts/pt-sans-48.bff");
#endif

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
        transformPannel.addChild(std::make_shared<UIElement>(transformPannelSlot1));
        UIElement transformPannelSlot2(mft::vec2i(17, i * 35 + 65),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
        transformPannelSlot2.setSize(mft::vec2i(98, 34));
        if (i == 2)
            transformPannelSlot2.texts.push_back(UIText("Color", mft::vec2i(10, 10), 16.0f));
        transformPannel.addChild(std::make_shared<UIElement>(transformPannelSlot2));
        UIElement transformPannelSlot3(mft::vec2i(116, i * 35 + 65),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
        transformPannelSlot3.setSize(mft::vec2i(185, 34));
        transformPannel.addChild(std::make_shared<UIElement>(transformPannelSlot3));
        UIElement transformPannelSlot3bis(mft::vec2i(302, i * 35 + 65),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-clear.png", "UI"));
        transformPannelSlot3bis.setSize(mft::vec2i(11, 34));
        transformPannel.addChild(std::make_shared<UIElement>(transformPannelSlot3bis));
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
        transformSlotsBackground.addChild(std::make_shared<UIElement>(slot));

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
            slot2.addChild(std::make_shared<UIElement>(N));

            Button button(mft::vec2i(49 + 60 * j, 17),
                assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"),
                assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"),
                assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
            button.setText("+");
            //button.setPos(mft::vec2i(49 + 60 * j, 16));
            button.setFont(font12);
            button.setAllSizes(mft::vec2i(15, 15));
            slot2.addChild(std::make_shared<Button>(button));


            button.setPos(mft::vec2i(49 + 60 * j, 3));
            button.setText("-");
            button.setFont(font12);
            button.setAllSizes(mft::vec2i(15, 15));
            slot2.addChild(std::make_shared<Button>(button));
        }
        transformSlotsBackground.addChild(std::make_shared<UIElement>(slot2));
    }
    transformPannel.addChild(std::make_shared<UIElement>(transformSlotsBackground));

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
        colorPannelSlot.addChild(std::make_shared<UIElement>(N));

        Button button(mft::vec2i(53 + 68 * j, 16),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI.png", "UI"),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"),
            assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
        button.setText("+");
        button.setFont(font12);
        button.setAllSizes(mft::vec2i(14, 14));
        colorPannelSlot.addChild(std::make_shared<Button>(button));


        button.setPos(mft::vec2i(53 + 68 * j, 2));
        button.setText("-");
        button.setFont(font12);
        button.setAllSizes(mft::vec2i(14, 14));
        colorPannelSlot.addChild(std::make_shared<Button>(button));
    }
    colorPannel.addChild(std::make_shared<UIElement>(colorPannelSlot));

    transformPannel.addChild(std::make_shared<UIElement>(colorPannel));

    ui.elements[2]->addChild(std::make_shared<UIElement>(transformPannel));

    UIElement transformBorder(mft::vec2i(2, 477),
    assetManager.loadAsset<Texture>("resources/UI/defaultUI-clearer.png", "UI"));
    transformBorder.setSize(mft::vec2i(304, 34));
    transformBorder.texts.push_back(UIText(">  Mesh", mft::vec2i(12, 6), 20.0f));
    ui.elements[2]->addChild(std::make_shared<UIElement>(transformBorder));
}

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
  std::shared_ptr<UIElement> colorPannel = ui.elements[2]->getChild(2)->getChild(33)->getChild(0);

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
  std::shared_ptr<UIElement> transformPannel = ui.elements[2]->getChild(2)->getChild(32);

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
  std::shared_ptr<UIElement> colorPannel = ui.elements[2]->getChild(2)->getChild(33)->getChild(0);
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

  UpdateColorPannelButtons();
}

void UpdateTransformPannel( void )
{
                                                  // rightP     / transformP / backgroundP
    std::shared_ptr<UIElement> transformPannel = ui.elements[2]->getChild(2)->getChild(32);
    ui.elements[2]->getChild(2)->getChild(25)->texts.clear();
    ui.elements[2]->getChild(2)->getChild(25)->texts.push_back(
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

    UpdateTransformPannelButtons();
}
