#pragma once
#include "ButtonBase.h"
#include <easyx.h>
#include <iostream>


class Ordinary_button :
    public ButtonBase
{
private:
	
	
    std::wstring text; // ��ť�ı�
    COLORREF buttonColor; // ��ť��ɫ
    COLORREF textColor; // ��ť�ı���ɫ
    COLORREF borderColor; // ��ť�߿���ɫ
	LPCTSTR fontName; // ��������
    
public:
    
    Ordinary_button(int x, int y, int width, int  height, const std::wstring& text,
        COLORREF newColor1= RGB(245, 204, 132) , COLORREF textColor1= RGB(0, 0, 0),COLORREF borderColor1= RGB(173, 173, 173)
        , LPCTSTR fontName1=L"΢���ź�") :ButtonBase(x, y, width, height),
        text(text), buttonColor(newColor1), textColor(textColor1), borderColor(borderColor1), fontName(fontName1){
    
    
    }

    ~Ordinary_button() {
    }

  //virtual  void changeColo(COLORREF newColor) {
	 // bool colorChanged = false;
  //     // draw();
  //   // ���������ͼ����
  //    if (!colorChanged) {
  //        
  //        colorChanged = true;
  //        // ���������ͼ����
  //        cleardevice();
  //        setfillcolor(newColor); // ��ť�����ɫ
  //        
  //        // ���»��ư�ť��������ɫ
  //      
  //    }
  //      
  //     
  //     
  //  }


    void text_style() {
        setlinestyle(PS_SOLID, 4);
        int fontSize = min(width/text.length(), height);
        setlinecolor(borderColor); // ��ť�߿���ɫ
        setfillcolor(buttonColor); // ��ť�����ɫ
        settextcolor(textColor); // ��ť�ı���ɫ
		solidroundrect(x, y, x + width + 3, y + height + 5, 20, 40);// 
		fillroundrect(x, y, x + width, y + height, 20, 40);// ���ư�ť
        setlinestyle(PS_SOLID, 3);
        setbkmode(TRANSPARENT); // �����ı�����͸��
        settextstyle(fontSize, 0, fontName, 0, 0, 700, 0, 0, 0); // �����ı���С������

        int textX = x + (width - textwidth(text.c_str())) / 2; // �����ı��ڰ�ť�����x����
        int textY = y + (height - textheight(fontName)) / 2; // �����ı��ڰ�ť�����y��
        outtextxy(textX, textY, text.c_str()); // �ڰ�ť�ϻ����ı�
    
    }

    virtual  void draw()override {
    
    
    
        text_style();
    
    
    
    
    
    
    }


};

