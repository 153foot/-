#pragma once
#include "ButtonBase.h"
#include <easyx.h>
#include <iostream>


class Ordinary_button :
    public ButtonBase
{
private:
	
	
    std::wstring text; // 按钮文本
    COLORREF buttonColor; // 按钮颜色
    COLORREF textColor; // 按钮文本颜色
    COLORREF borderColor; // 按钮边框颜色
	LPCTSTR fontName; // 字体名称
    
public:
    
    Ordinary_button(int x, int y, int width, int  height, const std::wstring& text,
        COLORREF newColor1= RGB(245, 204, 132) , COLORREF textColor1= RGB(0, 0, 0),COLORREF borderColor1= RGB(173, 173, 173)
        , LPCTSTR fontName1=L"微软雅黑") :ButtonBase(x, y, width, height),
        text(text), buttonColor(newColor1), textColor(textColor1), borderColor(borderColor1), fontName(fontName1){
    
    
    }

    ~Ordinary_button() {
    }

  //virtual  void changeColo(COLORREF newColor) {
	 // bool colorChanged = false;
  //     // draw();
  //   // 清除整个绘图窗口
  //    if (!colorChanged) {
  //        
  //        colorChanged = true;
  //        // 清除整个绘图窗口
  //        cleardevice();
  //        setfillcolor(newColor); // 按钮填充颜色
  //        
  //        // 重新绘制按钮，更改颜色
  //      
  //    }
  //      
  //     
  //     
  //  }


    void text_style() {
        setlinestyle(PS_SOLID, 4);
        int fontSize = min(width/text.length(), height);
        setlinecolor(borderColor); // 按钮边框颜色
        setfillcolor(buttonColor); // 按钮填充颜色
        settextcolor(textColor); // 按钮文本颜色
		solidroundrect(x, y, x + width + 3, y + height + 5, 20, 40);// 
		fillroundrect(x, y, x + width, y + height, 20, 40);// 绘制按钮
        setlinestyle(PS_SOLID, 3);
        setbkmode(TRANSPARENT); // 设置文本背景透明
        settextstyle(fontSize, 0, fontName, 0, 0, 700, 0, 0, 0); // 设置文本大小和字体

        int textX = x + (width - textwidth(text.c_str())) / 2; // 计算文本在按钮中央的x坐标
        int textY = y + (height - textheight(fontName)) / 2; // 计算文本在按钮中央的y坐
        outtextxy(textX, textY, text.c_str()); // 在按钮上绘制文本
    
    }

    virtual  void draw()override {
    
    
    
        text_style();
    
    
    
    
    
    
    }


};

