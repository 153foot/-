#include "PageBase.h"

PageBase::~PageBase()
{
}

void PageBase::addButton(std::unique_ptr<ButtonBase> button)
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

void PageBase::draw(const std::wstring& basePath, int index)
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
