//#pragma once
//#include "MediaPlayerBase.h"
//#include "TextboxBase.h"
//#include "PageBase.h"
//#include "TableWidgetBase.h"
//#include "FileHandler.h"
//#include "MessageDialogBase.h"
//#include <easyx.h>
//#include <memory>
//#include <map>
//#include <string>
//
//class Page_and_table : public PageBase {
//private:
//    int width;
//    int height;
//    std::unique_ptr<IMAGE> pageImage;
//    std::shared_ptr<TableWidgetBase> table;
//    std::string file_path;
//    std::map<std::string, std::unique_ptr<ButtonBase>> buttons;
//    std::map<std::string, std::shared_ptr<TextboxBase>> texstboxs;
//    std::map<std::string, std::shared_ptr<MediaPlayerBase>> mediaPlayers;
//    std::unique_ptr<MessageDialogBase> MessageDialo;
//    TextboxBase* currentSelectedTextBox = nullptr;
//    std::vector<std::wstring> headers;
//
//public:
//    Page_and_table(int width, int height, const wchar_t* imagePath);
//
//    virtual ~Page_and_table();
//
//    virtual void addButton(std::string name, std::unique_ptr<ButtonBase> button) {
//        buttons.insert(std::make_pair(name, std::move(button)));
//    }
//
//    virtual void addtexstbox(std::string name, std::shared_ptr<TextboxBase> texstbox) {
//        texstboxs.insert(std::make_pair(name, texstbox));
//    }
//
//    virtual void addGIF(std::string name, std::shared_ptr<MediaPlayerBase> GIF) {
//        mediaPlayers.insert(std::make_pair(name, GIF));
//    }
//
//    virtual void addTable(std::shared_ptr<TableWidgetBase> Table) {
//        table = Table;
//    }
//
//    virtual void addMessageDialog(std::unique_ptr<MessageDialogBase> messageDialog) {
//        MessageDialo = std::move(messageDialog);
//    }
//
//    virtual void setMessageDialog(std::wstring message) {
//        if (MessageDialo)
//            MessageDialo->setMessage(message);
//    }
//
//    virtual void draw() {
//        if (pageImage) {
//            putimage(0, 0, pageImage.get());
//        }
//
//        if (table) {
//            table->draw();
//        }
//
//        if (!buttons.empty()) {
//            for (auto& button : buttons) {
//                button.second->draw();
//            }
//        }
//
//        if (!texstboxs.empty()) {
//            for (auto& texstbox : texstboxs) {
//                texstbox.second->draw();
//            }
//        }
//
//        if (!mediaPlayers.empty()) {
//            for (auto& mediaPlayer : mediaPlayers) {
//                mediaPlayer.second->draw();
//            }
//        }
//
//        if (MessageDialo) {
//            MessageDialo->draw();
//        }
//    }
//
//    virtual void mouseClick(int mouseX, int mouseY) {
//        if (table) {
//            table->handleMouseClick(mouseX, mouseY);
//        }
//
//        for (auto& button : buttons) {
//            if (button.second->checkClick(mouseX, mouseY)) {
//                break;
//            }
//        }
//
//        for (auto& texstbox : texstboxs) {
//            if (texstbox.second->checkClick(mouseX, mouseY)) {
//                break;
//            }
//        }
//
//        onMouseClick(mouseX, mouseY);
//    }
//
//    virtual void mouseMove(int mouseX, int mouseY) {
//        for (auto& button : buttons) {
//            button.second->checkMouseOver(mouseX, mouseY);
//        }
//
//        for (auto& texstbox : texstboxs) {
//            texstbox.second->checkMouseOver(mouseX, mouseY);
//        }
//    }
//
//    virtual void HandleMouseUp() {
//        for (auto& texstbox : texstboxs) {
//            if (texstbox.second->handleMouseUp()) {
//                break;
//            }
//        }
//    }
//
//    virtual void KeyInput(wchar_t ch) {
//        if (currentSelectedTextBox) {
//            currentSelectedTextBox->keyInput(ch);
//        }
//    }
//
//    virtual void Hotkeydown(BYTE as) {
//        if (currentSelectedTextBox) {
//            currentSelectedTextBox->hotkeydown(as);
//        }
//    }
//
//    virtual std::wstring get_texstbox_message(std::string index) {
//        auto it = texstboxs.find(index);
//        if (it != texstboxs.end()) {
//            return it->second->getinput();
//        }
//        return L"";
//    }
//
//    void onMouseClick(int mouseX, int mouseY) {
//        TextboxBase* newSelectedTextBox = nullptr;
//
//        // 查找被点击的文本框
//        for (auto& textbox : texstboxs) {
//            if (textbox.second->checkClick(mouseX, mouseY)) {
//                newSelectedTextBox = textbox.second.get();
//                break;
//            }
//        }
//
//        // 处理新旧选中状态
//        if (newSelectedTextBox) {
//            if (currentSelectedTextBox && currentSelectedTextBox != newSelectedTextBox) {
//                currentSelectedTextBox->deselect();
//            }
//            currentSelectedTextBox = newSelectedTextBox;
//        }
//        else {
//            if (currentSelectedTextBox) {
//                currentSelectedTextBox->deselect();
//                currentSelectedTextBox = nullptr;
//            }
//        }
//    }
//
//    // 表格数据操作
//    std::vector<std::vector<std::wstring>> loaddata(const std::string& otherfilePath) {
//        FileHandler fileHandler(otherfilePath);
//        return fileHandler.getData();
//    }
//
//    void maketable(std::shared_ptr<TableWidgetBase> tablePtr, const std::string& otherfilePath, std::vector<std::wstring>& Headers) {
//        this->headers = Headers;
//        this->file_path = otherfilePath;
//        std::vector<std::vector<std::wstring>> txtdata = loaddata(otherfilePath);
//        txtdata.insert(txtdata.begin(), Headers);
//        tablePtr->setData(txtdata);
//        addTable(tablePtr);
//    }
//
//    void updata() {
//        FileHandler fileHandler(this->file_path);
//        std::vector<std::vector<std::wstring>> txtdata = table->getData();
//        fileHandler.setData(txtdata);
//    }
//
//    void extraction_data() {
//        FileHandler fileHandler(this->file_path);
//        std::vector<std::vector<std::wstring>> extr_data = loaddata(this->file_path);
//        extr_data.insert(extr_data.begin(), this->headers);
//        table->Clear_container_data();
//        table->setData(extr_data);
//    }
//
//    size_t Cell_num() {
//        return table ? table->Cell_num() : 0;
//    }
//
//    void deleteSelectedRow(int num) {
//        if (table) table->deleteSelectedRow(num);
//    }
//
//    void updateRow(int row, int colume_begin, int colume_end, const std::vector<std::wstring>& newRow) {
//        if (table) table->updateRow(row, colume_begin, colume_end, newRow);
//    }
//
//    void addRow(const std::wstring& newRow) {
//        if (table) table->addRow(newRow);
//    }
//
//    std::wstring search_ID(int ID) {
//        return table ? table->find_ID_Row(ID) : L"";
//    }
//
//    void chear_all_Cell() {
//        if (table) table->Clear_container_data();
//    }
//};

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
  
       std::unique_ptr<MessageDialogBase> MessageDialo;
       TextboxBase* currentSelectedTextBox = nullptr;
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
     virtual void addMessageDialog(std::unique_ptr<MessageDialogBase> messageDialog) {
         MessageDialo = std::move(messageDialog);
     }
     virtual std::unique_ptr<MessageDialogBase>& get_this_MessageDialo() {
     
         return this->MessageDialo;
     
     }
 
     virtual void setMessageDialog(std::wstring message) {
         if (MessageDialo)
             MessageDialo->setMessage(message);
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
        if (MessageDialo) {
            MessageDialo->draw();
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
        onMouseClick(mouseX, mouseY);
            
        
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
    virtual void HandleMouseUp() {
        for (auto& texstbox : texstboxs) {
            if (texstbox.second->handleMouseUp()) {
                break;
            }
        }
    }

    virtual void KeyInput(wchar_t ch) {
        if (currentSelectedTextBox) {
            currentSelectedTextBox->keyInput(ch);
        }
    }

    virtual void Hotkeydown(BYTE as) {
        if (currentSelectedTextBox) {
            currentSelectedTextBox->hotkeydown(as);
        }
    }

    virtual std::wstring get_texstbox_message(std::string index) {
        auto it = texstboxs.find(index);
        if (it != texstboxs.end()) {
            return it->second->getinput();
        }
        return L"";
    }



    void onMouseClick(int mouseX, int mouseY) {
        TextboxBase* newSelectedTextBox = nullptr;
        // 1. 查找被点击的文本框
        for (auto textbox : texstboxs) {
            if (textbox.second->checkClick(mouseX, mouseY)) {
                newSelectedTextBox = textbox.second.get();
                break;
            }
        }

        // 2. 处理新旧选中状态
        if (newSelectedTextBox) { // 点击了某个文本框
            if (currentSelectedTextBox && currentSelectedTextBox != newSelectedTextBox) {
                // 取消旧选中（仅当点击的是新文本框）
                currentSelectedTextBox->deselect();
            }
            // 更新为新选中（即使点击的是同一个文本框，也无需取消，保持选中）
            currentSelectedTextBox = newSelectedTextBox;
        }
        else { // 点击空白区域，取消所有选中
            if (currentSelectedTextBox) {
                currentSelectedTextBox->deselect();
                currentSelectedTextBox = nullptr;
            }
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
     void updateRow(int row, int colume_begin, int colume_end, const std::vector<std::wstring>& newRow, std::unique_ptr<MessageDialogBase>& MessageDialo) {
         table->updateRow(row, colume_begin, colume_end, newRow, MessageDialo);
    }

    // 添加新行
       void addRow(const std::wstring& newRow, std::unique_ptr<MessageDialogBase>& MessageDialo) {
           table->addRow(newRow, MessageDialo);
    }
       
       std::wstring search_ID(int ID, std::unique_ptr<MessageDialogBase>& MessageDialo) {//查找ID
           return table->find_ID_Row(ID, MessageDialo);
       
       }
       void chear_all_Cell() {
           table->Clear_container_data();
       
       }
      
};