#pragma once

#include "TextboxBase.h"
#include <easyx.h>
#include <string>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <memory>
#include <cwctype>
#include <functional>


// 声明全局变量



class Textbox 
    :public TextboxBase
   
{
private:

    bool isSelected;      // 是否选中
    bool showCursor;      // 是否显示光标
    bool isMouseDown;        // 鼠标左键是否按下

    
    int MAXword;
    int cursorPos;        // 光标位置
    COLORREF Highlight;   // 高亮显示颜色______-初始化为亮蓝色
    COLORREF selctedtext_color; // 选中文字的颜色
    int mouseHighlightStart; // 鼠标高亮起始位置
    int mouseHighlightEnd;   // 鼠标高亮结束位置
    
  
    int lastMouseX;          // 上一次鼠标的 x 坐标
    std::wstring text;       // 输入的文字
    std::wstring prompt;     // 提示文字
    std::wstring input;//要输出的文字
    std::function<void()> callback;
private:
   


    void updateCursor() {
    
        static ULONGLONG lastTick = GetTickCount64();
        ULONGLONG currentTick = GetTickCount64();
        if (currentTick - lastTick >= 500) // 每500毫秒切换光标状态
        {
            showCursor = !showCursor;
            lastTick = currentTick;
        }
    }
    void deleteHighlightedText() {

        if (isSelected && mouseHighlightStart != mouseHighlightEnd) {
            
            // 确保起始位置小于结束位置
            if (mouseHighlightStart > mouseHighlightEnd) {
                std::swap(mouseHighlightStart, mouseHighlightEnd);
            }
            text.erase(mouseHighlightStart, mouseHighlightEnd - mouseHighlightStart);
            cursorPos = mouseHighlightStart;
            mouseHighlightStart = cursorPos;
            mouseHighlightEnd = cursorPos;
        }
    }

public:
    Textbox(int x, int y, int width, int height, int MAXword, const std::wstring& prompt)
        :TextboxBase(x, y, width, height), MAXword(MAXword), isSelected(false), showCursor(false),
        cursorPos(0), Highlight(RGB(0, 87, 255)), selctedtext_color(RGB(199, 147, 246)), text(L""),
        mouseHighlightStart(0), mouseHighlightEnd(0), isMouseDown(false), lastMouseX(0), prompt(prompt)
    {
        text.reserve(20);
        input.resize(5,1);

    }

    ~Textbox() {
    }
   
    
    virtual std::wstring getinput() {
        this->input = text;
        
        
        return input;

    }
    bool getSelect() const {
        return isSelected;
    }

    bool isEmpty() const {
        return text.empty();
    }

    void clear() {
        text = L"";
        cursorPos = 0;
    }
    void setText(const std::wstring& newText) {
        text = newText;
        cursorPos = static_cast<int>(text.length());
    }
    

   virtual void draw() {
        updateCursor();
        setfillcolor(WHITE);
        setlinestyle(PS_SOLID, 2);
        settextstyle(20, 0, _T("微软雅黑"), 0, 0, 700, false, false, false);
        if (isSelected) {
            setlinecolor(RGB(239, 136, 190));
            fillrectangle(x, y, x + width, y + height);

        }
        else {
            setlinecolor(RGB(122, 122, 122));
            fillrectangle(x, y, x + width, y + height);

        }
        if (isSelected && showCursor) {//文本框文字颜色
            settextcolor(RGB(199, 147, 246));
        }
        else {
            settextcolor(BLACK);
        }


        setbkmode(TRANSPARENT);
        settextstyle(height * 3 / 4, 0, _T("微软雅黑"));
        
        // 绘制高亮部分
        if (mouseHighlightStart != mouseHighlightEnd) {
            int startX = x + 5 + textwidth(text.substr(0, min(mouseHighlightStart, mouseHighlightEnd)).c_str());
            int endX = x + 5 + textwidth(text.substr(0, max(mouseHighlightStart, mouseHighlightEnd)).c_str());
            int highlightWidth = endX - startX;
            int highlightHeight = height - 4 - height / 4;

            // 透明度值，范围 0 - 255，这里设置为半透明
            int alpha = 128;
            // 创建一个半透明颜色，这里假设高亮颜色是蓝色
            COLORREF semiTransparentColor = RGB(
                (GetRValue(Highlight) * alpha + GetRValue(WHITE) * (255 - alpha)) / 255,
                (GetGValue(Highlight) * alpha + GetGValue(WHITE) * (255 - alpha)) / 255,
                (GetBValue(Highlight) * alpha + GetBValue(WHITE) * (255 - alpha)) / 255
            );

            setfillcolor(semiTransparentColor);
            solidrectangle(startX, y + 2 + height / 8, startX + highlightWidth, y + 2 + height / 8 + highlightHeight);
        }

        // 绘制文本，区分选中和未选中部分
        int drawX = x + 5;

        if (mouseHighlightStart > 0) {
            settextcolor(BLACK);

            outtextxy(drawX, y + (height - textheight(_T("微软雅黑"))) / 2, text.substr(0, min(mouseHighlightStart, mouseHighlightEnd)).c_str());
            drawX += textwidth(text.substr(0, min(mouseHighlightStart, mouseHighlightEnd)).c_str());
        }
        if (mouseHighlightStart != mouseHighlightEnd) {
            settextcolor(selctedtext_color);
            outtextxy(drawX, y + (height - textheight(_T("微软雅黑"))) / 2, text.substr(min(mouseHighlightStart, mouseHighlightEnd), std::abs(mouseHighlightEnd - mouseHighlightStart)).c_str());
            drawX += textwidth(text.substr(min(mouseHighlightStart, mouseHighlightEnd), std::abs(mouseHighlightEnd - mouseHighlightStart)).c_str());
        }
        if (max(mouseHighlightStart, mouseHighlightEnd) < static_cast<int>(text.length())) {
            settextcolor(BLACK);
            outtextxy(drawX, y + (height - textheight(_T("微软雅黑"))) / 2, text.substr(max(mouseHighlightStart, mouseHighlightEnd)).c_str());
        }

        // 绘制提示文字
        if (text.empty()) {
            settextcolor(RGB(128, 128, 128)); // 淡灰色
            outtextxy(x + 5, y + (height - textheight(_T("微软雅黑"))) / 2, prompt.c_str());
        }

        setlinecolor(RGB(255, 127, 39)); // 绘制光标
        if (isSelected && showCursor) {
            int cursorX = x + 5 + textwidth(text.substr(0, cursorPos).c_str());
            line(cursorX, y + 2 + height / 8, cursorX, y + height * 7 / 8 - 2);
        }
    }

   
   virtual bool checkClick(int mouseX, int mouseY) {
        if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height) {
           
          
            isSelected = true;
            // 根据鼠标位置设置光标位置
            for (size_t i = 0; i <= text.length(); ++i) {
                int posX = x + 5 + textwidth(text.substr(0, i).c_str());
                if (mouseX < posX) {
                    cursorPos = static_cast<int>(i);
                    break;
                }
                if (i == text.length()) {
                    cursorPos = static_cast<int>(i);
                }
            }
            mouseHighlightStart = cursorPos;
            mouseHighlightEnd = cursorPos;
            isMouseDown = true;
            lastMouseX = mouseX;
            return true;
        }
        else {

            draw();
            this->input = text;
            isSelected = false;
            cursorPos = static_cast<int>(text.length());
            mouseHighlightStart = 0;
            mouseHighlightEnd = 0;
            isMouseDown = false;
            return false;
        }
    }

   virtual bool handleMouseUp() {
      return  isMouseDown = false;
        
    }

  
    virtual  void hotkeydown(BYTE as) {

        if ( as == VK_DELETE) {
           deleteHighlightedText();
        }
        bool shiftPressed = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
        bool ctrlPressed = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
        if (isSelected) {
            switch (as) {
            case VK_LEFT:
                if (shiftPressed) {
                    if (cursorPos > 0) {
                        cursorPos--;
                        if (cursorPos < mouseHighlightStart) {
                            mouseHighlightStart = cursorPos;
                        }
                        else if (cursorPos < mouseHighlightEnd) {
                            mouseHighlightEnd = cursorPos;
                        }
                    }
                }
                else {
                    if (cursorPos > 0) {
                        cursorPos--;
                        mouseHighlightStart = cursorPos;
                        mouseHighlightEnd = cursorPos;
                    }
                }
                break;
            case VK_RIGHT:
                if (shiftPressed) {
                    if (cursorPos < static_cast<int>(text.length())) {
                        cursorPos++;
                        if (cursorPos > mouseHighlightEnd) {
                            mouseHighlightEnd = cursorPos;
                        }
                        else if (cursorPos > mouseHighlightStart) {
                            mouseHighlightStart = cursorPos;
                        }
                    }
                }
                else {
                    if (cursorPos < static_cast<int>(text.length())) {
                        cursorPos++;
                        mouseHighlightStart = cursorPos;
                        mouseHighlightEnd = cursorPos;
                    }
                }
                break;
            case 'A':
                if (ctrlPressed) {
                    mouseHighlightStart = 0;
                    mouseHighlightEnd = static_cast<int>(text.length());
                    cursorPos = mouseHighlightEnd;
                    draw(); // 立即更新绘制
                    FlushBatchDraw(); // 强制刷新
                }
                break;
            case 'C':
                if (ctrlPressed) {
                    if (mouseHighlightStart != mouseHighlightEnd) {
                        // 确保起始位置小于结束位置
                        if (mouseHighlightStart > mouseHighlightEnd) {
                            std::swap(mouseHighlightStart, mouseHighlightEnd);
                        }
                        std::wstring selectedText = text.substr(mouseHighlightStart, mouseHighlightEnd - mouseHighlightStart);
                        if (OpenClipboard(nullptr)) {
                            EmptyClipboard();
                            HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, (selectedText.length() + 1) * sizeof(wchar_t));
                            if (hGlobal) {
                                wchar_t* pText = static_cast<wchar_t*>(GlobalLock(hGlobal));
                                if (pText) {
                                    wcscpy_s(pText, selectedText.length() + 1, selectedText.c_str());
                                    GlobalUnlock(hGlobal);
                                    SetClipboardData(CF_UNICODETEXT, hGlobal);
                                }
                                else {
                                    GlobalFree(hGlobal);
                                }
                            }
                            CloseClipboard();
                        }
                    }
                }
                break;
            case 'V':
                if (ctrlPressed) {
                    if (OpenClipboard(nullptr)) {

                        HGLOBAL hGlobal = static_cast<HGLOBAL>(GetClipboardData(CF_UNICODETEXT));
                        if (hGlobal) {
                            wchar_t* pText = static_cast<wchar_t*>(GlobalLock(hGlobal));

                            if (pText) {


                                std::wstring clipboardText(pText);

                                GlobalUnlock(hGlobal);

                                if (mouseHighlightStart != mouseHighlightEnd) {
                                    // 确保起始位置小于结束位置
                                    if (mouseHighlightStart > mouseHighlightEnd) {
                                        std::swap(mouseHighlightStart, mouseHighlightEnd);
                                    }
                                    text.erase(mouseHighlightStart, mouseHighlightEnd - mouseHighlightStart);
                                }
                                if (std::abs(mouseHighlightEnd - mouseHighlightStart) == text.length()) {
                                    text.swap(clipboardText);



                                }
                                if (text.length() + clipboardText.length() <= MAXword) {
                                    if (text.empty()) {
                                        text.insert(0, clipboardText);


                                    }
                                    text.insert(cursorPos, clipboardText);
                                    cursorPos += static_cast<int>(clipboardText.length());

                                }
                                mouseHighlightStart = cursorPos;
                                mouseHighlightEnd = cursorPos;

                            }
                        }
                        CloseClipboard();
                    }
                }
                break;
            default:
                break;
            }
        }
    }
   

    virtual  void keyInput(wchar_t ch) {
        if (isSelected) {
            switch (ch) {
            case '\b':                // 用户按退格键，删掉一个字符
                if (!text.empty() && cursorPos > 0) {
                    text.erase(cursorPos - 1, 1);
                    cursorPos--;
                }
                break;
            case '\r':
            case '\n':

                cursorPos = static_cast<int>(text.length());
                isSelected = false;
                break;

            default:                // 用户按其它键，接受文本输入


                if (!(ch >= 0 && ch <= 31)) {//去除控制字符  Ctrl+A 

                    if (text.length() < MAXword) {
                        text.insert(cursorPos, 1, ch);
                        cursorPos++;
                    }
                }
            }
            mouseHighlightStart = cursorPos;
            mouseHighlightEnd = cursorPos;
        }
    }


    virtual  void checkMouseOver(int mouseX, int mouseY) {
        bool ctrlPressed = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
        if (isSelected && isMouseDown && mouseY >= y && mouseY <= y + height && !ctrlPressed) {
            for (size_t i = 0; i <= text.length(); ++i) {
                int posX = x + 5 + textwidth(text.substr(0, i).c_str());
                if (mouseX < posX) {
                    mouseHighlightEnd = static_cast<int>(i);
                    break;
                }
                if (i == text.length()) {
                    mouseHighlightEnd = static_cast<int>(i);
                }
            }


            if (mouseX < lastMouseX) { // 鼠标左移
                if (mouseHighlightEnd < mouseHighlightStart) {
                    mouseHighlightEnd = mouseHighlightEnd;
                }
            }
            else if (mouseX > lastMouseX) { // 鼠标右移
                if (mouseHighlightEnd > mouseHighlightStart) {
                    mouseHighlightEnd = mouseHighlightEnd;
                }
            }

            lastMouseX = mouseX;
        }
    }
  
   

};
