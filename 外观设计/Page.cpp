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

    //// 1. 遍历所有文本框，找到被点击的文本框
    //for (auto& texstbox : texstboxs) {
    //    if (texstbox.second->checkClick(mouseX, mouseY)) {
    //        break;
    //    }
    //}
    //// 2. 取消旧文本框的选中（如果存在且不是当前点击的文本框）
    //if (currentSelectedTextBox && currentSelectedTextBox != newSelectedTextBox) {
    //    currentSelectedTextBox->deselect(); // 调用取消选中方法
    //}

    //// 3. 更新当前选中状态（newSelectedTextBox 可能为 nullptr，即点击空白区域）
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


