#pragma once
#include <string>
class MessageDialogBase
{
protected:
	int x;                  // 对话框左上角的 x 坐标
	int y;                  // 对话框左上角的 y 坐标
	int width;              // 对话框的宽度
	int height;             // 对话框的高度   
public:
	MessageDialogBase(int x, int y, int width, int height) :x(x),y(y), width(width), height(height){ // 默认构造函数
	
	}
	virtual ~MessageDialogBase() {

	}

	virtual void setMessage(const std::wstring& message) {// 设置消息内容
	
	} 
	virtual void setTitle(const std::wstring& title) {// 设置标题
	
	
	}
	virtual void draw() = 0; // 绘制消息显示区域


};

