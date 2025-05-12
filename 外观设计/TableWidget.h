#include "TableWidgetBase.h"
#include <vector>
#include <string>
#include "functional"
#include <algorithm>
#include <easyx.h>
class TableWidget 
    : public TableWidgetBase {
private:
    int visibleRowCount; // ���ɼ�����
    int rowHeight;       // ��
    int scrollOffset;    // ��ֱ����ƫ��
    std::vector<std::vector<std::wstring>> data;
    std::vector<int> columnWidths; // �еĿ��
    int selectedRow;          // ��ѡ�е���
    int scrollbarWidth;       // ��ֱ�������Ŀ��
    int handleHeight;         // ��ֱ����������ĸ߶�
    int handleY;              // ��ֱ����������Ĵ�ֱλ��

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
    std::function<void()> callback;
    const int textPadding = 1; // ��������ļ�࣬�޸�Ϊ 1 ����
    const int scrollStep = 10; // ÿ�ι�����������

public:
    TableWidget(int x, int y, int width, int height, int visibleRowCount, int maxRows = 10, int maxColumns = 5,
        std::function<void()> cb = []() {}, LPCTSTR font = _T("����"),
        COLORREF clickBkSelectColor = LIGHTBLUE, COLORREF clickTextSelectColor = RED,
        COLORREF noClickBkSelectColor = WHITE, COLORREF noclick_textselect_color = BLACK,
        COLORREF scroll_bkbox_color = LIGHTGRAY, COLORREF scroll_bkbar_color = DARKGRAY)
        : TableWidgetBase(x, y, width, height), callback(cb), visibleRowCount(visibleRowCount),
        maxVisibleRows(maxRows), maxVisibleColumns(maxColumns), rowHeight(height / visibleRowCount),
        scrollOffset(0), data({ {} }), columnWidths({}), selectedRow(-1),
        scrollbarWidth(20), handleHeight(30), handleY(0), fontName(font),
        click_bkselect_color(clickBkSelectColor), click_textselect_color(clickTextSelectColor),
        noclick_bkselect_color(noClickBkSelectColor), noclick_textselect_color(noclick_textselect_color),
        scroll_bkbox_color(scroll_bkbox_color), scroll_bkbar_color(scroll_bkbar_color) {
        data.reserve(200);
        columnWidths.reserve(100);
    }

    virtual ~TableWidget() {}

    virtual  std::vector<std::vector<std::wstring>>& getData()  { return this->data; }

    std::wstring getSelectedInfo(int col) const { return data[selectedRow][col]; }

    // ���ñ������
    virtual void setData(const std::vector<std::vector<std::wstring>> newData) {
        data.clear();
        for (size_t i = 0; i < newData.size(); ++i) {
            std::vector<std::wstring> row;
            for (size_t j = 0; j < newData[i].size(); ++j) {
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
            for (const auto& row : data) {
                for (size_t j = 0; j < row.size(); ++j) {
                    int width = textwidth(row[j].c_str());
                    if (width > columnWidths[j]) { // ÿ�е�����ȣ���ÿ�����ַ���󳤶ȣ�
                        columnWidths[j] = width;
                    }
                }
            }
            // ���������뵥Ԫ��ļ��
            for (auto& width : columnWidths) {
                width += 2 * textPadding;
            }
        }
        // ����ÿ������ȼ�����г���
        int sumWidth = 0;
        for (auto it : columnWidths)
            sumWidth += it;
        for (auto& it : columnWidths)
            it = (float)it / sumWidth * (width - scrollbarWidth); // ��ȥ��ֱ���������
    }

    // ���Ϲ���
    void scrollUp() {
        if (scrollOffset > 0) {
            scrollOffset = max(0, scrollOffset - scrollStep);
        }
    }

    // ���¹���
    void scrollDown() {
        int totalHeight = data.size() * rowHeight;
        int maxScrollOffset = max(0, totalHeight - height + rowHeight);
        // ȷ������ƫ�������ᳬ�����ɹ�����Χ
        if (scrollOffset < maxScrollOffset) {
            scrollOffset = min(maxScrollOffset, scrollOffset + scrollStep);
        }
    }
    virtual size_t Cell_num() {

       return data.size();
    }

    // ����������
    virtual void scroll(int mouseX, int mouseY, int wheel) {
        if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height) {
            if (wheel > 0) {
                scrollUp();
            }
            else if (wheel < 0) {
                scrollDown();
            }
        }
    }

    // ���������
    virtual void handleMouseClick(int mouseX, int mouseY) {
        int clickedRow = (mouseY - y + scrollOffset) / rowHeight;
        if (mouseX >= x && mouseX <= x + width - scrollbarWidth && mouseY >= y && mouseY <= y + height) {
            callback();
         

            if (clickedRow >= 0 && clickedRow < static_cast<int>(data.size())) {
                selectedRow = clickedRow;
            }
            else {
                selectedRow = -1;
            }
        }
        else {
           
            selectedRow = -1;
        }
    }

    // ���Ʊ��
    virtual void draw() {
        // ���Ʊ������
        setlinestyle(PS_SOLID, 2);
        setfillcolor(noclick_bkselect_color);
        solidrectangle(x, y, x + width, y + height);
        setlinecolor(noclick_textselect_color);
        settextstyle(12, 0, fontName);

        // ��ȡ������������
        int totalRows = static_cast<int>(data.size());
        int totalColumns = data.empty() ? 0 : static_cast<int>(data[0].size());

        // ������Ҫ���Ƶ�����������
        int firstVisibleRow = scrollOffset / rowHeight;
        int lastVisibleRow = min(totalRows, firstVisibleRow + visibleRowCount + (scrollOffset % rowHeight > 0 ? 1 : 0));

        // ���Ʊ�ͷ
        int headerY = y;
        int columnX = x;
        // ���ñ�ͷ�ü�����ȷ����ͷ�̶��Ҳ��������Χ
        HRGN headerClipRegion = CreateRectRgn(x, y, x + width, y + rowHeight);
        SelectClipRgn(GetImageHDC(), headerClipRegion);
        for (int j = 0; j < totalColumns; ++j) {
            int columnWidth = columnWidths[j];
            rectangle(columnX, headerY, columnX + columnWidth, headerY + rowHeight);
            // ˮƽ����
            int textX = columnX + (columnWidth - textwidth(data[0][j].c_str())) / 2;
            // ��ֱ����
            int textY = headerY + (rowHeight - textheight(data[0][j].c_str())) / 2;
            outtextxy(textX, textY, data[0][j].c_str());
            columnX += columnWidth;
        }
        // �ͷű�ͷ�ü�����
        DeleteObject(headerClipRegion);

        // ���ñ�����ݲü������ų���ͷ�Ҳ��������Χ
        HRGN contentClipRegion = CreateRectRgn(x, y + rowHeight, x + width, y + height);
        SelectClipRgn(GetImageHDC(), contentClipRegion);

        // ���Ʊ������
        for (int i = firstVisibleRow; i < lastVisibleRow; ++i) {
            int rowY = y + (i * rowHeight - scrollOffset);
            columnX = x;
            for (int j = 0; j < totalColumns; ++j) {
                int columnWidth = columnWidths[j];
                bool isSelectedRow = (i == selectedRow);
                if (isSelectedRow) { // ѡ��
                    setfillcolor(click_bkselect_color);
                    settextcolor(click_textselect_color);
                }
                else {
                    setfillcolor(noclick_bkselect_color);
                    settextcolor(noclick_textselect_color);
                }
                fillrectangle(columnX, rowY, columnX + columnWidth, rowY + rowHeight);

                // ����ÿ����Ԫ����ı���������
                RECT rect = {
                    columnX + textPadding,
                    rowY + textPadding,
                    columnX + columnWidth - textPadding,
                    rowY + rowHeight - textPadding
                };
                SetBkMode(GetImageHDC(), TRANSPARENT);
                drawtext(data[i][j].c_str(), &rect, DT_WORDBREAK | DT_LEFT | DT_VCENTER);
                columnX += columnWidth;
            }
        }

        // �ͷű�����ݲü�����
        DeleteObject(contentClipRegion);
        SelectClipRgn(GetImageHDC(), NULL);

        // ���ƴ�ֱ����������
        int scrollbarX = x + width - scrollbarWidth;
        setfillcolor(scroll_bkbox_color);
        solidrectangle(scrollbarX, y, scrollbarX + scrollbarWidth, y + height);

        // ���㴹ֱ����λ�úʹ�С
        int handleX = scrollbarX;
        int handleWidth = scrollbarWidth;
        int totalHeight = data.size() * rowHeight;
        int maxHandleY = height - handleHeight;
        if (totalHeight > height) {
            handleY = maxHandleY * double(scrollOffset) / (totalHeight - height);
        }
        else {
            handleY = 0;
        }

        // ���ƴ�ֱ����
        setfillcolor(scroll_bkbar_color);
        solidrectangle(handleX, y + handleY, handleX + handleWidth, y + handleY + handleHeight);
    }

    // ɾ����
   virtual void deleteSelectedRow(int a) {
        if (a >0) {
            data.erase(data.begin() + a);

          
            sortByID();
            calculateColumnWidths();
            draw();
            selectedRow = -1;
        }
    }

    // �޸�ѡ����
   virtual void updateSelectedRow(std::vector < std::wstring > & newRow) {
        if (selectedRow != -1) {
            data[selectedRow] = newRow;
            sortByID();
            calculateColumnWidths();
        }
    }

    // �������
   virtual   void addRow( std::wstring& newRow) {
        
        sortByID();
        calculateColumnWidths();
    }

    // ��ID���򣨼����һ����ID�У�
    void sortByID() {
        // ���±�ţ���1��ʼ����
        for (int i = 1; i < data.size(); ++i) {
            if (data[i].size() > 0) { // ȷ����������һ��Ԫ��
                data[i][0] = std::to_wstring(i); // ����ID��
            }
        }
    }

  
};