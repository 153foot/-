#pragma once
#include <windows.h>
#include<vector>
#include<string>
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
	virtual void setData(const std::vector<std::vector<std::wstring>>& newData);
	virtual int getSelectedRow() {
		return -1;
	}
	virtual size_t Cell_num() {
		return 0;
		
	}
	// 删除选中行
	virtual void deleteSelectedRow(int a) {

	}
	// 修改选中行
	virtual void updateSelectedRow( std::vector<std::wstring>& newRow) {

	}
	// 添加新行
	virtual   void addRow( std::vector<std::wstring>& newRow) {

	}
	
};

