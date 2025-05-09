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
    for (auto& texstbox : texstboxs) {
        if (texstbox.second->checkClick(mouseX, mouseY)) {
            break;
        }
    }
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


