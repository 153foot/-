#pragma once
#include "Textbox.h"
#include"PageBase.h"
#include "MediaPlayerBase.h"
#include "TextboxBase.h"
#include "MessageDialogBase.h"

#include <easyx.h>
#include <memory>

#include<map>


class Page//只能添加按钮的
    :public PageBase {
private:
    int width;
    int height;
    std::unique_ptr<MessageDialogBase> MessageDialo;
  
    std::unique_ptr<IMAGE> pageImage;
    std::map<std::string, std::unique_ptr<ButtonBase>> buttons;
    std::map<std::string, std::shared_ptr<TextboxBase>> texstboxs;
    std::map<std::string, std::shared_ptr<MediaPlayerBase>> mediaPlayers;
    TextboxBase* currentSelectedTextBox = nullptr;
public:
	
    Page(int width, int height, const wchar_t* imagePath);
    virtual ~Page();
   
    virtual void addButton(std::string name,std::unique_ptr<ButtonBase> button) {//添加按钮


        buttons.insert(std::pair<const std::string, std::unique_ptr<ButtonBase>>(name, move(button)));

    }
    virtual void addtexstbox(std::string name, std::shared_ptr<TextboxBase>  texstbox) {//添加输入框

        texstboxs.insert(std::pair<const std::string, std::shared_ptr<TextboxBase>>(name, texstbox));

    }
    virtual void addGIF(std::string name, std::shared_ptr<MediaPlayerBase> GIF) {//添加GIF 动图

        mediaPlayers.insert(std::pair<const std::string, std::shared_ptr<MediaPlayerBase>>(name, GIF));

    }
	virtual void addMessageDialog(std::unique_ptr<MessageDialogBase> messageDialog) {//添加消息对话框
		MessageDialo = std::move(messageDialog);
	}
    virtual void setMessageDialog(std::wstring message) {//添加消息对话框
        MessageDialo->setMessage(message);
    }

    virtual std::wstring  get_texstbox_message(std::string index) {
        
           
        
        return texstboxs[index]->getinput();
        
      
        
    }

    virtual void draw();
    virtual void mouseClick(int mouseX, int mouseY);
    virtual void mouseMove(int mouseX, int mouseY);
    virtual void HandleMouseUp();
    virtual void KeyInput(wchar_t ch);
    virtual void Hotkeydown(BYTE as);
    void onMouseClick(int mouseX, int mouseY);
	/*void showMessageDialog() {
		if (MessageDialo) {
			MessageDialo->draw();

            Sleep(2000);
		}
	}*/

};