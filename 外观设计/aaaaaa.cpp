#include"Widget.h"
#include"easyx.h"
#include"iostream"
//#include"myButton.h"

//void button(int x, int y, int w, int h, const char* text);


ExMessage msg;
int main(int argc, char* argv[]) {
    
    //initgraph(960, 640);
   
    //IMAGE img;
    //// 尝试从当前目录（相对路径"./"）加载图像文件 "example.jpg"
    //loadimage(&img, L".//Image//可爱小狗.png", getwidth(), getheight());
    //    // 在窗口中显示图像
    //putimage(0, 0, &img);
    //int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    //int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    //int windowWidth = screenWidth * 0.8; // 占屏幕宽度的w %   此时1024*640 Widget widget(windowWidth, windowHeight);
    //int windowHeight = screenHeight * 0.8; // 占屏幕高度的h %

    /*std::cout << "宽" << windowWidth << endl;
    std::cout << "高" << windowHeight << endl;*/
    Widget widget(1024, 640);
    widget.init();
   
    widget.run();
    widget.close();

 
	
   std::cin.ignore();

    // 关闭绘图窗口
    closegraph();
    return 0;
}









		



