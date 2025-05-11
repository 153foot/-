#pragma once
#include "MessageDialogBase.h"
#include <easyx.h>
#include <vector>


class MessageDialog 
    : public MessageDialogBase
{
private:

    std::wstring title;       // 表头标题
    std::wstring message;     // 显示的消息内容
    int titleHeight;          // 表头区域高度
    COLORREF titleBgColor;    // 表头背景颜色
    COLORREF titleTextColor;  // 表头文本颜色
    COLORREF contentBgColor;  // 内容区域背景颜色
    COLORREF contentTextColor;// 内容文本颜色
    COLORREF borderColor;     // 边框颜色
public:
    // 构造函数

    MessageDialog(int x, int y, int width, int height,
        const std::wstring& title = L"消息标题",
        const std::wstring& initialMessage = L"")
        : MessageDialogBase(x,y, width, height),
        title(title),
        message(initialMessage),
        titleHeight(25) {
        titleBgColor = RGB(220, 220, 255);      // 表头背景色 - 浅蓝色
        titleTextColor = RGB(0, 0, 128);        // 表头文本色 - 深蓝色
        contentBgColor = RGB(240, 240, 240);    // 内容背景色 - 浅灰色
        contentTextColor = RGB(0, 0, 0);        // 内容文本色 - 黑色
        borderColor = RGB(100, 100, 100);       // 边框颜色 - 深灰色
    }
    virtual ~MessageDialog() {
    }
    // 设置消息内容
  virtual  void setMessage(const std::wstring& message) {
        this->message = message;
    }

   
  virtual void setTitle(const std::wstring& title) { 
      this->title = title; 
  }

    // 绘制消息显示区域
    virtual  void draw() override {
        // 绘制整体边框
        setlinecolor(borderColor);
        rectangle(x, y, x + width, y + height);

        // 绘制表头区域
        setfillcolor(titleBgColor);
        solidrectangle(x + 1, y + 1, x + width - 1, y + titleHeight - 1);

        // 绘制表头文本 (左对齐)
        settextcolor(titleTextColor);
        settextstyle(14, 0, L"微软雅黑");
        outtextxy(x + 8, y + 6, title.c_str());

        // 绘制内容区域背景
        setfillcolor(contentBgColor);
        solidrectangle(x + 1, y + titleHeight, x + width - 1, y + height - 1);

        // 绘制内容文本 (左对齐)
        settextcolor(contentTextColor);
        settextstyle(16, 0, L"微软雅黑");
        outtextxy(x + 8, y + titleHeight + 8, message.c_str());
    }
 
  
};
