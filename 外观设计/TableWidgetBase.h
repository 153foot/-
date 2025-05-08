#pragma once
#include <windows.h>
#include<vector>
#include<string>
class TableWidgetBase
{
	protected:
	int x;
	int y;
	int width;
	int height;
	

public:
	TableWidgetBase(int x, int y, int width, int height);
	virtual ~TableWidgetBase();
	virtual void draw() = 0; // ���麯�����������ʵ��
	virtual  void changeColo(COLORREF newColor);// �ı䰴ť��ɫ
	virtual void checkMouseOver(int mouseX, int mouseY); // ��������ͣ
	virtual bool checkClick(int mouseX, int mouseY); // ��������
	virtual void onClick(); // ���ʱ�Ļص�����
	virtual void Mousemove(int mouseX, int mouseY);//����ƶ�
	virtual void doublecheckClick(int mouseX, int mouseY);//˫��
	virtual void scroll(int mouseX, int mouseY, int wheel);
	virtual void handleMouseClick(int mouseX, int mouseY);
	virtual void setData(const std:: vector<std::vector<std::wstring>>& newData);

	
};

