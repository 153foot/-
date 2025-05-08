#pragma once
#include "TableWidgetBase.h"
#include <easyx.h>
#include <string>
#include <vector>
#include <functional>
using namespace std;

// �����
class TableWidget : public TableWidgetBase {
private:
    std::function<void()> callback;
    int visibleRowCount; // ���ɼ�����
    int rowHeight;       // �еĸ߶�
    int scrollOffset;    // ��ֱ����ƫ��
    int horizontalScrollOffset; // ˮƽ����ƫ��
    vector<vector<wstring>> data;
    vector<int> columnWidths; // �еĿ��
    int selectedRow;          // ��ѡ�е���
    int scrollbarWidth;       // ��ֱ�������Ŀ��
    int handleHeight;         // ��ֱ����������ĸ߶�
    int handleY;              // ��ֱ����������Ĵ�ֱλ��
    int horizontalScrollbarHeight; // ˮƽ�������ĸ߶�
    int horizontalHandleWidth;     // ˮƽ����������Ŀ��
    int horizontalHandleX;         // ˮƽ�����������ˮƽλ��

    int maxVisibleRows;    // ��������ʾ������
    int maxVisibleColumns; // ��������ʾ������

    LPCTSTR fontName; // ������
    COLORREF click_bkselect_color; // ����ѡ��ʱ��񱳾���ɫ
    COLORREF click_textselect_color; // ����ѡ��ʱ���������ɫ
    COLORREF noclick_bkselect_color; // ������񱳾���ɫ
    COLORREF noclick_textselect_color; // ���������������ɫ
    // �����ǹ�������ɫ
    COLORREF scroll_bkbox_color; // �����򱳾���ɫ
    COLORREF scroll_bkbar_color; // ������������ɫ

public:
    TableWidget(int x, int y, int width, int height, int visibleRowCount, int maxRows = 10, int maxColumns = 5,
                std::function<void()> cb = []() {}, LPCTSTR font = _T("����"),
                COLORREF clickBkSelectColor = LIGHTBLUE, COLORREF clickTextSelectColor = RED,
                COLORREF noClickBkSelectColor = WHITE, COLORREF noclick_textselect_color = BLACK,
                COLORREF scroll_bkbox_color = LIGHTGRAY, COLORREF scroll_bkbar_color = DARKGRAY)
        : TableWidgetBase(x, y, width, height), callback(cb), visibleRowCount(visibleRowCount),
          maxVisibleRows(maxRows), maxVisibleColumns(maxColumns), rowHeight(height / visibleRowCount),
          scrollOffset(0), horizontalScrollOffset(0), data({{}}), columnWidths({}), selectedRow(-1),
          scrollbarWidth(20), handleHeight(30), handleY(0), horizontalScrollbarHeight(20),
          horizontalHandleWidth(50), horizontalHandleX(0), fontName(font),
          click_bkselect_color(clickBkSelectColor), click_textselect_color(clickTextSelectColor),
          noclick_bkselect_color(noClickBkSelectColor), noclick_textselect_color(noclick_textselect_color),
          scroll_bkbox_color(scroll_bkbox_color), scroll_bkbar_color(scroll_bkbar_color) {
        data.reserve(200);
        columnWidths.reserve(100);
    }

    virtual ~TableWidget() {}

    int getSelectedRow() const { return selectedRow; }

    wstring getSelectedInfo(int col) const { return data[selectedRow][col]; }

    virtual void setData(const vector<vector<wstring>> &newData) {
        data.clear();
        for (size_t i = 0; i < min(static_cast<size_t>(maxVisibleRows), newData.size()); ++i) {
            vector<wstring> row;
            for (size_t j = 0; j < min(static_cast<size_t>(maxVisibleColumns), newData[i].size()); ++j) {
                row.push_back(newData[i][j]);
            }
            data.push_back(row);
        }
        calculateColumnWidths();
    }

    // ����ÿ�еĿ��
    void calculateColumnWidths() {
        columnWidths.clear();
        if (!data.empty()) {
            columnWidths.resize(data[0].size(), 0);
            for (const auto &row : data) {
                for (size_t j = 0; j < row.size(); ++j) {
                    int width = textwidth(row[j].c_str());
                    if (width > columnWidths[j]) { // ÿ�е�����ȣ���ÿ�����ַ���󳤶ȣ�
                        columnWidths[j] = width;
                    }
                }
            }
        }
        // ����ÿ������ȼ�����г���
        int sumWidth = 0;
        for (auto it : columnWidths)
            sumWidth += it;
        for (auto &it : columnWidths)
            it = (float)it / sumWidth * width;
    }

    void scrollUp() {
        if (scrollOffset > 0) {
            scrollOffset--;
        }
        if (scrollOffset < 0) {
            scrollOffset = 0;
        }
    }

    void scrollDown() {
        int maxScrollOffset = data.size() - visibleRowCount;
        if (scrollOffset < maxScrollOffset) {
            scrollOffset++;
        }
    }

    void scrollLeft() {
        if (horizontalScrollOffset > 0) {
            horizontalScrollOffset--;
        }
    }

    void scrollRight() {
        int maxHorizontalScrollOffset = columnWidths.size() - 1;
        if (horizontalScrollOffset < maxHorizontalScrollOffset) {
            horizontalScrollOffset++;
        }
    }

    virtual void scroll(int mouseX, int mouseY, int wheel) {
        if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height) {
            if (wheel > 0) {
                scrollUp();
            } else if (wheel < 0) {
                scrollDown();
            }
        } else if (mouseY >= y + height && mouseY <= y + height + horizontalScrollbarHeight) {
            if (wheel > 0) {
                scrollLeft();
            } else if (wheel < 0) {
                scrollRight();
            }
        }
    }

    virtual void handleMouseClick(int mouseX, int mouseY) {
        if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height) {
            callback();
            int clickedRow = (mouseY - y) / rowHeight + scrollOffset;

            if (clickedRow >= 0 && clickedRow < static_cast<int>(data.size())) {
                selectedRow = clickedRow;
            } else {
                selectedRow = -1;
            }
        } else if (mouseY >= y + height && mouseY <= y + height + horizontalScrollbarHeight) {
            int clickedPosition = mouseX - x;
            horizontalScrollOffset = clickedPosition * (columnWidths.size() - 1) / width;
        }
    }

    virtual void draw() {
        // ���Ʊ������
        setfillcolor(noclick_bkselect_color);
        solidrectangle(x, y, x + width, y + height);
        setlinecolor(noclick_textselect_color);
        settextstyle(12, 0, fontName);

        // ������Ҫ���Ƶ�����������
        int rowCount = min(visibleRowCount, min(maxVisibleRows, static_cast<int>(data.size())));
        int startColumn = horizontalScrollOffset;
        int columnCount = min(maxVisibleColumns, static_cast<int>(data[0].size()) - startColumn);

        // ���Ʊ�ͷ
        int headerY = y;
        int columnX = x;
        for (int j = 0; j < columnCount; ++j) {
            int columnWidth = columnWidths[startColumn + j];
            rectangle(columnX, headerY, columnX + columnWidth, headerY + rowHeight);

            int textX = columnX + (columnWidth - textwidth(data[0][startColumn + j].c_str())) / 2;
            int textY = headerY + (rowHeight - textheight(fontName)) / 2;
            outtextxy(textX, textY, data[0][startColumn + j].c_str());

            columnX += columnWidth;
        }

        // ���Ʊ������
        for (int i = 1; i < rowCount; ++i) {
            int rowY = y + i * rowHeight;
            int dataIndex = i + scrollOffset;
            columnX = x;
            for (int j = 0; j < columnCount; ++j) {
                int columnWidth = columnWidths[startColumn + j];
                bool isSelectedRow = (dataIndex == selectedRow);
                if (isSelectedRow) { // ѡ��
                    setfillcolor(click_bkselect_color);
                    settextcolor(click_textselect_color);
                } else {
                    setfillcolor(noclick_bkselect_color);
                    settextcolor(noclick_textselect_color);
                }
                fillrectangle(columnX, rowY, columnX + columnWidth, rowY + rowHeight);
                int textX = columnX + (columnWidth - textwidth(data[dataIndex][startColumn + j].c_str())) / 2;
                int textY = rowY + (rowHeight - textheight(fontName)) / 2;
                outtextxy(textX, textY, data[dataIndex][startColumn + j].c_str());
                columnX += columnWidth;
            }
        }

        // ���ƴ�ֱ����������
        int scrollbarX = x + width;
        setfillcolor(LIGHTGRAY);
        solidrectangle(scrollbarX, y, scrollbarX + scrollbarWidth, y + height);

        // ���㴹ֱ����λ�úʹ�С
        int handleX = scrollbarX;
        int handleWidth = scrollbarWidth;
        int maxHandleY = height - handleHeight;
        handleY = maxHandleY * double(scrollOffset) / (data.size() - visibleRowCount);

        // ���ƴ�ֱ����
        setfillcolor(DARKGRAY);
        solidrectangle(handleX, y + handleY, handleX + handleWidth, y + handleY + handleHeight);

        // ����ˮƽ����������
        int horizontalScrollbarY = y + height;
        setfillcolor(LIGHTGRAY);
        solidrectangle(x, horizontalScrollbarY, x + width, horizontalScrollbarY + horizontalScrollbarHeight);

        // ����ˮƽ����λ�úʹ�С
        int maxHorizontalHandleX = width - horizontalHandleWidth;
        horizontalHandleX = maxHorizontalHandleX * double(horizontalScrollOffset) / (columnWidths.size() - 1);

        // ����ˮƽ����
        setfillcolor(DARKGRAY);
        solidrectangle(x + horizontalHandleX, horizontalScrollbarY, x + horizontalHandleX + horizontalHandleWidth,
                       horizontalScrollbarY + horizontalScrollbarHeight);
    }
};
