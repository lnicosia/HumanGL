#include "HumanGL.hpp"

void InitUI()
{
  UIElement topPannel(mft::vec2i(0, 860));
  topPannel.setSize(mft::vec2i(1280, 40));
  topPannel.texts.push_back(UIText("Bobby", mft::vec2i(790, 10), 0.5f));
  ui.registerElement(std::shared_ptr<UIElement>(new UIElement(topPannel)));

  UIElement rightPannel(mft::vec2i(1280, 0));
  rightPannel.setSize(mft::vec2i(320, 900));
  ui.registerElement(std::shared_ptr<UIElement>(new UIElement(rightPannel)));

  UIElement bottomPannel(mft::vec2i(0, 0));
  bottomPannel.setSize(mft::vec2i(1600, 140));
  ui.registerElement(std::shared_ptr<UIElement>(new UIElement(bottomPannel)));
}
