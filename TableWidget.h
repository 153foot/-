#pragma once
#include "TableWidgetBase.h"
#include <easyx.h>
#include <string>
#include <vector>
#include <functional>
using namespace std;

// 表格类
class TableWidget : public TableWidgetBase {
private:
    std::function<void()> callback;
    int visibleRowCount; // 最多可见行数
    int rowHeight;       // 行的高度
    int scrollOffset;    // 垂直滚动偏移
    int horizontalScrollOffset; // 水平滚动偏移
    vector<vector<wstring>> data;
    vector<int> columnWidths; // 列的宽度
    int selectedRow;          // 被选中的行
    int scrollbarWidth;       // 垂直滚动条的宽度
    int handleHeight;         // 垂直滚动条滑块的高度
    int handleY;              // 垂直滚动条滑块的垂直位置
    int horizontalScrollbarHeight; // 水平滚动条的高度
    int horizontalHandleWidth;     // 水平滚动条滑块的宽度
    int horizontalHandleX;         // 水平滚动条滑块的水平位置

    int maxVisibleRows;    // 表格最多显示的行数
    int maxVisibleColumns; // 表格最多显示的列数

    LPCTSTR fontName; // 字体风格
    COLORREF click_bkselect_color; // 单击选中时表格背景颜色
    COLORREF click_textselect_color; // 单击选中时表格文字颜色
    COLORREF noclick_bkselect_color; // 正常表格背景颜色
    COLORREF noclick_textselect_color; // 正常表格中文字颜色
    // 以下是滚动条颜色
    COLORREF scroll_bkbox_color; // 滚动框背景颜色
    COLORREF scroll_bkbar_color; // 滚动条背景颜色

public:
    TableWidget(int x, int y, int width, int height, int visibleRowCount, int maxRows = 10, int maxColumns = 5,
                std::function<void()> cb = []() {}, LPCTSTR font = _T("宋体"),
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

    // 计算每列的宽度
    void calculateColumnWidths() {
        columnWidths.clear();
        if (!data.empty()) {
            columnWidths.resize(data[0].size(), 0);
            for (const auto &row : data) {
                for (size_t j = 0; j < row.size(); ++j) {
                    int width = textwidth(row[j].c_str());
                    if (width > columnWidths[j]) { // 每列的最大宽度（即每列中字符最大长度）
                        columnWidths[j] = width;
                    }
                }
            }
        }
        // 根据每列最大宽度计算该列长度
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
        // 绘制表格区域
        setfillcolor(noclick_bkselect_color);
        solidrectangle(x, y, x + width, y + height);
        setlinecolor(noclick_textselect_color);
        settextstyle(12, 0, fontName);

        // 计算需要绘制的行数和列数
        int rowCount = min(visibleRowCount, min(maxVisibleRows, static_cast<int>(data.size())));
        int startColumn = horizontalScrollOffset;
        int columnCount = min(maxVisibleColumns, static_cast<int>(data[0].size()) - startColumn);

        // 绘制表头
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

        // 绘制表格内容
        for (int i = 1; i < rowCount; ++i) {
            int rowY = y + i * rowHeight;
            int dataIndex = i + scrollOffset;
            columnX = x;
            for (int j = 0; j < columnCount; ++j) {
                int columnWidth = columnWidths[startColumn + j];
                bool isSelectedRow = (dataIndex == selectedRow);
                if (isSelectedRow) { // 选中
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

        // 绘制垂直滚动条背景
        int scrollbarX = x + width;
        setfillcolor(LIGHTGRAY);
        solidrectangle(scrollbarX, y, scrollbarX + scrollbarWidth, y + height);

        // 计算垂直滑块位置和大小
        int handleX = scrollbarX;
        int handleWidth = scrollbarWidth;
        int maxHandleY = height - handleHeight;
        handleY = maxHandleY * double(scrollOffset) / (data.size() - visibleRowCount);

        // 绘制垂直滑块
        setfillcolor(DARKGRAY);
        solidrectangle(handleX, y + handleY, handleX + handleWidth, y + handleY + handleHeight);

        // 绘制水平滚动条背景
        int horizontalScrollbarY = y + height;
        setfillcolor(LIGHTGRAY);
        solidrectangle(x, horizontalScrollbarY, x + width, horizontalScrollbarY + horizontalScrollbarHeight);

        // 计算水平滑块位置和大小
        int maxHorizontalHandleX = width - horizontalHandleWidth;
        horizontalHandleX = maxHorizontalHandleX * double(horizontalScrollOffset) / (columnWidths.size() - 1);

        // 绘制水平滑块
        setfillcolor(DARKGRAY);
        solidrectangle(x + horizontalHandleX, horizontalScrollbarY, x + horizontalHandleX + horizontalHandleWidth,
                       horizontalScrollbarY + horizontalScrollbarHeight);
    }
};
