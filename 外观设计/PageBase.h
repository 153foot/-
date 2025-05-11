#pragma once
#include "MessageDialogBase.h"
#include "MediaPlayerBase.h"
#include "TextboxBase.h"
#include "ButtonBase.h"

#include "TableWidgetBase.h"
#include <memory>

class PageBase
{


public:
	virtual ~PageBase();
	virtual void addButton(std::string name, std::unique_ptr<ButtonBase> button);
	virtual void addtexstbox(std::string name, std::shared_ptr<TextboxBase>  texstbox);
	virtual void addGIF(std::string name, std::shared_ptr<MediaPlayerBase> GIF);
	virtual void addTable(std::unique_ptr<TableWidgetBase>& Table);
	virtual void addaline();
	virtual void addTable(int index, std::unique_ptr<TableWidgetBase> Table);
	virtual void draw();
	
	virtual void mouseClick(int mouseX, int mouseY);
	virtual void mouseMove(int mouseX, int mouseY);
	virtual  void mouseWheel(int mouseX, int mouseY, int wheel);
	virtual void HandleMouseUp();
	virtual void KeyInput(wchar_t ch);
	virtual void Hotkeydown(BYTE as);
	virtual std::wstring get_texstbox_message(std::string index);
	virtual void addMessageDialog(std::unique_ptr<MessageDialogBase> messageDialog);//添加消息对话框
};

