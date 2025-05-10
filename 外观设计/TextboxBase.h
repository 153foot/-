#pragma once
#include <string>
#include <wtypes.h>
class TextboxBase
{
protected:
	int x;
	int y;
	int width;
	int height;


public:
	TextboxBase(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
	
	}
	virtual ~TextboxBase() {

	}

	virtual std::wstring getinput() {
		return L" ";
	}
	virtual void draw() = 0;
	virtual bool checkClick(int mouseX, int mouseY) {
		return false;
	}
	virtual bool handleMouseUp() {
		return   false;

	}
	virtual  void hotkeydown(BYTE as) {
	
	}
	virtual  void keyInput(wchar_t ch) {
	}
	virtual  void checkMouseOver(int mouseX, int mouseY) {
	
	}
	virtual  void deselect() {
		
	}
};

