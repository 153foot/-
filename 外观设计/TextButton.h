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
    float scale; // ���ű���������ʵ�������ͣЧ��
    bool isMouseOver; // ��ʾ����Ƿ��ڰ�ť�Ϸ�
    std::wstring text; // ��ť�ı�
    COLORREF textColor; // �����ͣʱ�ı���ɫ
    COLORREF textColor1; // ����״̬�ı���ɫ
    LPCTSTR fontName; // ������

public:
    TextButton(int x, int y, const std::wstring& text)
        : ButtonBase(x, y, 0, 0), text(text), scale(1.0f), isMouseOver(false),
        textColor(RGB(255, 255, 255)), textColor1(RGB(0, 0, 0)), fontName(_T("����")) {
        mciSendStringW(L"open .\\soundeffects\\hover.mp3 alias audio", NULL, 0, NULL);
        mciSendStringW(L"open .\\soundeffects\\select.mp3 alias audio1", NULL, 0, NULL);
    }

    TextButton(int x, int y, const wchar_t* text, const std::function<void()> callback,
        COLORREF mtextColor = RGB(255, 255, 255), COLORREF mtextColor1 = RGB(0, 0, 0),
        LPCTSTR mfontName = _T("����"))
        : ButtonBase(x, y, 0, 0), text(text), callback(callback), scale(1.0f), isMouseOver(false),
        textColor(mtextColor), textColor1(mtextColor1), fontName(mfontName) {
        mciSendStringW(L"open .\\soundeffects\\hover.mp3 alias audio", NULL, 0, NULL);
        mciSendStringW(L"open .\\soundeffects\\select.mp3 alias audio1", NULL, 0, NULL);
    }

    ~TextButton() {
        mciSendStringW(L"close audio", NULL, 0, NULL); // �ر���Ƶ
        mciSendStringW(L"close audio1", NULL, 0, NULL); // �ر���Ƶ
    }

    inline void music_button_move() {
        mciSendStringW(L"seek audio to start", NULL, 0, NULL);
        mciSendStringW(L"play audio", NULL, 0, NULL); // ������Ч
    }

    void music_button_click() {
        mciSendStringW(L"seek audio1 to start", NULL, 0, NULL);
        mciSendStringW(L"play audio1", NULL, 0, NULL); // ������Ч
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
            scale = 0.9f; // �����ͣʱ�����ı�
        }
        else {
            scale = 1.0f; // �ָ��ı�ԭʼ��С
        }
    }

    virtual bool checkClick(int mouseX, int mouseY) {
        if (isMouseOver) {
            callback(); // ִ�а�ť���ʱ�ĺ���
            music_button_click();
            isMouseOver = false;
            scale = 1.0f;
            return true;
        }
        return false;
    }

    virtual void draw() override {
        if (isMouseOver) {
            settextcolor(textColor); // �����ͣʱ�ı���ɫ
        }
        else {
            settextcolor(textColor1); // ����״̬�ı���ɫ
        }

        setbkmode(TRANSPARENT); // �����ı�����͸��
        settextstyle(20 * scale, 0, fontName, 0, 0, 700, 0, 0, 0); // �����ı���С������

        outtextxy(x, y, text.c_str()); // ��ָ��λ�û����ı�
    }
};