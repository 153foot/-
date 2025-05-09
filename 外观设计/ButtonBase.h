#pragma once


#include <windows.h>
#include <string>
class ButtonBase
{
protected: 
	int x;
	int y;
	int width;
	int height;
	
public:
	ButtonBase(int x, int y, int width, int height);
	
	virtual ~ButtonBase();
	virtual const std::wstring getinput();
	virtual void draw() = 0; // 纯虚函数，子类必须实现
	virtual void draw(const std::wstring& basePath, int index);
	virtual bool handleMouseUp();
	virtual void keyInput(wchar_t ch);
	virtual void hotkeydown(BYTE as);
	
	virtual  void changeColo(COLORREF newColor);// 改变按钮颜色
	virtual void checkMouseOver(int mouseX, int mouseY) ; // 检查鼠标是否在上
	virtual bool checkClick(int mouseX, int mouseY) ; // 检查鼠标点击
	virtual void onClick() ; // 点击时的回调函数
	virtual void Mousemove(int mouseX, int mouseY);//鼠标移动
	virtual void doublecheckClick(int mouseX, int mouseY);//双击
};