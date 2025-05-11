#pragma once
#include "MessageDialogBase.h"
#include <easyx.h>
#include <vector>


class MessageDialog 
    : public MessageDialogBase
{
private:

    std::wstring title;       // ��ͷ����
    std::wstring message;     // ��ʾ����Ϣ����
    int titleHeight;          // ��ͷ����߶�
    COLORREF titleBgColor;    // ��ͷ������ɫ
    COLORREF titleTextColor;  // ��ͷ�ı���ɫ
    COLORREF contentBgColor;  // �������򱳾���ɫ
    COLORREF contentTextColor;// �����ı���ɫ
    COLORREF borderColor;     // �߿���ɫ
public:
    // ���캯��

    MessageDialog(int x, int y, int width, int height,
        const std::wstring& title = L"��Ϣ����",
        const std::wstring& initialMessage = L"")
        : MessageDialogBase(x,y, width, height),
        title(title),
        message(initialMessage),
        titleHeight(25) {
        titleBgColor = RGB(220, 220, 255);      // ��ͷ����ɫ - ǳ��ɫ
        titleTextColor = RGB(0, 0, 128);        // ��ͷ�ı�ɫ - ����ɫ
        contentBgColor = RGB(240, 240, 240);    // ���ݱ���ɫ - ǳ��ɫ
        contentTextColor = RGB(0, 0, 0);        // �����ı�ɫ - ��ɫ
        borderColor = RGB(100, 100, 100);       // �߿���ɫ - ���ɫ
    }
    virtual ~MessageDialog() {
    }
    // ������Ϣ����
  virtual  void setMessage(const std::wstring& message) {
        this->message = message;
    }

   
  virtual void setTitle(const std::wstring& title) { 
      this->title = title; 
  }

    // ������Ϣ��ʾ����
    virtual  void draw() override {
        // ��������߿�
        setlinecolor(borderColor);
        rectangle(x, y, x + width, y + height);

        // ���Ʊ�ͷ����
        setfillcolor(titleBgColor);
        solidrectangle(x + 1, y + 1, x + width - 1, y + titleHeight - 1);

        // ���Ʊ�ͷ�ı� (�����)
        settextcolor(titleTextColor);
        settextstyle(14, 0, L"΢���ź�");
        outtextxy(x + 8, y + 6, title.c_str());

        // �����������򱳾�
        setfillcolor(contentBgColor);
        solidrectangle(x + 1, y + titleHeight, x + width - 1, y + height - 1);

        // ���������ı� (�����)
        settextcolor(contentTextColor);
        settextstyle(16, 0, L"΢���ź�");
        outtextxy(x + 8, y + titleHeight + 8, message.c_str());
    }
 
  
};
