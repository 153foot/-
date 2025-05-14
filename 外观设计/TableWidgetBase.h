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
	virtual void draw() = 0; // ���麯�����������ʵ��
	virtual  void changeColo(COLORREF newColor);// �ı䰴ť��ɫ
	virtual void checkMouseOver(int mouseX, int mouseY); // ��������ͣ
	virtual bool checkClick(int mouseX, int mouseY); // ��������
	virtual void onClick(); // ���ʱ�Ļص�����
	virtual void Mousemove(int mouseX, int mouseY);//����ƶ�
	virtual void doublecheckClick(int mouseX, int mouseY);//˫��
	virtual void scroll(int mouseX, int mouseY, int wheel);
	virtual void handleMouseClick(int mouseX, int mouseY);
	virtual void setData(const std::vector<std::vector<std::wstring>> newData);
	virtual  std::vector<std::vector<std::wstring>>& getData() = 0;
	virtual size_t Cell_num() {
		return 0;
		
	}
	virtual void deleteALL() {
	
	}
	// ɾ������ID��Ӧ����
	virtual void deleteSelectedRow(int ID) {

	}
	// �������
	virtual void addRow( std::vector<std::wstring>& newRow) {

	}
	virtual void Clear_container_data() {//�����������
	
	}
	virtual std::wstring find_ID_Row(int id ,std::unique_ptr<MessageDialogBase>& MessageDialo) {//���Ҷ�ӦID��һ������
		return L" ";
	
	}
	virtual void updateRow(int row, int colume_begin, int colume_end, const std::vector<std::wstring>& newRow, std::unique_ptr<MessageDialogBase>& MessageDialo) {//�޸�һ������
	
	
	}
	virtual void addRow(const std::wstring& newRow, std::unique_ptr<MessageDialogBase>& MessageDialo) {//���һ��������
	
	
	}
};

