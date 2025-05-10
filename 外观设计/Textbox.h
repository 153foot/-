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

class Textbox : public TextboxBase
{
private:
    bool isDisplay_content;     // 是否显示文本内容，true显示文本，false显示掩码
    bool isSelected;            // 是否选中
    bool showCursor;            // 是否显示光标
    bool isMouseDown;           // 鼠标左键是否按下

    int MAXword;                // 最大输入字数
    int cursorPos;              // 光标位置
    COLORREF Highlight;         // 高亮显示颜色
    COLORREF selectedTextColor; // 选中文字的颜色
    int mouseHighlightStart;    // 鼠标高亮起始位置
    int mouseHighlightEnd;      // 鼠标高亮结束位置
    int lastMouseX;             // 上一次鼠标的x坐标

    std::wstring text;          // 输入的文字
    std::wstring prompt;        // 提示文字
    std::wstring input;         // 要提取的文字
    std::function<void()> callback;
    // 静态变量（所有实例共享）
     ULONGLONG lastTick;       // 上次闪烁时间戳
     const UINT blinkInterval; // 闪烁间隔（静态常量，建议设为1000ms）
   
private:
    // 获取用于显示的文本（真实文本或掩码）
    std::wstring getDisplayText() const {
        return isDisplay_content ? text : std::wstring(text.length(), L'*');
    }

    // 更新光标闪烁状态
    void updateCursor() {
        
        ULONGLONG currentTick = GetTickCount64();
        if (currentTick - lastTick >= blinkInterval) { // 每500毫秒切换光标状态
            showCursor = !showCursor;
            lastTick = currentTick;
        }
    }

    // 删除选中的文本
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
    Textbox(int x, int y, int width, int height, int MAXword, const std::wstring& prompt, bool isDisplay_content = true)
        : TextboxBase(x, y, width, height),
        MAXword(MAXword),
        isDisplay_content(isDisplay_content),
        isSelected(false),
        showCursor(false),
        cursorPos(0),
        Highlight(RGB(0, 87, 255)),
        selectedTextColor(RGB(199, 147, 246)),
        text(L""),
        mouseHighlightStart(0),
        mouseHighlightEnd(0),
        isMouseDown(false),
        lastMouseX(0),
        prompt(prompt),blinkInterval(500),  // 固定1秒间隔（可改为参数传入）
        lastTick(GetTickCount64())
    {
        //static ULONGLONG lastTick = GetTickCount64();
       
        text.reserve(20);
        input.resize(5, 1);
    }

    ~Textbox() = default;

    virtual std::wstring getinput() {
        this->input = text;
        return input;
    }
  virtual  void deselect() {
        isSelected = false;          // 取消选中标记
        showCursor = false;          // 隐藏光标
        mouseHighlightStart = 0;     // 清除高亮区域
        mouseHighlightEnd = 0;       // 清除高亮区域
        isMouseDown = false;         // 重置鼠标按下状态
        draw();                      // 触发重绘（更新界面显示）
       // FlushBatchDraw();            // 强制刷新绘图（EasyX 双缓冲时需要）
    }
    bool getSelect() const {
        return isSelected;
    }

    bool isEmpty() const {
        return text.empty();
    }

    void clear() {
        text.clear();
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

        // 绘制文本框边框和背景
        if (isSelected) {
            setlinecolor(RGB(239, 136, 190));
        }
        else {
            setlinecolor(RGB(122, 122, 122));
        }
        fillrectangle(x, y, x + width, y + height);

        // 设置文本颜色
        settextcolor(isSelected && showCursor ? RGB(199, 147, 246) : BLACK);
        setbkmode(TRANSPARENT);
        settextstyle(height * 3 / 4, 0, _T("微软雅黑"));

        // 获取显示文本
        const std::wstring displayText = getDisplayText();

        // 绘制高亮部分
        if (mouseHighlightStart != mouseHighlightEnd) {
            int startX = x + 5 + textwidth(displayText.substr(0, min(mouseHighlightStart, mouseHighlightEnd)).c_str());
            int endX = x + 5 + textwidth(displayText.substr(0, max(mouseHighlightStart, mouseHighlightEnd)).c_str());
            int highlightWidth = endX - startX;
            int highlightHeight = height - 4 - height / 4;

            // 创建半透明高亮颜色
            int alpha = 128;
            COLORREF semiTransparentColor = RGB(
                (GetRValue(Highlight) * alpha + GetRValue(WHITE) * (255 - alpha)) / 255,
                (GetGValue(Highlight) * alpha + GetGValue(WHITE) * (255 - alpha)) / 255,
                (GetBValue(Highlight) * alpha + GetBValue(WHITE) * (255 - alpha)) / 255
            );

            setfillcolor(semiTransparentColor);
            solidrectangle(startX, y + 2 + height / 8, startX + highlightWidth, y + 2 + height / 8 + highlightHeight);
        }

        // 绘制文本
        int drawX = x + 5;
        if (mouseHighlightStart > 0) {
            settextcolor(BLACK);
            outtextxy(drawX, y + (height - textheight(_T("微软雅黑"))) / 2,
                displayText.substr(0, min(mouseHighlightStart, mouseHighlightEnd)).c_str());
            drawX += textwidth(displayText.substr(0, min(mouseHighlightStart, mouseHighlightEnd)).c_str());
        }

        if (mouseHighlightStart != mouseHighlightEnd) {
            settextcolor(selectedTextColor);
            outtextxy(drawX, y + (height - textheight(_T("微软雅黑"))) / 2,
                displayText.substr(min(mouseHighlightStart, mouseHighlightEnd),
                    std::abs(mouseHighlightEnd - mouseHighlightStart)).c_str());
            drawX += textwidth(displayText.substr(min(mouseHighlightStart, mouseHighlightEnd),
                std::abs(mouseHighlightEnd - mouseHighlightStart)).c_str());
        }

        if (max(mouseHighlightStart, mouseHighlightEnd) < static_cast<int>(displayText.length())) {
            settextcolor(BLACK);
            outtextxy(drawX, y + (height - textheight(_T("微软雅黑"))) / 2,
                displayText.substr(max(mouseHighlightStart, mouseHighlightEnd)).c_str());
        }

        // 绘制提示文字
        if (text.empty()) {
            settextcolor(RGB(128, 128, 128)); // 淡灰色
            outtextxy(x + 5, y + (height - textheight(_T("微软雅黑"))) / 2, prompt.c_str());
        }

        // 绘制光标
        setlinecolor(RGB(255, 127, 39));
        if (isSelected&& showCursor) {
           
            int cursorX = x + 5 + textwidth(displayText.substr(0, cursorPos).c_str());
            line(cursorX, y + 2 + height / 8, cursorX, y + height * 7 / 8 - 2);
           
        }
    }

    virtual bool checkClick(int mouseX, int mouseY) {
        if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height) {
          
          

            // 根据鼠标位置设置光标位置
            const std::wstring displayText = getDisplayText();
            for (size_t i = 0; i <= displayText.length(); ++i) {
                int posX = x + 5 + textwidth(displayText.substr(0, i).c_str());
                if (mouseX < posX) {
                    cursorPos = static_cast<int>(i);
                    break;
                }
                if (i == displayText.length()) {
                    cursorPos = static_cast<int>(i);
                }
            }
            lastTick = GetTickCount64();  // 重置时间戳，确保立即开始闪烁计时
            // 其他光标位置计算逻辑...
            mouseHighlightStart = cursorPos;
            mouseHighlightEnd = cursorPos;
            isSelected = true;
            isMouseDown = true;
            lastMouseX = mouseX;
           
            return true;
        }
        else {
            this->input = text;
       
            deselect(); // 调用取消选中方法
            isSelected = false;
            showCursor = false;
           // cursorPos = static_cast<int>(text.length());
          
            return false;
        }
    }

    virtual bool handleMouseUp() {
        return isMouseDown = false;
    }

    virtual void hotkeydown(BYTE as) {
        if (as == VK_DELETE) {
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
                    draw();
                    FlushBatchDraw();
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

                                if (text.length() + clipboardText.length() <= MAXword) {
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

    virtual void keyInput(wchar_t ch) {
        if (isSelected) {
            switch (ch) {
            case '\b': // 退格键
                if (!text.empty() && cursorPos > 0) {
                    text.erase(cursorPos - 1, 1);
                    cursorPos--;
                }
                break;

            case '\r': // 回车键
            case '\n':
                cursorPos = static_cast<int>(text.length());
                isSelected = false;
                break;

            default: // 其他字符
                if (ch >= 32 && text.length() < MAXword) { // 过滤控制字符
                    text.insert(cursorPos, 1, ch);
                    cursorPos++;
                }
                break;
            }

            mouseHighlightStart = cursorPos;
            mouseHighlightEnd = cursorPos;
        }
    }

    virtual void checkMouseOver(int mouseX, int mouseY) {
        bool ctrlPressed = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
        if (isSelected && isMouseDown && mouseY >= y && mouseY <= y + height && !ctrlPressed) {
            const std::wstring displayText = getDisplayText();
            for (size_t i = 0; i <= displayText.length(); ++i) {
                int posX = x + 5 + textwidth(displayText.substr(0, i).c_str());
                if (mouseX < posX) {
                    mouseHighlightEnd = static_cast<int>(i);
                    break;
                }
                if (i == displayText.length()) {
                    mouseHighlightEnd = static_cast<int>(i);
                }
            }

            lastMouseX = mouseX;
        }
    }
};