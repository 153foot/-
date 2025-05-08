#include "ButtonBase.h"

  ButtonBase::ButtonBase(int x, int y, int width, int height)
	: x(x), y(y), width(width), height(height) {
}

  ButtonBase::~ButtonBase() {
}

  void ButtonBase::draw(const std::wstring& basePath, int index)
  {
  }

  bool ButtonBase::handleMouseUp()
  {
	  return false;
  }

  void ButtonBase::keyInput(wchar_t ch)
  {
  }

  void ButtonBase::hotkeydown(BYTE as)
  {
  }



  void ButtonBase::changeColo(COLORREF newColor)
  {
  }

  void ButtonBase::checkMouseOver(int mouseX, int mouseY)
  {
  }

  bool ButtonBase::checkClick(int mouseX, int mouseY)
  {
	  return false;
  }

  void ButtonBase::onClick()
  {
  }

  void ButtonBase::Mousemove(int mouseX, int mouseY)
  {
  }

  void ButtonBase::doublecheckClick(int mouseX, int mouseY)
  {
  }
