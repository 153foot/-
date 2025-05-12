#include "TableWidgetBase.h"
#include<vector>
TableWidgetBase::TableWidgetBase(int x, int y, int width, int height)
	:x(x),y(y), width(width), height(height)
{
}

TableWidgetBase::~TableWidgetBase()
{
}

void TableWidgetBase::changeColo(COLORREF newColor)
{
}

void TableWidgetBase::checkMouseOver(int mouseX, int mouseY)
{
}

bool TableWidgetBase::checkClick(int mouseX, int mouseY)
{
	return false;
}

void TableWidgetBase::onClick()
{
}

void TableWidgetBase::Mousemove(int mouseX, int mouseY)
{
}

void TableWidgetBase::doublecheckClick(int mouseX, int mouseY)
{
}

void TableWidgetBase::scroll(int mouseX, int mouseY, int wheel)
{
}

void TableWidgetBase::handleMouseClick(int mouseX, int mouseY)
{
}

void TableWidgetBase::setData(const std::vector <std::vector<std::wstring>> newData)
{
}

