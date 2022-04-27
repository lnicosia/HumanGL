#include "HumanGL.hpp"
#include "UI/Button.class.hpp"
#include "UI.hpp"

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
