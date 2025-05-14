#include "TableWidgetBase.h"
#include <vector>
#include <string>
#include "functional"
#include <algorithm>
#include <easyx.h>
#include <exception>
#include <iostream>
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
        setfillcolor(RGB(240, 155, 89));
       // setfillcolor(noclick_bkselect_color);
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
            
            settextcolor(BLACK);
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

    virtual std::wstring find_ID_Row(int id, std::unique_ptr<MessageDialogBase>& MessageDialo) {
        for (const auto& row : std::vector<std::vector<std::wstring>>(data.begin() + 1, data.end())) {
            if (!row.empty()) {
               
                    int currentId = std::stoi(row[0]);
                    if (currentId == id) {
                        std::wstring result;
                        for (size_t i = 0; i < row.size(); ++i) {
                            result += row[i];
                            if (i != row.size() - 1) {
                                result += L"|";
                            }
                        }
                        return result;
                    }
                
             
            }
        }
        return L""; // ���δ�ҵ������ؿ��ַ���
    }
    // ɾ����
   virtual void deleteSelectedRow(int a) {
        if (a >0) {
            data.erase(data.begin() + a); 
            sort_ASC_ID();
            calculateColumnWidths();
            draw();
            selectedRow = -1;
        }
       
    }
   virtual void deleteALL() {
       data.erase(std::next(data.begin()),data.end());

   }

    // �޸���n,�޸� ��n�е�ĳ��  
   virtual void updateRow(int row, int colume_begin, int colume_end, const std::vector<std::wstring>& newRow, std::unique_ptr<MessageDialogBase>& MessageDialo) {
       int update_colume_num= (colume_end- colume_begin)+1;
       if (newRow.size() > data[0].size()) {
           MessageDialo->setMessage(_T("��������Ϊ����"));
           //MessageBoxW(NULL, _T("��������Ϊ����"), _T("����"), MB_OK | MB_ICONWARNING);
           return;
       
       }
       else if (newRow.size()< data[0].size()|| newRow.size()!= update_colume_num) {
           MessageDialo->setMessage(_T("��������Ϊ����,�޸ĵ�������������"));
          // MessageBoxW(NULL, _T("��������Ϊ����,�޸ĵ�������������"), _T("����"), MB_OK | MB_ICONWARNING);
           return;
       }


       if (row >= 1 && row < static_cast<int>(data.size())) {
           if (colume_begin == 0&& colume_end==0) {
               // �޸�����
               data[row] = newRow;
           }
           else if (colume_begin >= 1 && colume_end <= static_cast<int>(data[row].size())) {
               // �޸�ָ����
               auto colume =  static_cast<std::vector<std::wstring, std::allocator<std::wstring>>::size_type>(colume_begin - 1);
                  
               for (const auto& newRow_1 : newRow) {
                   
                   data[row][++colume] = newRow_1;
                       
               
               }
           }
           else {
               MessageDialo->setMessage(_T("����ID����"));
               //MessageBoxW(NULL, _T("����ID����"), _T("����"), MB_OK | MB_ICONWARNING);
               return;
           
           }

           sort_ASC_ID();
           calculateColumnWidths();
       }
   }
   
   // �������
  // �������
   virtual void addRow(const std::wstring& newRow, std::unique_ptr<MessageDialogBase>& MessageDialo) {

       if (newRow.empty()) {
           MessageDialo->setMessage(_T("����Ϊ��"));
          // MessageBoxW(NULL, _T("����Ϊ��"), _T("����"), MB_OK | MB_ICONWARNING);
           return;
       }
       std::vector<std::wstring> splitData = splitString(newRow);

       // ����Ƿ����㹻��Ԫ��
       if (splitData.empty()) {
           MessageDialo->setMessage(_T("����Ϊ��"));
          // MessageBoxW(NULL, _T("����Ϊ��"), _T("����"), MB_OK | MB_ICONWARNING);
           return;
       }
       if (splitData.size() > data[0].size()) {
           MessageDialo->setMessage(_T("��������Ϊ����"));
          // MessageBoxW(NULL, _T("��������Ϊ����"), _T("����"), MB_OK | MB_ICONWARNING);
           return;
       }
       else if (splitData.size() <data[0].size()) {
           MessageDialo->setMessage(_T("��������Ϊ����"));
          // MessageBoxW(NULL, _T("��������Ϊ����"), _T("����"), MB_OK | MB_ICONWARNING);
           return;
       
       }
       // ����һ��(ID)ת��Ϊ����
       
           int newID = std::stoi(splitData[0]);

           // ���ID�Ƿ��Ѵ���
        
           for (const auto& row : std::vector<std::vector<std::wstring>>(data.begin() + 1, data.end())) {
               if (!row.empty() && std::stoi(row[0]) == newID) {
                   MessageDialo->setMessage(_T("����ID���ظ�"));
                   return;
                   //MessageBoxW(NULL, _T("����ID���ظ�"), _T("����"), MB_OK | MB_ICONWARNING);
               }
           }
       
      

       // ���ID�Ϸ���Ψһ������ӵ�������
       data.push_back(splitData);
       sort_ASC_ID();
       calculateColumnWidths();
   }
   virtual void Clear_container_data() {
       data.clear();
   }
   private:
   std::vector<std::wstring> splitString(const std::wstring& input, wchar_t delimiter = L'|') {
       std::vector<std::wstring> result;
       size_t start = 0;
       size_t end = 0;

       while ((end = input.find(delimiter, start)) != std::wstring::npos) {
           result.push_back(input.substr(start, end - start));
           start = end + 1;
       }

       // ������һ�����ַ������������ַ��������û���ҵ��ָ�����
       result.push_back(input.substr(start));

       return result;
   }

    //// ��ID����
    //void sortByID() {
    //    // ���±�ţ���1��ʼ����
    //    for (int i = 1; i < data.size(); ++i) {
    //        if (data[i].size() > 0) { // ȷ����������һ��Ԫ��
    //            data[i][0] = std::to_wstring(i); // ����ID��
    //        }
    //    }
    //}
    void sort_ASC_ID() {
        // ������ID�е�ֵ�������򣨲����±�ţ�
        std::sort(std::next(data.begin()), data.end(), [](const std::vector<std::wstring>& a, const std::vector<std::wstring>& b) {
            if (a.empty() || b.empty() || a[0].empty() || b[0].empty()) {
                return false; // ���л��ID����������
            }
            try {
                // ���Խ�IDת��Ϊ�������бȽ�
                int idA = std::stoi(a[0]);
                int idB = std::stoi(b[0]);
                return idA < idB;
            }
            catch (const std::exception&) {
                // ת��ʧ��ʱ���ַ����Ƚ�
                return a[0] < b[0];
            }
        });
        calculateColumnWidths(); 
    }
  
};