#include "page.h"

Page::Page(int width, int height, const wchar_t* imagePath)
    : width(width), height(height), pageImage(new IMAGE(width, height)){
    
    loadimage(pageImage.get(), imagePath, width, height);
	//putimage(0, 0, pageImage);
   
   
        setfillcolor(RGB(240, 240, 240));
        solidrectangle(0, 0, width, height);
        putimage(0, 0, pageImage.get());
        getimage(pageImage.get(), 0, 0, width, height);
    
}

Page::~Page() {
    
}





void Page::draw() {
    if (pageImage != nullptr) {
        putimage(0, 0, pageImage.get());
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

void Page::mouseClick(int mouseX, int mouseY) {
    for (auto& button : buttons) {
        if (button.second->checkClick(mouseX, mouseY)) {
            break;
        }
    }
    onMouseClick( mouseX,  mouseY);
    //Textbox* newSelectedTextBox = nullptr;

    //// 1. ���������ı����ҵ���������ı���
    //for (auto& texstbox : texstboxs) {
    //    if (texstbox.second->checkClick(mouseX, mouseY)) {
    //        break;
    //    }
    //}
    //// 2. ȡ�����ı����ѡ�У���������Ҳ��ǵ�ǰ������ı���
    //if (currentSelectedTextBox && currentSelectedTextBox != newSelectedTextBox) {
    //    currentSelectedTextBox->deselect(); // ����ȡ��ѡ�з���
    //}

    //// 3. ���µ�ǰѡ��״̬��newSelectedTextBox ����Ϊ nullptr��������հ�����
    //currentSelectedTextBox = newSelectedTextBox;
  

}

void Page::mouseMove(int mouseX, int mouseY) {
    for (auto& button : buttons) {
        button.second->checkMouseOver(mouseX, mouseY);
    }
    for (auto& texstbox : texstboxs) {
        texstbox.second->checkMouseOver(mouseX, mouseY);
    }
}

void Page::HandleMouseUp()
{
    for (auto& texstbox : texstboxs) {
        if(texstbox.second->handleMouseUp()) {
            break;
        }
    }
   
}

void Page::KeyInput(wchar_t ch)
{
    for (auto& texstbox : texstboxs) {
        texstbox.second->keyInput(ch);
    }
}

void Page::Hotkeydown(BYTE as)
{
    for (auto& texstbox : texstboxs) {
        texstbox.second->hotkeydown(as);
    }
}

inline void Page::onMouseClick(int mouseX, int mouseY) {
    TextboxBase* newSelectedTextBox = nullptr;
    // 1. ���ұ�������ı���
    for (auto textbox : texstboxs) {
        if (textbox.second->checkClick(mouseX, mouseY)) {
            newSelectedTextBox = textbox.second.get();
            break;
        }
    }

    // 2. �����¾�ѡ��״̬
    if (newSelectedTextBox) { // �����ĳ���ı���
        if (currentSelectedTextBox && currentSelectedTextBox != newSelectedTextBox) {
            // ȡ����ѡ�У���������������ı���
            currentSelectedTextBox->deselect();
        }
        // ����Ϊ��ѡ�У���ʹ�������ͬһ���ı���Ҳ����ȡ��������ѡ�У�
        currentSelectedTextBox = newSelectedTextBox;
    }
    else { // ����հ�����ȡ������ѡ��
        if (currentSelectedTextBox) {
            currentSelectedTextBox->deselect();
            currentSelectedTextBox = nullptr;
        }
    }
}


