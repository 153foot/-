#pragma once
#include <memory>
#include "ButtonBase.h"
#include "TableWidgetBase.h"

class PageBase
{


public:
	virtual ~PageBase();
	virtual void addButton(std::unique_ptr<ButtonBase> button);

	virtual void addaline();
	virtual void addTable(int index, std::unique_ptr<TableWidgetBase> Table);
	virtual void draw();
	virtual void draw(const std::wstring& basePath, int index);
	virtual void mouseClick(int mouseX, int mouseY);
	virtual void mouseMove(int mouseX, int mouseY);
	virtual  void mouseWheel(int mouseX, int mouseY, int wheel);
	virtual void HandleMouseUp();
	virtual void KeyInput(wchar_t ch);
	virtual void Hotkeydown(BYTE as);

};

