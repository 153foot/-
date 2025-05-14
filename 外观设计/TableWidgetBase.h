#pragma once
#include <windows.h>
#include<vector>
#include<string>
#include <memory>
#include "MessageDialogBase.h"
class TableWidgetBase
{
protected:
	int x;
	int y;
	int width;
	int height;


public:
	TableWidgetBase(int x, int y, int width, int height);
	virtual ~TableWidgetBase();
	virtual void draw() = 0; // 纯虚函数，子类必须实现
	virtual  void changeColo(COLORREF newColor);// 改变按钮颜色
	virtual void checkMouseOver(int mouseX, int mouseY); // 检查鼠标悬停
	virtual bool checkClick(int mouseX, int mouseY); // 检查鼠标点击
	virtual void onClick(); // 点击时的回调函数
	virtual void Mousemove(int mouseX, int mouseY);//鼠标移动
	virtual void doublecheckClick(int mouseX, int mouseY);//双击
	virtual void scroll(int mouseX, int mouseY, int wheel);
	virtual void handleMouseClick(int mouseX, int mouseY);
	virtual void setData(const std::vector<std::vector<std::wstring>> newData);
	virtual  std::vector<std::vector<std::wstring>>& getData() = 0;
	virtual size_t Cell_num() {
		return 0;
		
	}
	virtual void deleteALL() {
	
	}
	// 删除输入ID对应的行
	virtual void deleteSelectedRow(int ID) {

	}
	// 添加新行
	virtual void addRow( std::vector<std::wstring>& newRow) {

	}
	virtual void Clear_container_data() {//清除容器数据
	
	}
	virtual std::wstring find_ID_Row(int id ,std::unique_ptr<MessageDialogBase>& MessageDialo) {//查找对应ID的一行数据
		return L" ";
	
	}
	virtual void updateRow(int row, int colume_begin, int colume_end, const std::vector<std::wstring>& newRow, std::unique_ptr<MessageDialogBase>& MessageDialo) {//修改一行数据
	
	
	}
	virtual void addRow(const std::wstring& newRow, std::unique_ptr<MessageDialogBase>& MessageDialo) {//添加一行新数据
	
	
	}
};

