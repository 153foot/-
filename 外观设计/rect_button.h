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
   
	int scaledWidth=-1; // 缩放后的按钮宽度
	int scaledHeight = -1; // 缩放后的按钮高度
	int scaledX = -1; // 缩放后的按钮x坐标
	int scaledY = -1; // 缩放后的按钮y坐标

    float scale; // 缩放比例，用于实现鼠标悬停效果
    bool isMouseOver; // 表示鼠标是否在按钮上方
	
	COLORREF buttonColor;  // 鼠标悬停时按钮边框颜色
	COLORREF textColor; // 鼠标悬停时文本颜色
    COLORREF borderColor; // 鼠标悬停时按钮填充颜色

	LPCTSTR fontName; // 字体风格

	COLORREF buttonColor1; // 按钮边框颜色
	COLORREF buttonColor2; // 按钮填充颜色
    COLORREF textColor1; // 按钮文本颜色
    std::wstring text; // 按钮文本
    std::function<void()> callback;
   


private:

    
public:
  //  rect_button(int x, int y, int width, int height, const std:: wstring& text)
		//:ButtonBase(x, y, width, height), text(text), scale(1.0f), isMouseOver(false), 
  //      scaledWidth(0), scaledHeight(0), scaledX(0), scaledY(0) // 初始化按钮的x坐标、y坐标、宽度和高度
  //  {
  //      mciSendStringW(L"open .\\soundeffects\\hover.mp3 alias audio", NULL, 0, NULL);
  //      mciSendStringW(L"open .\\soundeffects\\select.mp3 alias audio1", NULL, 0, NULL);
  //  }
    rect_button(int x, int y, int width, int height, const wchar_t* text, const std::function<void()> &callback ,COLORREF mbuttonColor= RGB(255, 189, 225), 
        COLORREF mtextColor= RGB(255, 255, 255), COLORREF mborderColor= RGB(255, 189, 225),LPCTSTR mfontName= _T("宋体"), COLORREF mbuttonColor1= RGB(173, 173, 173), COLORREF mbuttonColor2= RGB(245, 204, 132), COLORREF mtextColor1= RGB(0, 0, 0))
        :ButtonBase(x, y, width, height), text(text), callback(callback),scale(1.0f), isMouseOver(false),
        scaledWidth(0), scaledHeight(0), scaledX(0), scaledY(0), buttonColor(mbuttonColor), textColor(mtextColor), 
        borderColor(mborderColor), fontName(mfontName), buttonColor1(mbuttonColor1), buttonColor2(mbuttonColor2), textColor1(mtextColor1) {
        mciSendStringW(L"open .\\soundeffects\\hover.mp3 alias audio", NULL, 0, NULL);
        mciSendStringW(L"open .\\soundeffects\\select.mp3 alias audio1", NULL, 0, NULL);
    }

	~rect_button() {
		mciSendStringW(L"close audio", NULL, 0, NULL); // 关闭音频
		mciSendStringW(L"close audio1", NULL, 0, NULL); // 关闭音频
	}



    inline  void music_button_move() {//鼠标悬停是音效
      
       mciSendStringW(L"seek audio to start", NULL, 0, NULL);
       
		mciSendStringW(L"play audio", NULL, 0, NULL); // 播放音效
    
        
    
    }
    void music_button_click() {//鼠标点击音效
       
       
        mciSendStringW(L"seek audio1 to start", NULL, 0, NULL);
       
        mciSendStringW(L"play audio1", NULL, 0, NULL); // 播放音效   
    }
  
  virtual  void checkMouseOver(int mouseX, int mouseY)//按钮在上会缩放
	{
        bool wasMouseOver = isMouseOver;//if还在就不在播放音效了
        isMouseOver = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);

        if (isMouseOver) {
           // L".\\soundeffects\\hover.mp3"
            if (!wasMouseOver) {
                music_button_move();
            }
            scale = 0.9f; // 鼠标悬停时缩放按钮
        }
        else {
            // 重置音频位置到起始点

            
            scale = 1.0f; // 恢复按钮原始大小
        }

    }
   
  
     // 检查鼠标点击是否在按钮内，并执行函数
  virtual  bool checkClick(int mouseX, int mouseY)
    {
      
        
		if (isMouseOver)
		{
			callback(); // 执行按钮点击时的函数
			music_button_click();
			
            //onClick(); // 执行按钮点击时的函数
            isMouseOver = false;
            scale = 1.0f;
            return true;
        }
        return false;
    }
    

    // 绘制按钮
  virtual  void draw()override
	{
        //static_cast<int>(width * scale);
            scaledWidth = width * scale; // 缩放后的按钮宽度
            scaledHeight = height * scale; // 缩放后的按钮高度
             scaledX = x + (width - scaledWidth) / 2; // 缩放后的按钮x坐标
             scaledY = y + (height - scaledHeight) / 2; // 缩放后的按钮y坐标

        if (isMouseOver)
        {
            setlinecolor(buttonColor); // 鼠标悬停时按钮边框颜色
            setfillcolor(borderColor); // 鼠标悬停时按钮填充颜色
			settextcolor(textColor); // 鼠标悬停时文本颜色
          
            
			
			
        }
        else
        {
            setlinecolor(buttonColor1); // 按钮边框颜色
            setfillcolor(buttonColor2); // 按钮填充颜色
			settextcolor(textColor1); // 按钮文本颜色
			
			
        }
        solidroundrect(scaledX, scaledY, scaledX + scaledWidth+3, scaledY + scaledHeight+5,20,40);
       // fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight,20,40); // 绘制按钮
        fillroundrect(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight, 20, 40);
		//void scaledraw();// 绘制缩放后的按钮
		//rectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight); // 绘制按钮边框
       
        setlinestyle(PS_SOLID, 3);
        setbkmode(TRANSPARENT); // 设置文本背景透明
        settextstyle(20 * scale, 0, fontName, 0, 0, 700, 0, 0, 0); // 设置文本大小和字体

        int textX = scaledX + (scaledWidth - textwidth(text.c_str())) / 2; // 计算文本在按钮中央的x坐标
        int textY = scaledY + (scaledHeight - textheight(fontName)) / 2; // 计算文本在按钮中央的y坐
        outtextxy(textX, textY, text.c_str()); // 在按钮上绘制文本
    }

 
   

};

