#pragma once
#include"ButtonBase.h"
#include<string>
#include <functional>
#include <windows.h>
#include <easyx.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <iostream>
#include <sstream>

using namespace std;
class rect_button :
    public ButtonBase
{
private:
   
	int scaledWidth=-1; // ���ź�İ�ť���
	int scaledHeight = -1; // ���ź�İ�ť�߶�
	int scaledX = -1; // ���ź�İ�ťx����
	int scaledY = -1; // ���ź�İ�ťy����

    float scale; // ���ű���������ʵ�������ͣЧ��
    bool isMouseOver; // ��ʾ����Ƿ��ڰ�ť�Ϸ�
	
	COLORREF buttonColor;  // �����ͣʱ��ť�߿���ɫ
	COLORREF textColor; // �����ͣʱ�ı���ɫ
    COLORREF borderColor; // �����ͣʱ��ť�����ɫ

	LPCTSTR fontName; // ������

	COLORREF buttonColor1; // ��ť�߿���ɫ
	COLORREF buttonColor2; // ��ť�����ɫ
    COLORREF textColor1; // ��ť�ı���ɫ
    std::wstring text; // ��ť�ı�
    std::function<void()> callback;
   


private:

    
public:
  //  rect_button(int x, int y, int width, int height, const std:: wstring& text)
		//:ButtonBase(x, y, width, height), text(text), scale(1.0f), isMouseOver(false), 
  //      scaledWidth(0), scaledHeight(0), scaledX(0), scaledY(0) // ��ʼ����ť��x���ꡢy���ꡢ��Ⱥ͸߶�
  //  {
  //      mciSendStringW(L"open .\\soundeffects\\hover.mp3 alias audio", NULL, 0, NULL);
  //      mciSendStringW(L"open .\\soundeffects\\select.mp3 alias audio1", NULL, 0, NULL);
  //  }
    rect_button(int x, int y, int width, int height, const wchar_t* text, const std::function<void()> &callback ,COLORREF mbuttonColor= RGB(255, 189, 225), 
        COLORREF mtextColor= RGB(255, 255, 255), COLORREF mborderColor= RGB(255, 189, 225),LPCTSTR mfontName= _T("����"), COLORREF mbuttonColor1= RGB(173, 173, 173), COLORREF mbuttonColor2= RGB(245, 204, 132), COLORREF mtextColor1= RGB(0, 0, 0))
        :ButtonBase(x, y, width, height), text(text), callback(callback),scale(1.0f), isMouseOver(false),
        scaledWidth(0), scaledHeight(0), scaledX(0), scaledY(0), buttonColor(mbuttonColor), textColor(mtextColor), 
        borderColor(mborderColor), fontName(mfontName), buttonColor1(mbuttonColor1), buttonColor2(mbuttonColor2), textColor1(mtextColor1) {
        mciSendStringW(L"open .\\soundeffects\\hover.mp3 alias audio", NULL, 0, NULL);
        mciSendStringW(L"open .\\soundeffects\\select.mp3 alias audio1", NULL, 0, NULL);
    }

	~rect_button() {
		mciSendStringW(L"close audio", NULL, 0, NULL); // �ر���Ƶ
		mciSendStringW(L"close audio1", NULL, 0, NULL); // �ر���Ƶ
	}



    inline  void music_button_move() {//�����ͣ����Ч
      
       mciSendStringW(L"seek audio to start", NULL, 0, NULL);
       
		mciSendStringW(L"play audio", NULL, 0, NULL); // ������Ч
    
        
    
    }
    void music_button_click() {//�������Ч
       
       
        mciSendStringW(L"seek audio1 to start", NULL, 0, NULL);
       
        mciSendStringW(L"play audio1", NULL, 0, NULL); // ������Ч   
    }
  
  virtual  void checkMouseOver(int mouseX, int mouseY)//��ť���ϻ�����
	{
        bool wasMouseOver = isMouseOver;//if���ھͲ��ڲ�����Ч��
        isMouseOver = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);

        if (isMouseOver) {
           // L".\\soundeffects\\hover.mp3"
            if (!wasMouseOver) {
                music_button_move();
            }
            scale = 0.9f; // �����ͣʱ���Ű�ť
        }
        else {
            // ������Ƶλ�õ���ʼ��

            
            scale = 1.0f; // �ָ���ťԭʼ��С
        }

    }
   
  
     // ���������Ƿ��ڰ�ť�ڣ���ִ�к���
  virtual  bool checkClick(int mouseX, int mouseY)
    {
      
        
		if (isMouseOver)
		{
			callback(); // ִ�а�ť���ʱ�ĺ���
			music_button_click();
			
            //onClick(); // ִ�а�ť���ʱ�ĺ���
            isMouseOver = false;
            scale = 1.0f;
            return true;
        }
        return false;
    }
    

    // ���ư�ť
  virtual  void draw()override
	{
        //static_cast<int>(width * scale);
            scaledWidth = width * scale; // ���ź�İ�ť���
            scaledHeight = height * scale; // ���ź�İ�ť�߶�
             scaledX = x + (width - scaledWidth) / 2; // ���ź�İ�ťx����
             scaledY = y + (height - scaledHeight) / 2; // ���ź�İ�ťy����

        if (isMouseOver)
        {
            setlinecolor(buttonColor); // �����ͣʱ��ť�߿���ɫ
            setfillcolor(borderColor); // �����ͣʱ��ť�����ɫ
			settextcolor(textColor); // �����ͣʱ�ı���ɫ
          
            
			
			
        }
        else
        {
            setlinecolor(buttonColor1); // ��ť�߿���ɫ
            setfillcolor(buttonColor2); // ��ť�����ɫ
			settextcolor(textColor1); // ��ť�ı���ɫ
			
			
        }
        solidroundrect(scaledX, scaledY, scaledX + scaledWidth+3, scaledY + scaledHeight+5,20,40);
       // fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight,20,40); // ���ư�ť
        fillroundrect(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight, 20, 40);
		//void scaledraw();// �������ź�İ�ť
		//rectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight); // ���ư�ť�߿�
       
        setlinestyle(PS_SOLID, 3);
        setbkmode(TRANSPARENT); // �����ı�����͸��
        settextstyle(20 * scale, 0, fontName, 0, 0, 700, 0, 0, 0); // �����ı���С������

        int textX = scaledX + (scaledWidth - textwidth(text.c_str())) / 2; // �����ı��ڰ�ť�����x����
        int textY = scaledY + (scaledHeight - textheight(fontName)) / 2; // �����ı��ڰ�ť�����y��
        outtextxy(textX, textY, text.c_str()); // �ڰ�ť�ϻ����ı�
    }

 
   

};

