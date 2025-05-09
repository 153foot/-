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
	virtual void draw() = 0; // ���麯�����������ʵ��
	virtual void draw(const std::wstring& basePath, int index);
	virtual bool handleMouseUp();
	virtual void keyInput(wchar_t ch);
	virtual void hotkeydown(BYTE as);
	
	virtual  void changeColo(COLORREF newColor);// �ı䰴ť��ɫ
	virtual void checkMouseOver(int mouseX, int mouseY) ; // �������Ƿ�����
	virtual bool checkClick(int mouseX, int mouseY) ; // ��������
	virtual void onClick() ; // ���ʱ�Ļص�����
	virtual void Mousemove(int mouseX, int mouseY);//����ƶ�
	virtual void doublecheckClick(int mouseX, int mouseY);//˫��
};