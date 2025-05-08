#include "Page_and_table.h"
Page_and_table::Page_and_table(int width, int height, const wchar_t* imagePath) 
    : width(width), height(height), tableIndex(-1) {
    pageImage = new IMAGE(width, height);
    loadimage(pageImage, imagePath, width, height);
   
    tables.reserve(64);
    buttons.reserve(32);
    setfillcolor(RGB(240, 240, 240));
    solidrectangle(0, 0, width, height);
    putimage(0, 0, pageImage);
    getimage(pageImage, 0, 0, width, height);

}

Page_and_table::~Page_and_table() {
    delete pageImage;
}