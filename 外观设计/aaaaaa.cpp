#include"Widget.h"
#include"easyx.h"
#include"iostream"
//#include"myButton.h"

//void button(int x, int y, int w, int h, const char* text);


ExMessage msg;
int main(int argc, char* argv[]) {
    
    //initgraph(960, 640);
   
    //IMAGE img;
    //// ���Դӵ�ǰĿ¼�����·��"./"������ͼ���ļ� "example.jpg"
    //loadimage(&img, L".//Image//�ɰ�С��.png", getwidth(), getheight());
    //    // �ڴ�������ʾͼ��
    //putimage(0, 0, &img);
    //int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    //int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    //int windowWidth = screenWidth * 0.8; // ռ��Ļ��ȵ�w %   ��ʱ1024*640 Widget widget(windowWidth, windowHeight);
    //int windowHeight = screenHeight * 0.8; // ռ��Ļ�߶ȵ�h %

    /*std::cout << "��" << windowWidth << endl;
    std::cout << "��" << windowHeight << endl;*/
    Widget widget(1024, 640);
    widget.init();
   
    widget.run();
    widget.close();

 
	
   std::cin.ignore();

    // �رջ�ͼ����
    closegraph();
    return 0;
}









		



