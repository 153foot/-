#include "Page_and_table.h"
Page_and_table::Page_and_table(int width, int height, const wchar_t* imagePath) 
    : width(width), height(height), table(nullptr), pageImage(new IMAGE(width, height)){
   
    loadimage(pageImage.get(), imagePath, width, height);
    setfillcolor(RGB(240, 240, 240));
    solidrectangle(0, 0, width, height);
    putimage(0, 0, pageImage.get());
    getimage(pageImage.get(), 0, 0, width, height);

}

Page_and_table::~Page_and_table() {
    
}