#pragma once
#include"PageBase.h"
#include <easyx.h>
#include <vector>



class Page//只能添加按钮的
    :public PageBase {
private:
    IMAGE* pageImage;
    std:: vector<std::unique_ptr<ButtonBase>> buttons;
   

    int width;
    int height;

public:
	
    Page(int width, int height, const wchar_t* imagePath);
    virtual ~Page();
    virtual  void addButton(std::unique_ptr<ButtonBase> button);
  
    virtual void draw();
  //  virtual void draw(const std::wstring& basePath, int index);
    virtual void mouseClick(int mouseX, int mouseY);
    virtual void mouseMove(int mouseX, int mouseY);
    virtual void HandleMouseUp();
    virtual void KeyInput(wchar_t ch);
    virtual void Hotkeydown(BYTE as);
    virtual std::vector<std::unique_ptr<TableWidgetBase>> gettables(int num);
	
};