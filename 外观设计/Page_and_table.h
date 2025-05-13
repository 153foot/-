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
    std::string file_path;
    std::map<std::string, std::unique_ptr<ButtonBase>> buttons;
    std::map<std::string, std::shared_ptr<TextboxBase>> texstboxs;
    std::map<std::string, std::shared_ptr<MediaPlayerBase>> mediaPlayers;
    std::vector<std::wstring> headers;

public:
    Page_and_table(int width, int height, const wchar_t* imagePath);


    virtual ~Page_and_table();
 

   
    virtual void addButton(std::string name, std::unique_ptr<ButtonBase> button) {//添加按钮

        buttons.insert(std::pair<const std::string, std::unique_ptr<ButtonBase>>(name, move(button)));

    }


    virtual void addtexstbox(std::string name, std::shared_ptr<TextboxBase>  texstbox) {//添加输入框

        texstboxs.insert(std::pair<const std::string, std::shared_ptr<TextboxBase>>(name, texstbox));

    }
    virtual void addGIF(std::string name, std::shared_ptr<MediaPlayerBase> GIF) {//添加GIF 动图

        mediaPlayers.insert(std::pair<const std::string, std::shared_ptr<MediaPlayerBase>>(name,GIF));

    }

    virtual void addTable(std::shared_ptr<TableWidgetBase> Table) {
     
        table = Table;
    }
   
    virtual void draw() {//把所有组件添加到一个界面中
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
    std::vector<std::vector<std::wstring>> loaddata(const std::string& otherfilePath) {
        FileHandler fileHandler(otherfilePath);//加载数据容器
		std::vector<std::vector<std::wstring>> data1 = fileHandler.getData();
       
       
		//table->setData(data);
        return data1;
    
    }

    void maketable(std::shared_ptr<TableWidgetBase> tablePtr, const std::string& otherfilePath, std::vector<std::wstring>& Headers) {//要改
        this->headers = Headers;
        this->file_path = otherfilePath;
        std::vector<std::vector<std::wstring>> txtdata= loaddata(otherfilePath);
        txtdata.insert(txtdata.begin(), Headers);
        tablePtr->setData(txtdata);
        addTable(tablePtr);
        
    }
    void updata() {
        //std::string& otherfilePath = this->file_path;
        FileHandler fileHandler(this->file_path);//加载数据容器
        std::vector<std::vector<std::wstring>> txtdata =table->getData();
        fileHandler.setData(txtdata);
    
    }
    void extraction_data() {//加载数据||更新数据库数据
        FileHandler fileHandler(this->file_path);//加载数据容器
        std::vector<std::vector<std::wstring>> extr_data = loaddata(this->file_path);
        extr_data.insert(extr_data.begin(), this->headers);

        table->Clear_container_data();

        table->setData(extr_data);

    
    }


     size_t Cell_num() {

        return table->Cell_num();
    }
    // 删除输入的ID
     void deleteSelectedRow(int num) {
        
         table->deleteSelectedRow(num);
    }

    // 修改选中行
     void updateRow(int row, int colume_begin, int colume_end, const std::vector<std::wstring>& newRow) {
         table->updateRow(row, colume_begin, colume_end, newRow);
    }

    // 添加新行
       void addRow(const std::wstring& newRow) {
           table->addRow(newRow);
    }
       
       std::wstring search_ID(int ID) {
           return table->find_ID_Row(ID);
       
       }
       void chear_all_Cell() {
           table->Clear_container_data();
       
       }
      
};