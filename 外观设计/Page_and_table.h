#pragma once
#include "PageBase.h"
#include "TableWidget.h"
#include <easyx.h>
#include <vector>

class Page_and_table : public PageBase {
private:
    IMAGE* pageImage;
    std::vector<std::unique_ptr<ButtonBase>> buttons;
    std::vector<std::unique_ptr<TableWidgetBase>> tables;
    int tableIndex;
    int width;
    int height;

public:
    Page_and_table(int width, int height, const wchar_t* imagePath);


       virtual ~Page_and_table();

    void addButton(std::unique_ptr<ButtonBase> button) {
        if (buttons.size() == buttons.capacity()) {
            buttons.reserve(buttons.size() * 2);
        }
        buttons.push_back(std::move(button));
    }

    void addTable(std::unique_ptr<TableWidgetBase>& Table) {
        if (tables.size() == tables.capacity()) {
            tables.reserve(tables.size() * 2);
        }
        tables.push_back(std::move(Table));
    }

    virtual void draw() {
        if (pageImage != nullptr) {
            putimage(0, 0, pageImage);
        }
        if (!tables.empty()) {
            for (const auto& table : tables) {
                if (table) {
                    table->draw();
                }
            }
        }
        if (!buttons.empty()) {
            for (auto& button : buttons) {
                button->draw();
            }
        }
    }

    virtual void mouseClick(int mouseX, int mouseY) {
        for (auto& button : buttons) {
            if (button->checkClick(mouseX, mouseY)) {
                break;
            }
        }
        for (const auto& table : tables) {
            if (table) {
                table->handleMouseClick(mouseX, mouseY);
            }
        }
    }

    virtual void mouseMove(int mouseX, int mouseY) {
        for (auto& button : buttons) {
            button->checkMouseOver(mouseX, mouseY);
        }
    }

    virtual void mouseWheel(int mouseX, int mouseY, int wheel) {
        for (const auto& table : tables) {
            if (table) {
                table->scroll(mouseX, mouseY, wheel);
            }
        }
    }

    void maketable(std::unique_ptr<TableWidgetBase> tablePtr) {
        tablePtr->setData({
            {L"�ID", L"�����", L"��ʼʱ��", L"����ʱ��", L"�����", L"�����", L"��������", L"�״̬"},
            {L"1", L"���������ػ�", L"2025-07-01 00:00:00", L"2025-07-31 23:59:59", L"ȫ����Ʒ 8 ���Ż�", L"ֱ���ڽ���ʱ�����ۿ�", L"��", L"δ��ʼ"},
            {L"2", L"��Աר������", L"2025-05-15 00:00:00", L"2025-05-31 23:59:59", L"��Ա������ 500 �� 100", L"��Ա��������ѽ��ﵽҪ��", L"��Ա�û�", L"�ѽ���"},
            {L"3", L"���û�ע������", L"2025-06-01 00:00:00", L"2025-06-30 23:59:59", L"���û�ע���;�����Ʒһ��", L"�ɹ�ע�����û�������ȡ", L"��ע���û�", L"�ѽ���"},
            {L"4", L"����񻶴��", L"2025-10-01 00:00:00", L"2025-10-07 23:59:59", L"������Ʒ 7 ����", L"����ָ����Ʒ�������ۿ�", L"��", L"δ��ʼ"},
            {L"5", L"����ж�����", L"2025-08-18 00:00:00", L"2025-08-20 23:59:59", L"������ 200 Ԫ�ɲ���齱", L"���ݳ齱��������Ӧ��Ʒ", L"������ 200 Ԫ", L"δ��ʼ"},
            {L"6", L"����ů���ײ�", L"2025-12-01 00:00:00", L"2025-12-31 23:59:59", L"�Ƴ�������ɫ�ײ�", L"ֱ�ӹ����ײͼ���", L"��", L"δ��ʼ"},
            {L"7", L"���˽������ػ�", L"2025-02-14 00:00:00", L"2025-02-15 23:59:59", L"������Ʒ 9 ���Ż�", L"����˫����ͬ������Ʒ�������ۿ�", L"�����û�", L"�ѽ���"},
            {L"8", L"ĸ�׽ڸж��ػ�", L"2025-05-11 00:00:00", L"2025-05-12 23:59:59", L"������ 300 ���ʻ�һ��", L"���ѽ��ﵽҪ�󼴿ɻ���", L"��", L"�ѽ���"},
            {L"9", L"��ѧ�����Ż�", L"2025-09-01 00:00:00", L"2025-09-10 23:59:59", L"ѧ����Ʒ 8.5 ��", L"ƾѧ��֤����ѧ����Ʒ�������ۿ�", L"ѧ���û�", L"δ��ʼ"},
            {L"10", L"ʥ���ھ�ϲ�", L"2025-12-25 00:00:00", L"2025-12-26 23:59:59", L"������ 100 �ɲ���齱", L"���ݳ齱��������Ӧ��Ʒ", L"������ 100 Ԫ", L"δ��ʼ"}
            });
        addTable(tablePtr);
        tableIndex = 0;
    }
};