#pragma once
#include <string>
class MessageDialogBase
{
protected:
	int x;                  // �Ի������Ͻǵ� x ����
	int y;                  // �Ի������Ͻǵ� y ����
	int width;              // �Ի���Ŀ��
	int height;             // �Ի���ĸ߶�   
public:
	MessageDialogBase(int x, int y, int width, int height) :x(x),y(y), width(width), height(height){ // Ĭ�Ϲ��캯��
	
	}
	virtual ~MessageDialogBase() {

	}

	virtual void setMessage(const std::wstring& message) {// ������Ϣ����
	
	} 
	virtual void setTitle(const std::wstring& title) {// ���ñ���
	
	
	}
	virtual void draw() = 0; // ������Ϣ��ʾ����


};

