#pragma once
#include "ButtonBase.h"
#include <easyx.h>
#include <string>
#include <functional>
#include <windows.h>
#include <iostream>
#include <sstream>

using namespace std;

class TextButton : public ButtonBase {
private:
    std::function<void()> callback;
    float scale; // 缩放比例，用于实现鼠标悬停效果
    bool isMouseOver; // 表示鼠标是否在按钮上方
    std::wstring text; // 按钮文本
    COLORREF textColor; // 鼠标悬停时文本颜色
    COLORREF textColor1; // 正常状态文本颜色
    LPCTSTR fontName; // 字体风格

public:
    TextButton(int x, int y, const std::wstring& text)
        : ButtonBase(x, y, 0, 0), text(text), scale(1.0f), isMouseOver(false),
        textColor(RGB(255, 255, 255)), textColor1(RGB(0, 0, 0)), fontName(_T("宋体")) {
        mciSendStringW(L"open .\\soundeffects\\hover.mp3 alias audio", NULL, 0, NULL);
        mciSendStringW(L"open .\\soundeffects\\select.mp3 alias audio1", NULL, 0, NULL);
    }

    TextButton(int x, int y, const wchar_t* text, const std::function<void()> callback,
        COLORREF mtextColor = RGB(255, 255, 255), COLORREF mtextColor1 = RGB(0, 0, 0),
        LPCTSTR mfontName = _T("宋体"))
        : ButtonBase(x, y, 0, 0), text(text), callback(callback), scale(1.0f), isMouseOver(false),
        textColor(mtextColor), textColor1(mtextColor1), fontName(mfontName) {
        mciSendStringW(L"open .\\soundeffects\\hover.mp3 alias audio", NULL, 0, NULL);
        mciSendStringW(L"open .\\soundeffects\\select.mp3 alias audio1", NULL, 0, NULL);
    }

    ~TextButton() {
        mciSendStringW(L"close audio", NULL, 0, NULL); // 关闭音频
        mciSendStringW(L"close audio1", NULL, 0, NULL); // 关闭音频
    }

    inline void music_button_move() {
        mciSendStringW(L"seek audio to start", NULL, 0, NULL);
        mciSendStringW(L"play audio", NULL, 0, NULL); // 播放音效
    }

    void music_button_click() {
        mciSendStringW(L"seek audio1 to start", NULL, 0, NULL);
        mciSendStringW(L"play audio1", NULL, 0, NULL); // 播放音效
    }

    virtual void checkMouseOver(int mouseX, int mouseY) {
        bool wasMouseOver = isMouseOver;
        int textWidth = textwidth(text.c_str());
        int textHeight = textheight(fontName);
        isMouseOver = (mouseX >= x && mouseX <= x + textWidth && mouseY >= y && mouseY <= y + textHeight);

        if (isMouseOver) {
            if (!wasMouseOver) {
                music_button_move();
            }
            scale = 0.9f; // 鼠标悬停时缩放文本
        }
        else {
            scale = 1.0f; // 恢复文本原始大小
        }
    }

    virtual bool checkClick(int mouseX, int mouseY) {
        if (isMouseOver) {
            callback(); // 执行按钮点击时的函数
            music_button_click();
            isMouseOver = false;
            scale = 1.0f;
            return true;
        }
        return false;
    }

    virtual void draw() override {
        if (isMouseOver) {
            settextcolor(textColor); // 鼠标悬停时文本颜色
        }
        else {
            settextcolor(textColor1); // 正常状态文本颜色
        }

        setbkmode(TRANSPARENT); // 设置文本背景透明
        settextstyle(20 * scale, 0, fontName, 0, 0, 700, 0, 0, 0); // 设置文本大小和字体

        outtextxy(x, y, text.c_str()); // 在指定位置绘制文本
    }
};