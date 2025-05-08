#include "page.h"

Page::Page(int width, int height, const wchar_t* imagePath) : width(width), height(height) {
    pageImage = new IMAGE(width, height);
    loadimage(pageImage, imagePath, width, height);
	//putimage(0, 0, pageImage);
   
    buttons.reserve(32);
        setfillcolor(RGB(240, 240, 240));
        solidrectangle(0, 0, width, height);
        putimage(0, 0, pageImage);
        getimage(pageImage, 0, 0, width, height);
    
}

Page::~Page() {
    delete pageImage;
}

void Page::addButton(std::unique_ptr<ButtonBase> button) {
    if (buttons.size() == buttons.capacity()) {
    
    
		buttons.reserve(buttons.size()*2);
      
    }
   
    
        buttons.push_back(std::move(button));
    
  
}



void Page::draw() {
    if (pageImage != nullptr) {
        putimage(0, 0, pageImage);
    }
    if (!buttons.empty()) {
        for (auto& button : buttons) {
            button->draw();
        }
    }
}
//void Page::draw(const std::wstring& basePath, int index)
//{
//    if (pageImage != nullptr) {
//        putimage(0, 0, pageImage);
//    }
//    if (!buttons.empty()) {
//        for (auto& button : buttons) {
//            button->draw(basePath,index);
//        }
//    }
//
//
//}
void Page::mouseClick(int mouseX, int mouseY) {
    for (auto& button : buttons) {
        if (button->checkClick(mouseX, mouseY)) {
            break;
        }
    }
}

void Page::mouseMove(int mouseX, int mouseY) {
    for (auto& button : buttons) {
        button->checkMouseOver(mouseX, mouseY);
    }
}

void Page::HandleMouseUp()
{
    for (auto& button : buttons) {
        if( button->handleMouseUp()) {
            break;
        }
    }
   
}

void Page::KeyInput(wchar_t ch)
{
    for (auto& button : buttons) {
        button->keyInput(ch);
    }
}

void Page::Hotkeydown(BYTE as)
{
    for (auto& button : buttons) {
        button->hotkeydown(as);
    }
}

std::vector<std::unique_ptr<TableWidgetBase>> Page::gettables(int num)
{
    return std::vector<std::unique_ptr<TableWidgetBase>>();
}
