#include "PageBase.h"

PageBase::~PageBase()
{
}

void PageBase::addButton(std::string name, std::unique_ptr<ButtonBase> button)
{
}

void PageBase::addtexstbox(std::string name, std::shared_ptr<TextboxBase> texstbox)
{
}

void PageBase::addGIF(std::string name, std::shared_ptr<MediaPlayerBase> GIF)
{
}

void PageBase::addTable(std::unique_ptr<TableWidgetBase>& Table)
{
}


void PageBase::addaline()
{
}

void PageBase::addTable(int index, std::unique_ptr<TableWidgetBase> Table)
{
}

void PageBase::draw()
{
}



void PageBase::mouseClick(int mouseX, int mouseY)
{
}

void PageBase::mouseMove(int mouseX, int mouseY)
{
}

void PageBase::mouseWheel(int mouseX, int mouseY, int wheel)
{
}

void PageBase::HandleMouseUp()
{
}

void PageBase::KeyInput(wchar_t ch)
{
}

void PageBase::Hotkeydown(BYTE as)
{
}

 std::wstring PageBase::get_texstbox_message(std::string index)
{
	return std::wstring();
}

 void PageBase::addMessageDialog(std::unique_ptr<MessageDialogBase> messageDialog)
 {
 }



