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
    int visibleRowCount; // 最多可见行数
    int rowHeight;       // 行
    int scrollOffset;    // 垂直滚动偏移
    std::vector<std::vector<std::wstring>> data;
    std::vector<int> columnWidths; // 列的宽度
    int selectedRow;          // 被选中的行
    int scrollbarWidth;       // 垂直滚动条的宽度
    int handleHeight;         // 垂直滚动条滑块的高度
    int handleY;              // 垂直滚动条滑块的垂直位置

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
    std::function<void()> callback;
    const int textPadding = 1; // 文字与表框的间距，修改为 1 像素
    const int scrollStep = 10; // 每次滚动的像素数

public:
    TableWidget(int x, int y, int width, int height, int visibleRowCount, int maxRows = 10, int maxColumns = 5,
        std::function<void()> cb = []() {}, LPCTSTR font = _T("宋体"),
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

    // 设置表格数据
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

    // 计算每列的宽度
    void calculateColumnWidths() {
        columnWidths.clear();
        if (!data.empty()) {
            columnWidths.resize(data[0].size(), 0);
            for (const auto& row : data) {
                for (size_t j = 0; j < row.size(); ++j) {
                    int width = textwidth(row[j].c_str());
                    if (width > columnWidths[j]) { // 每列的最大宽度（即每列中字符最大长度）
                        columnWidths[j] = width;
                    }
                }
            }
            // 考虑文字与单元格的间距
            for (auto& width : columnWidths) {
                width += 2 * textPadding;
            }
        }
        // 根据每列最大宽度计算该列长度
        int sumWidth = 0;
        for (auto it : columnWidths)
            sumWidth += it;
        for (auto& it : columnWidths)
            it = (float)it / sumWidth * (width - scrollbarWidth); // 减去垂直滚动条宽度
    }

    // 向上滚动
    void scrollUp() {
        if (scrollOffset > 0) {
            scrollOffset = max(0, scrollOffset - scrollStep);
        }
    }

    // 向下滚动
    void scrollDown() {
        int totalHeight = data.size() * rowHeight;
        int maxScrollOffset = max(0, totalHeight - height + rowHeight);
        // 确保滚动偏移量不会超过最大可滚动范围
        if (scrollOffset < maxScrollOffset) {
            scrollOffset = min(maxScrollOffset, scrollOffset + scrollStep);
        }
    }
    virtual size_t Cell_num() {

       return data.size();
    }

    // 处理鼠标滚动
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

    // 处理鼠标点击
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

    // 绘制表格
    virtual void draw() {
        // 绘制表格区域
        setlinestyle(PS_SOLID, 2);
        setfillcolor(RGB(240, 155, 89));
       // setfillcolor(noclick_bkselect_color);
        solidrectangle(x, y, x + width, y + height);
        setlinecolor(noclick_textselect_color);
        settextstyle(12, 0, fontName);

        // 获取总行数和列数
        int totalRows = static_cast<int>(data.size());
        int totalColumns = data.empty() ? 0 : static_cast<int>(data[0].size());

        // 计算需要绘制的行数和列数
        int firstVisibleRow = scrollOffset / rowHeight;
        int lastVisibleRow = min(totalRows, firstVisibleRow + visibleRowCount + (scrollOffset % rowHeight > 0 ? 1 : 0));

        // 绘制表头
        int headerY = y;
        int columnX = x;
        // 设置表头裁剪区域，确保表头固定且不超出表格范围
        HRGN headerClipRegion = CreateRectRgn(x, y, x + width, y + rowHeight);
        SelectClipRgn(GetImageHDC(), headerClipRegion);
        for (int j = 0; j < totalColumns; ++j) {
            int columnWidth = columnWidths[j];
            
            settextcolor(BLACK);
            rectangle(columnX, headerY, columnX + columnWidth, headerY + rowHeight);
            // 水平居中
            int textX = columnX + (columnWidth - textwidth(data[0][j].c_str())) / 2;
            // 垂直居中
            int textY = headerY + (rowHeight - textheight(data[0][j].c_str())) / 2;
            outtextxy(textX, textY, data[0][j].c_str());
            columnX += columnWidth;
        }
        // 释放表头裁剪区域
        DeleteObject(headerClipRegion);

        // 设置表格内容裁剪区域，排除表头且不超出表格范围
        HRGN contentClipRegion = CreateRectRgn(x, y + rowHeight, x + width, y + height);
        SelectClipRgn(GetImageHDC(), contentClipRegion);

        // 绘制表格内容
        for (int i = firstVisibleRow; i < lastVisibleRow; ++i) {
            int rowY = y + (i * rowHeight - scrollOffset);
            columnX = x;
            for (int j = 0; j < totalColumns; ++j) {
                int columnWidth = columnWidths[j];
                bool isSelectedRow = (i == selectedRow);
                if (isSelectedRow) { // 选中
                    setfillcolor(click_bkselect_color);
                    settextcolor(click_textselect_color);
                }
                else {
                    setfillcolor(noclick_bkselect_color);
                    settextcolor(noclick_textselect_color);
                }
                fillrectangle(columnX, rowY, columnX + columnWidth, rowY + rowHeight);

                // 定义每个单元格的文本绘制区域
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

        // 释放表格内容裁剪区域
        DeleteObject(contentClipRegion);
        SelectClipRgn(GetImageHDC(), NULL);

        // 绘制垂直滚动条背景
        int scrollbarX = x + width - scrollbarWidth;
        setfillcolor(scroll_bkbox_color);
        solidrectangle(scrollbarX, y, scrollbarX + scrollbarWidth, y + height);

        // 计算垂直滑块位置和大小
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

        // 绘制垂直滑块
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
        return L""; // 如果未找到，返回空字符串
    }
    // 删除行
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

    // 修改行n,修改 行n中的某列  
   virtual void updateRow(int row, int colume_begin, int colume_end, const std::vector<std::wstring>& newRow, std::unique_ptr<MessageDialogBase>& MessageDialo) {
       int update_colume_num= (colume_end- colume_begin)+1;
       if (newRow.size() > data[0].size()) {
           MessageDialo->setMessage(_T("输入内容为过多"));
           //MessageBoxW(NULL, _T("输入内容为过多"), _T("警告"), MB_OK | MB_ICONWARNING);
           return;
       
       }
       else if (newRow.size()< data[0].size()|| newRow.size()!= update_colume_num) {
           MessageDialo->setMessage(_T("输入内容为过少,修改的内容数量不符"));
          // MessageBoxW(NULL, _T("输入内容为过少,修改的内容数量不符"), _T("警告"), MB_OK | MB_ICONWARNING);
           return;
       }


       if (row >= 1 && row < static_cast<int>(data.size())) {
           if (colume_begin == 0&& colume_end==0) {
               // 修改整行
               data[row] = newRow;
           }
           else if (colume_begin >= 1 && colume_end <= static_cast<int>(data[row].size())) {
               // 修改指定列
               auto colume =  static_cast<std::vector<std::wstring, std::allocator<std::wstring>>::size_type>(colume_begin - 1);
                  
               for (const auto& newRow_1 : newRow) {
                   
                   data[row][++colume] = newRow_1;
                       
               
               }
           }
           else {
               MessageDialo->setMessage(_T("输入ID错误"));
               //MessageBoxW(NULL, _T("输入ID错误"), _T("警告"), MB_OK | MB_ICONWARNING);
               return;
           
           }

           sort_ASC_ID();
           calculateColumnWidths();
       }
   }
   
   // 添加新行
  // 添加新行
   virtual void addRow(const std::wstring& newRow, std::unique_ptr<MessageDialogBase>& MessageDialo) {

       if (newRow.empty()) {
           MessageDialo->setMessage(_T("内容为空"));
          // MessageBoxW(NULL, _T("内容为空"), _T("警告"), MB_OK | MB_ICONWARNING);
           return;
       }
       std::vector<std::wstring> splitData = splitString(newRow);

       // 检查是否有足够的元素
       if (splitData.empty()) {
           MessageDialo->setMessage(_T("内容为空"));
          // MessageBoxW(NULL, _T("内容为空"), _T("警告"), MB_OK | MB_ICONWARNING);
           return;
       }
       if (splitData.size() > data[0].size()) {
           MessageDialo->setMessage(_T("输入内容为过多"));
          // MessageBoxW(NULL, _T("输入内容为过多"), _T("警告"), MB_OK | MB_ICONWARNING);
           return;
       }
       else if (splitData.size() <data[0].size()) {
           MessageDialo->setMessage(_T("输入内容为过少"));
          // MessageBoxW(NULL, _T("输入内容为过少"), _T("警告"), MB_OK | MB_ICONWARNING);
           return;
       
       }
       // 将第一列(ID)转换为数字
       
           int newID = std::stoi(splitData[0]);

           // 检查ID是否已存在
        
           for (const auto& row : std::vector<std::vector<std::wstring>>(data.begin() + 1, data.end())) {
               if (!row.empty() && std::stoi(row[0]) == newID) {
                   MessageDialo->setMessage(_T("输入ID号重复"));
                   return;
                   //MessageBoxW(NULL, _T("输入ID号重复"), _T("警告"), MB_OK | MB_ICONWARNING);
               }
           }
       
      

       // 如果ID合法且唯一，则添加到数据中
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

       // 添加最后一个子字符串（或整个字符串，如果没有找到分隔符）
       result.push_back(input.substr(start));

       return result;
   }

    //// 按ID排序
    //void sortByID() {
    //    // 重新编号：从1开始递增
    //    for (int i = 1; i < data.size(); ++i) {
    //        if (data[i].size() > 0) { // 确保行至少有一个元素
    //            data[i][0] = std::to_wstring(i); // 更新ID列
    //        }
    //    }
    //}
    void sort_ASC_ID() {
        // 按现有ID列的值升序排序（不重新编号）
        std::sort(std::next(data.begin()), data.end(), [](const std::vector<std::wstring>& a, const std::vector<std::wstring>& b) {
            if (a.empty() || b.empty() || a[0].empty() || b[0].empty()) {
                return false; // 空行或空ID不参与排序
            }
            try {
                // 尝试将ID转换为整数进行比较
                int idA = std::stoi(a[0]);
                int idB = std::stoi(b[0]);
                return idA < idB;
            }
            catch (const std::exception&) {
                // 转换失败时按字符串比较
                return a[0] < b[0];
            }
        });
        calculateColumnWidths(); 
    }
  
};