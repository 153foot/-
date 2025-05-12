#pragma once
#include "MediaPlayerBase.h"
#include "TextboxBase.h"
#include "PageBase.h"
#include "TableWidgetBase.h"
#include "FileHandler.h"
#include <easyx.h>
#include <memory>
#include <map>
#include <string>
class Page_and_table : public PageBase {
private:
    
    int width;
    int height;
    std::unique_ptr<IMAGE> pageImage;
    std::shared_ptr<TableWidgetBase> table;
   
    std::map<std::string, std::unique_ptr<ButtonBase>> buttons;
    std::map<std::string, std::shared_ptr<TextboxBase>> texstboxs;
    std::map<std::string, std::shared_ptr<MediaPlayerBase>> mediaPlayers;
    

public:
    Page_and_table(int width, int height, const wchar_t* imagePath);


    virtual ~Page_and_table();
 

   
    virtual void addButton(std::string name, std::unique_ptr<ButtonBase> button) {//��Ӱ�ť

        buttons.insert(std::pair<const std::string, std::unique_ptr<ButtonBase>>(name, move(button)));

    }


    virtual void addtexstbox(std::string name, std::shared_ptr<TextboxBase>  texstbox) {//��������

        texstboxs.insert(std::pair<const std::string, std::shared_ptr<TextboxBase>>(name, texstbox));

    }
    virtual void addGIF(std::string name, std::shared_ptr<MediaPlayerBase> GIF) {//���GIF ��ͼ

        mediaPlayers.insert(std::pair<const std::string, std::shared_ptr<MediaPlayerBase>>(name,GIF));

    }

    virtual void addTable(std::shared_ptr<TableWidgetBase> Table) {
     
        table = Table;
    }
   
    virtual void draw() {//�����������ӵ�һ��������
        if (pageImage.get() != nullptr) {
            putimage(0, 0, pageImage.get());
        }
       

        if (table) {
            table->draw();
        }
            
        if (!buttons.empty()) {
            for (auto& button : buttons) {
                button.second->draw();
            }
        }
        if (!texstboxs.empty()) {
            for (auto& texstbox : texstboxs) {
                texstbox.second->draw();
            }
        }
        if (!mediaPlayers.empty()) {//
            for (auto& mediaPlayer : mediaPlayers) {
                mediaPlayer.second->draw();
            }
        }

    }

    virtual void mouseClick(int mouseX, int mouseY) {
        if (table) {
            table->handleMouseClick(mouseX, mouseY);
        }
        for (auto& button : buttons) {
            if (button.second->checkClick(mouseX, mouseY)) {
                break;
            }
        }
        for (auto& texstbox : texstboxs) {
            if (texstbox.second->checkClick(mouseX, mouseY)) {
                break;
            }
        }
       
            
        
    }

    virtual void mouseMove(int mouseX, int mouseY) {
        for (auto& button : buttons) {
            button.second->checkMouseOver(mouseX, mouseY);
        }
        for (auto& texstbox : texstboxs) {
            texstbox.second->checkMouseOver(mouseX, mouseY);
        }
    }

    virtual void mouseWheel(int mouseX, int mouseY, int wheel) {
       
            if (table) {
                table->scroll(mouseX, mouseY, wheel);
            }
        
    }
    std::vector<std::vector<std::wstring>> loaddata(const std::string& otherfilePath, wchar_t otherdelimiter) {
        FileHandler fileHandler(otherfilePath);//������������
		std::vector<std::vector<std::wstring>> data1 = fileHandler.getData();
       
       
		//table->setData(data);
        return data1;
    
    }

    void maketable(std::shared_ptr<TableWidgetBase> tablePtr, const std::string& otherfilePath, wchar_t otherdelimiter, std::vector<std::wstring>& Headers) {//Ҫ��
        std::vector<std::vector<std::wstring>> txtdata= loaddata(otherfilePath, otherdelimiter);
        txtdata.insert(txtdata.begin(), Headers);
        tablePtr->setData(txtdata);
        addTable(tablePtr);
        
    }
    void updata(const std::string& otherfilePath) {
        FileHandler fileHandler(otherfilePath);//������������
        std::vector<std::vector<std::wstring>> txtdata =table->getData();
        fileHandler.setData(txtdata);
    
    }


     size_t Cell_num() {

        return table->Cell_num();
    }
    // ɾ��ѡ����
     void deleteSelectedRow(int num) {
        
         table->deleteSelectedRow(num);
    }

    // �޸�ѡ����
     void updateSelectedRow(const std::vector<std::wstring>& newRow) {
        // table->updateSelectedRow(,);
    }

    // �������
       void addRow(const std::vector<std::wstring>& newRow) {
        
    }

};