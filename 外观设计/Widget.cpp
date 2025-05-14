#include "Widget.h"

#include <conio.h>
#include <iostream>


Widget::Widget(int width, int height) : width(width), height(height),
currentIndex("主界面"), userDatabase{ {L"user003", L"pwd003"} }, adminDatabase{ {L"admin001", L"admin123"} },
keys{
            {1, L"L6Rc3K8Np2W9Xd7Jy"},
            {2, L"9gH2Q4Mb6Es8Y1Zt"},
            {3, L"W5z7Gh3PD0Jk6Fr"},
            {4, L"4Bv9a2Sn5I7Ow3Q"},
            {5, L"J8u4N7gZ6Xc1E2Tp"},
            {6, L"7YM3j5Rd8Hi0Wb9"},
            {7, L"3Fw6e9KL2q4GPs8"},
            {8, L"z2V8O3Ny5Lh7JDr6"},
            {9, L"S4pQ17Xz9g3EMu5"},
            {10, L"6Ih5J2rC8t7ZWfN"} 
}
  {//内容
   
  // 添加背景音乐
     // 打开并循环播放背景音乐
    mciSendStringW(L"open .\\bgm\\runereality.mp3 alias bgm", NULL, 0, NULL);
    mciSendStringW(L"play bgm repeat", NULL, 0, NULL);

}

Widget::~Widget() {}

void Widget::setCurrentIndex(string index_name) {

  
        currentIndex = index_name;
  

}

void Widget::init() {
    initgraph(width, height);
    setwintext();
   
    init_page0( width,  height);
    init_page1(width, height);
    init_page2(width, height);
    init_page3(width, height);
    init_page4(width, height);
    init_page5(width, height);
    init_page6(width, height);
    init_page7(width, height);
    init_page8(width, height);
    init_page9(width, height);
    init_page10(width, height);
    init_page11(width, height);
    init_page12(width, height);
    init_page13(width, height);
    init_page14(width, height);
    init_page15(width, height);
    init_page16(width, height);
    init_page17(width, height);
    init_page18(width, height);
    init_page19(width, height);
    init_page20(width, height);
    init_page21(width, height);
    init_page22(width, height);
}

void Widget::run() {
    ExMessage msg;
    BeginBatchDraw();
    cleardevice();
    while (true) {
        if (peekmessage(&msg)) {
            int mouseX = msg.x;
            int mouseY = msg.y;

            switch (msg.message) {
            case WM_LBUTTONDOWN: {
                pages[currentIndex]->mouseClick(mouseX, mouseY);
            
            }
               
               
                break;
            case WM_LBUTTONUP: {
                pages[currentIndex]->HandleMouseUp();
            
            }
                
                break;
            case WM_MOUSEMOVE: {
            
                pages[currentIndex]->mouseMove(mouseX, mouseY);
            }
                
                break;

            case WM_MOUSEWHEEL: {
                pages[currentIndex]->mouseWheel(mouseX, mouseY, msg.wheel);
            }
              
                break;

            case WM_CHAR: {
                pages[currentIndex]->KeyInput(msg.ch);
            
            }
                
                break;
            case WM_KEYDOWN: {

                pages[currentIndex]->Hotkeydown(msg.vkcode);
            
            }
              
                break;


            }
             


        }

        pages[currentIndex]->draw();
      
        FlushBatchDraw();
        Sleep(1);
    }

    EndBatchDraw();
}

void Widget::close() {
    closegraph();
}

inline void Widget::init_page0(int width, int height) {

    // 创建主界面0
    auto page0 = std::make_shared<Page>(width, height, L".//Image//可爱小狗.png");
    page0->addGIF("GIF3", std::make_unique<AnimatedGifPlayer>(0, 0, 30, 30, L"GIF//3//", 17));



    page0->addButton("订餐服务系统", std::make_unique<Ordinary_button>(300, 0, 400, 100, L"订餐服务系统"));
    page0->addButton("退出", std::make_unique<rect_button>(920, 0, 100, 50, L"退出", [=]() {
        
        exit(0); // 退出程序
    }));
    page0->addButton("注册管理员", std::make_unique<rect_button>(920, 50, 100, 50, L"成为管理员", [=]() {
        setCurrentIndex("管理员注册界面");
       
    }));
    page0->addButton("登录", std::make_unique<rect_button>(200, 450, 150, 50, L"登录", [=]() {
      //  selectbutton(ButtonID::MAIN_LOGIN);
		setCurrentIndex("登录界面");


    }));
    page0->addButton("注册", std::make_unique<rect_button>(600, 450, 150, 50, L"注册", [=]() {
		setCurrentIndex("注册界面");

      //  selectbutton(ButtonID::MAIN_REGISTER);
    }));
    pages["主界面"] = std::move(page0);
    

}
inline void Widget::init_page1(int width, int height) { // 创建登录界面1
   
    
    auto page1 = std::make_shared<Page>(width, height, L".//Image//可爱小狗.png");
   
    page1->addtexstbox("输入账号", std::make_unique<Textbox>(300, 160, 200, 30, 10, L"请输入用户账号"));
    page1->addButton("按钮0", std::make_unique<Ordinary_button>(300, 0, 400, 100, L"登录界面"));//按钮0
    page1->addButton("按钮1", std::make_unique<Ordinary_button>(80, 100, 140, 360, L"          ", RGB(245, 143, 152)));//按钮1
 



    page1->addButton("返回主界面", std::make_unique<rect_button>(920, 50, 100, 50, L"返回主界面", [=]() {//按钮2
		setCurrentIndex("主界面");
       // selectbutton(ButtonID::LOGIN_RETURN_MAIN);//

    }));

    page1->addButton("去注册！", std::make_unique<rect_button>(920, 0, 100, 50, L"去注册！", [=]() {//按钮3
		setCurrentIndex("注册界面");
       // selectbutton(ButtonID::LOGIN_GO_REGISTER);
    }));
    page1->addButton("忘记密码", std::make_unique<rect_button>(920, 100, 100, 50, L"忘记密码", [=]() {//按钮4
       // selectbutton(ButtonID::LOGIN_FORGET_PASSWORD);
    }));
    page1->addButton("用户账号1", std::make_unique<Ordinary_button>(100, 150, 100, 50, L"用户账号"));
   // page1->addButton("按钮0", std::make_unique<Ordinary_button>(300, 0, 400, 100, L"登录界面"));//按钮0

  

    page1->addButton("密码1", std::make_unique<Ordinary_button>(100, 200, 100, 50, L"账户密码"));//

    //page1->addButton("输入账号", std::make_unique<Textbox>(300, 160, 200, 30, 10, L"请输入用户账号", [=]() {//按钮7密码
    //    // selectbutton(ButtonID::LOGIN_PASSWORD);InputBox

    //    name=page1->getmassage("输入账号");
    //    
    //}));//
    // 添加文本框并保存实例
    page1->addtexstbox("输入密码", std::make_unique<Textbox>(300, 210, 200, 30, 10, L"eeeee",false));//

   
    page1->addMessageDialog(std::make_unique<MessageDialog>(510, 160, 150, 80, L"消息弹出框"));

    page1->addButton("进入", std::make_unique<rect_button>(300, 500, 400, 30, L"进入", [=]() {//9
       
        page1->setMessageDialog(pas);
        
       // MessageBoxW(NULL, pas.c_str(), _T("消息框标题"), MB_OK | MB_ICONINFORMATION);
       
    }));


    page1->addButton("用户", std::make_unique<rect_button>(100, 300, 100, 50, L"用户", [=]() {//按钮10

        pas = page1->get_texstbox_message("输入密码");
        name = page1->get_texstbox_message("输入账号");
       if( login(name, pas, false)) {
        
            std::wstring nsws = L"顾客" + name+L"欢迎光临";
            page1->setMessageDialog(nsws);
			setCurrentIndex("用户总界面");
        
       }
       else {
           page1->setMessageDialog(L"账户或密码错误");
       
       }

    }));//

    page1->addButton("管理员", std::make_unique<rect_button>(100, 350, 100, 50, L"管理员", [=]() {//按钮11
       
        pas = page1->get_texstbox_message("输入密码");
        name = page1->get_texstbox_message("输入账号");
        if (login(name, pas, true)) {
            std::wstring nsw = L"欢迎管理员" + name;
            page1->setMessageDialog(nsw);
			setCurrentIndex("管理员总界面");
        }
        else {
        
            page1->setMessageDialog(L"账户或密码错误");
        
        }
        
    }));

    pages["登录界面"] = page1;
    


}
inline void Widget::init_page2(int width, int height)
{// 创建注册页面2
    auto page2 = std::make_shared<Page>(width, height, L".//Image//MAC.png");
    /*setfillcolor(RED);
    solidrectangle(0, 0, width, height);*/
    page2->addMessageDialog(std::make_unique<MessageDialog>(510, 260, 150, 80, L"消息弹出框"));
    page2->addButton("回到主界面", std::make_unique<rect_button>(100, 150, 100, 50, L"回到主界面", [=]() {
		setCurrentIndex("主界面");
      //  selectbutton(ButtonID::REGISTER_RETURN_MAIN);


    }));
    page2->addButton("标题", std::make_unique<Ordinary_button>(300, 0, 400, 100, L"欢迎来注册(ﾉ*･ω･)ﾉ"));

    page2->addButton("用户账号", std::make_unique<rect_button>(100, 200, 100, 50, L"用户账号", [=]() {
       // selectbutton(ButtonID::REGISTER_USER_ACCOUNT);
    }));
    page2->addtexstbox("用户账输入框", std::make_unique<Textbox>(300, 210, 200, 30, 20, L"请输入用户账号"));
    page2->addButton("手机号", std::make_unique<rect_button>(100, 250, 100, 50, L"手机号", [=]() {
        //selectbutton(ButtonID::REGISTER_PHONE_NUMBER);
    }));
    page2->addtexstbox("手机号输入框", std::make_unique<Textbox>(300, 260, 200, 30, 20, L"请输入手机号"));

    page2->addButton("登录密码", std::make_unique<rect_button>(100, 300, 100, 50, L"登录密码", [=]() {
       // selectbutton(ButtonID::REGISTER_LOGIN_PASSWORD);
    }));
    page2->addtexstbox("输入密码框", std::make_unique<Textbox>(300, 310, 200, 30, 20, L"请输入密码"));
    page2->addButton("1", std::make_unique<rect_button>(100, 350, 100, 50, L"确认密码", [=]() {
       // selectbutton(ButtonID::REGISTER_CONFIRM_PASSWORD);
    }));
    page2->addtexstbox("再次确认密码框", std::make_unique<Textbox>(300, 360, 200, 30, 20, L"请再次输入密码"));
    //￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥




    page2->addButton("2", std::make_unique<rect_button>(300, 500, 400, 30, L"确认", [=]() {
      //  selectbutton(ButtonID::REGISTER_CONFIRM);
        setCurrentIndex("登录界面");

    }));
    page2->addButton("3", std::make_unique<rect_button>(920, 0, 100, 50, L"退出", [=]() {

        exit(0); // 退出程序
    }));
    page2->addButton("提交", std::make_unique<rect_button>(920, 50, 100, 50, L"提交！", [=]() {
        name = page2->get_texstbox_message("用户账输入框");
        pas = page2->get_texstbox_message("输入密码框");
        mobile_phone_number = page2->get_texstbox_message("手机号输入框");
        confirm_password_again = page2->get_texstbox_message("再次确认密码框");

        if (pas == confirm_password_again) {
            if (registerUser(name, pas, false))
            {
                page2->setMessageDialog(L"用户注册成功");
            }
            else {
                page2->setMessageDialog(L"用户已存在");
            
            }


        }
        else {
            page2->setMessageDialog(L"两次输入的密码不一致");

        }
       
    }));
    pages["注册界面"] = page2;
  
}

inline void Widget::init_page3(int width, int height)
{  //创建管理员界面3
    auto page3 = std::make_shared<Page>(width, height, L".//Image//MAC1.png");
    page3->addButton("1",std::make_unique<rect_button>(100, 100, 100, 50, L"返回主界面", [=]() {
       // selectbutton(ButtonID::ADMIN_RETURN_MAIN);
		setCurrentIndex("主界面");

    }));
    page3->addButton("2", std::make_unique<Ordinary_button>(300, 0, 400, 100, L"管理员管理界面"));//

    page3->addButton("3", std::make_unique<rect_button>(100, 150, 100, 50, L"用户管理", [=]() {
       // selectbutton(ButtonID::ADMIN_USER_MANAGEMENT);
		setCurrentIndex("用户管理界面");

    }));//
    page3->addButton("4", std::make_unique<rect_button>(100, 200, 100, 50, L"菜单管理", [=]() {
        setCurrentIndex("菜品管理界面");

    }));

    page3->addButton("5", std::make_unique<rect_button>(100, 250, 100, 50, L"订单管理", [=]() {
        setCurrentIndex("订单管理界面");

    }));//
    page3->addButton("6", std::make_unique<rect_button>(100, 300, 100, 50, L"餐桌管理", [=]() {
        setCurrentIndex("餐桌管理界面");
        
    }));
    page3->addButton("7", std::make_unique<rect_button>(100, 350, 100, 50, L"公告管理", [=]() {
        setCurrentIndex("公告管理界面");
      
    }));
    page3->addButton("8", std::make_unique<rect_button>(100, 400, 100, 50, L"库存管理", [=]() {
        setCurrentIndex("库存管理界面");
    }));
    page3->addButton("9", std::make_unique<rect_button>(100, 450, 100, 50, L"活动管理", [=]() {
        setCurrentIndex("活动管理界面");
        
    }));
    page3->addButton("11", std::make_unique<rect_button>(100, 500, 100, 50, L"评论管理", [=]() {
        setCurrentIndex("评论管理界面");
    }));
    page3->addButton("12", std::make_unique<rect_button>(100, 550, 100, 50, L"管理员管理", [=]() {
        setCurrentIndex("员工管理界面");
    }));
    page3->addButton("10", std::make_unique<rect_button>(920, 0, 100, 50, L"退出", [=]() {
        exit(0); // 退出程序

    }));
    pages["管理员总界面"] = page3;
}

inline void Widget::init_page4(int width, int height)
{//创建用户界面4
    auto page4 = std::make_shared<Page>(width, height, L".//Image//MAC1.png");

    page4->addButton("1",std::make_unique<Ordinary_button>(300, 0, 400, 100, L"欢迎来到本餐厅"));
    page4->addButton("2", std::make_unique<rect_button>(100, 100, 100, 50, L"返回登录", [=]() {
      //  selectbutton(ButtonID::USER_PAGE4_RETURN_MAIN);
        
        setCurrentIndex("登录界面");

    }));
    page4->addButton("3", std::make_unique<rect_button>(920, 0, 100, 50, L"退出", [=]() {
        exit(0); // 退出程序
        

    }));
    page4->addButton("4", std::make_unique<rect_button>(100, 150, 100, 50, L"菜单", [=]() {//
       // selectbutton(ButtonID::USER_PAGE4_MENU);用户菜单界面
        setCurrentIndex("用户菜单界面");

    }));
    page4->addButton("5", std::make_unique<rect_button>(100, 200, 100, 50, L"购物车", [=]() {//
       // selectbutton(ButtonID::USER_PAGE4_SHOPPING_CART);
        setCurrentIndex("购物车界面");

    }));
    page4->addButton("6", std::make_unique<rect_button>(100, 250, 100, 50, L"看看公告", [=]() {//
      //  selectbutton(ButtonID::USER_PAGE4_CHECK_ANNOUNCEMENT);
        setCurrentIndex("公告界面");

    }));
    page4->addButton("7", std::make_unique<rect_button>(100, 300, 100, 50, L"活动！", [=]() {//
      //  selectbutton(ButtonID::USER_PAGE4_ACTIVITY);
        setCurrentIndex("活动界面");

    }));
    page4->addButton("8", std::make_unique<rect_button>(100, 350, 100, 50, L"评论！", [=]() {//
        //  selectbutton(ButtonID::USER_PAGE4_ACTIVITY);
        setCurrentIndex("用户评论");

    }));
  

    pages["用户总界面"] = page4;
  
}

inline void Widget::init_page5(int width, int height)
{ //用户菜单界面5
    auto page5 = std::make_shared<Page>(width, height, L".//Image//3.jpg");
    page5->addButton("1",std::make_unique<Ordinary_button>(300, 0, 400, 100, L"菜单"));
    page5->addButton("1", std::make_unique<rect_button>(0, 0, 100, 20, L"返回", [=]() {
      //  selectbutton(ButtonID::USER_PAGE5_RETURN_USER_MAIN);

    }));
    page5->addButton("1", std::make_unique<rect_button>(920, 0, 100, 50, L"用户主界面", [=]() {
      //  selectbutton(ButtonID::USER_PAGE4_EXIT);

    }));

    page5->addButton("1", std::make_unique<rect_button>(0, 20, 100, 20, L"查看购物车", [=]() {//
      //  selectbutton(ButtonID::USER_PAGE4_SHOPPING_CART);

    }));
    page5->addButton("1", std::make_unique<rect_button>(0, 40, 100, 20, L"查看公告", [=]() {//
      //  selectbutton(ButtonID::USER_PAGE4_CHECK_ANNOUNCEMENT);

    }));
    page5->addButton("1", std::make_unique<rect_button>(0, 60, 100, 20, L"活动！", [=]() {//
      //  selectbutton(ButtonID::USER_PAGE4_ACTIVITY);

    }));
    page5->addButton("1", std::make_unique<rect_button>(0, 80, 100, 20, L"去评价", [=]() {//
      //  selectbutton(ButtonID::USER_PAGE4_GO_EVALUATE);

    }));//划线了
    pages["用户菜"] = page5;
    
}

inline void Widget::init_page6(int width, int height)
{//测试！！！！！！！！！！222！！！￥￥￥￥￥￥￥￥￥
    auto page6 = std::make_shared<Page_and_table>(width, height, L".//Image//3.jpg");
 

     std::vector<std::wstring> ADMIN_HEADERS = {
       L"管理员ID", L"管理员用户名", L"管理员密码", L"管理员姓名",
       L"联系方式", L"权限等级", L"权限列表", L"入职日期",
       L"最后登录时间"
    };
    page6->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page6->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "管理员.csv", ADMIN_HEADERS);
  
    page6->get_texstbox_message("信息输入");
    page6->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page6->addButton("1",std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
     //   setCurrentIndex(0);//测试用

    }));
    page6->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page6->updata();

    }));
    page6->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page6->extraction_data();

    }));
    //page6->addButton("提取", std::make_unique<rect_button>(0, 0, 100, 20, L"获取！", [=]() {//
    //    page6->extraction_data();

    //}));
    page6->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"添加活动", [=]() {//
        
        this->input_information = page6->get_texstbox_message("信息输入");
        std::wstring infor = input_information;
        
        
        page6->addRow(infor, page6->get_this_MessageDialo());

    }));
    page6->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找活动", [=]() {//
       this->input_information = page6->get_texstbox_message("信息输入"); 
        std::wstring row = L"";
      

            // 将用户输入转换为数字
            int r = _wtoi(input_information.c_str());
            if (r > 0 && r < page6->Cell_num()) {
                row = page6->search_ID(r, page6->get_this_MessageDialo());
                page6->setMessageDialog(row);
               // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
            }
            else {
                page6->setMessageDialog(_T("输入ID号错误"));
               // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
            }


        

       

    }));
    page6->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"修改活动", [=]() {//
        int row = 0;
        int columnstart = 0;
        int columnend = 0;
        this->input_information = page6->get_texstbox_message("信息输入");
       
        std::wstring Wide_string = input_information;

        std::vector<std::wstring> extracted_data =this->split_input_String_to_updateRow(Wide_string,L'|',row, columnstart, columnend);
        
        
        page6->updateRow(row, columnstart, columnend, extracted_data, page6->get_this_MessageDialo());

    }));
    page6->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"删除活动", [=]() {//
        this->input_information = page6->get_texstbox_message("信息输入");
        std::wstring input_infor = input_information;
      

            // 将用户输入转换为数字
            int r = _wtoi(input_infor.c_str());
            if (r > 0 && r < page6->Cell_num()) {
                page6->deleteSelectedRow(r);

            }
            else {
                page6->setMessageDialog(_T("输入ID号错误"));
                //MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
            }
        
        
        
      
       
           

    }));


    page6->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"活动管理界面"));
    pages["管理员活动管理界面"] = page6;
   


}

void Widget::init_page7(int width, int height)
{
    auto page7 = std::make_shared<Page>(width, height, L".//Image//MAC.png");
    /*setfillcolor(RED);
    solidrectangle(0, 0, width, height);*/
    page7->addMessageDialog(std::make_unique<MessageDialog>(510, 260, 150, 80, L"消息弹出框"));
    page7->addButton("回到主界面", std::make_unique<rect_button>(100, 150, 100, 50, L"回到主界面", [=]() {
        setCurrentIndex("主界面");
        //  selectbutton(ButtonID::REGISTER_RETURN_MAIN);


    }));
    page7->addButton("标题", std::make_unique<Ordinary_button>(300, 0, 400, 100, L"欢迎注册管理员(ﾉ*･ω･)ﾉ"));

    page7->addButton("用户账号", std::make_unique<rect_button>(100, 200, 100, 50, L"账号", [=]() {
        // selectbutton(ButtonID::REGISTER_USER_ACCOUNT);
    }));
    page7->addtexstbox("用户账输入框", std::make_unique<Textbox>(300, 210, 200, 30, 20, L"请输入用户账号"));
    page7->addButton("手机号", std::make_unique<rect_button>(100, 250, 100, 50, L"手机号", [=]() {
        //selectbutton(ButtonID::REGISTER_PHONE_NUMBER);
    }));
    page7->addtexstbox("手机号输入框", std::make_unique<Textbox>(300, 260, 200, 30, 20, L"请输入手机号"));

    page7->addButton("登录密码", std::make_unique<rect_button>(100, 300, 100, 50, L"登录密码", [=]() {
        // selectbutton(ButtonID::REGISTER_LOGIN_PASSWORD);
    }));
    page7->addtexstbox("输入密码框", std::make_unique<Textbox>(300, 310, 200, 30, 20, L"请输入密码"));
    page7->addButton("1", std::make_unique<rect_button>(100, 350, 100, 50, L"确认密码", [=]() {
        // selectbutton(ButtonID::REGISTER_CONFIRM_PASSWORD);
    }));
    page7->addtexstbox("再次确认密码框", std::make_unique<Textbox>(300, 360, 200, 30, 20, L"请再次输入密码"));
    //￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥
    page7->addButton("密钥", std::make_unique<rect_button>(100, 400, 100, 50, L"输入密钥", [=]() {
        // selectbutton(ButtonID::REGISTER_CONFIRM_PASSWORD);
    }));
    page7->addtexstbox("输入密钥框", std::make_unique<Textbox>(300, 410, 200, 30, 20, L"请输入密钥"));

    

    page7->addButton("2", std::make_unique<rect_button>(300, 500, 400, 30, L"确认", [=]() {
        //  selectbutton(ButtonID::REGISTER_CONFIRM);
        setCurrentIndex("登录界面");

    }));
    page7->addButton("3", std::make_unique<rect_button>(920, 0, 100, 50, L"退出", [=]() {

        exit(0); // 退出程序
    }));
    page7->addButton("提交", std::make_unique<rect_button>(920, 50, 100, 50, L"提交！", [=]() {
        name = page7->get_texstbox_message("用户账输入框");
        pas = page7->get_texstbox_message("输入密码框");
        mobile_phone_number = page7->get_texstbox_message("手机号输入框");
        confirm_password_again = page7->get_texstbox_message("再次确认密码框");
        inputkey = page7->get_texstbox_message("输入密钥框");

        std::wstring errorMessage;

        // 检查密钥
        if (!checkKey(inputkey)) {
            errorMessage += L"输入的密钥错误\n";
        }

        // 检查密码一致性
        if (pas != confirm_password_again) {
            errorMessage += L"两次输入的密码不一致\n";
        }

        if (errorMessage.empty()) {
            // 密钥正确，密码一致，尝试注册
            if (registerUser(name, pas, false)) {
                page7->setMessageDialog(L"用户注册成功");
            }
            else {
                page7->setMessageDialog(L"用户已存在");
            }
        }
        else {
            // 显示所有错误
            page7->setMessageDialog(errorMessage);
        }
    }));
    pages["管理员注册界面"] = page7;


}

void Widget::init_page8(int width, int height){//用户管理

    auto page8 = std::make_shared<Page_and_table>(width, height, L".//Image//4.jpg");


     std::vector<std::wstring> USER_HEADERS = {
    L"用户ID", L"用户名", L"密码", L"姓名",
    L"联系方式", L"余额", L"订单数量", L"积分",
    L"最后登录时间"
    };
    page8->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page8->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/用户.csv", USER_HEADERS);

    page8->get_texstbox_message("信息输入");
    page8->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page8->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("管理员总界面");
        

    }));
    page8->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page8->updata();

    }));
    page8->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page8->extraction_data();

    }));
    //page8->addButton("提取", std::make_unique<rect_button>(0, 0, 100, 20, L"获取！", [=]() {//
    //    page8->extraction_data();

    //}));
    page8->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"添加用户", [=]() {//

        this->input_information = page8->get_texstbox_message("信息输入");
        std::wstring infor = input_information;


        page8->addRow(infor, page8->get_this_MessageDialo());

    }));
    page8->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找用户", [=]() {//
        this->input_information = page8->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page8->Cell_num()) {
            row = page8->search_ID(r, page8->get_this_MessageDialo());
            page8->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page8->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }






    }));
    page8->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"修改用户", [=]() {//
        int row = 0;
        int columnstart = 0;
        int columnend = 0;
        this->input_information = page8->get_texstbox_message("信息输入");

        std::wstring Wide_string = input_information;

        std::vector<std::wstring> extracted_data = this->split_input_String_to_updateRow(Wide_string, L'|', row, columnstart, columnend);


        page8->updateRow(row, columnstart, columnend, extracted_data, page8->get_this_MessageDialo());

    }));
    page8->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"删除用户", [=]() {//
        this->input_information = page8->get_texstbox_message("信息输入");
        std::wstring input_infor = input_information;


        // 将用户输入转换为数字
        int r = _wtoi(input_infor.c_str());
        if (r > 0 && r < page8->Cell_num()) {
            page8->deleteSelectedRow(r);

        }
        else {
            page8->setMessageDialog(_T("输入ID号错误"));
            //MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }







    }));


    page8->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"用户管理界面"));
    pages["用户管理界面"] = page8;


}

void Widget::init_page9(int width, int height)//管理员菜单管理界面
{
    auto page9 = std::make_shared<Page_and_table>(width, height, L".//Image//5.jpg");


    std::vector<std::wstring> DISH_HEADERS = {
    L"菜品ID", L"菜品名称", L"菜品描述", L"菜品价格",
    L"库存数量", L"类别ID", L"类别名称", L"是否可用",
    L"是否推荐"
    };
    page9->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page9->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/菜品.csv", DISH_HEADERS);

    page9->get_texstbox_message("信息输入");
    page9->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page9->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("管理员总界面");


    }));
    page9->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page9->updata();

    }));
    page9->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page9->extraction_data();

    }));
   
    page9->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"添加菜品", [=]() {//

        this->input_information = page9->get_texstbox_message("信息输入");
        std::wstring infor = input_information;


        page9->addRow(infor, page9->get_this_MessageDialo());

    }));
    page9->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找菜品", [=]() {//
        this->input_information = page9->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page9->Cell_num()) {
            row = page9->search_ID(r, page9->get_this_MessageDialo());
            page9->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page9->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }






    }));
    page9->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"更改菜品", [=]() {//
        int row = 0;
        int columnstart = 0;
        int columnend = 0;
        this->input_information = page9->get_texstbox_message("信息输入");

        std::wstring Wide_string = input_information;

        std::vector<std::wstring> extracted_data = this->split_input_String_to_updateRow(Wide_string, L'|', row, columnstart, columnend);


        page9->updateRow(row, columnstart, columnend, extracted_data, page9->get_this_MessageDialo());

    }));
    page9->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"删除菜品", [=]() {//
        this->input_information = page9->get_texstbox_message("信息输入");
        std::wstring input_infor = input_information;


        // 将用户输入转换为数字
        int r = _wtoi(input_infor.c_str());
        if (r > 0 && r < page9->Cell_num()) {
            page9->deleteSelectedRow(r);

        }
        else {
            page9->setMessageDialog(_T("输入ID号错误"));
            //MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }



    }));


    page9->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"菜品管理界面"));
    pages["菜品管理界面"] = page9;

}

void Widget::init_page10(int width, int height)//订单管理
{
    auto page10 = std::make_shared<Page_and_table>(width, height, L".//Image//2.jpg");


    std::vector<std::wstring> ORDER_HEADERS = {
    L"订单ID", L"用户ID", L"订单创建时间", L"菜品数量",
    L"菜品ID", L"订单状态", L"支付方式", L"总价",
    L"餐桌ID", L"餐桌编号"
    };
    page10->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page10->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/订单表.csv", ORDER_HEADERS);

    page10->get_texstbox_message("信息输入");
    page10->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page10->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("管理员总界面");


    }));
    page10->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page10->updata();

    }));
    page10->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page10->extraction_data();

    }));

    page10->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"创建订单", [=]() {//

        this->input_information = page10->get_texstbox_message("信息输入");
        std::wstring infor = input_information;


        page10->addRow(infor, page10->get_this_MessageDialo());

    }));
    page10->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找订单", [=]() {//
        this->input_information = page10->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page10->Cell_num()) {
            row = page10->search_ID(r, page10->get_this_MessageDialo());
            page10->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page10->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }






    }));
    page10->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"更改订单", [=]() {//
        int row = 0;
        int columnstart = 0;
        int columnend = 0;
        this->input_information = page10->get_texstbox_message("信息输入");

        std::wstring Wide_string = input_information;

        std::vector<std::wstring> extracted_data = this->split_input_String_to_updateRow(Wide_string, L'|', row, columnstart, columnend);


        page10->updateRow(row, columnstart, columnend, extracted_data, page10->get_this_MessageDialo());

    }));
    page10->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"删除订单", [=]() {//
        this->input_information = page10->get_texstbox_message("信息输入");
        std::wstring input_infor = input_information;


        // 将用户输入转换为数字
        int r = _wtoi(input_infor.c_str());
        if (r > 0 && r < page10->Cell_num()) {
            page10->deleteSelectedRow(r);

        }
        else {
            page10->setMessageDialog(_T("输入ID号错误"));
            //MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }



    }));


    page10->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"订单管理界面"));
    pages["订单管理界面"] = page10;


}

void Widget::init_page11(int width, int height)//餐桌管理
{
    auto page11 = std::make_shared<Page_and_table>(width, height, L".//Image//2.jpg");


    std::vector<std::wstring> TABLE_HEADERS = {
     L"餐桌ID", L"餐桌名称", L"区域", L"状态",
     L"最后更新时间", L"预订用户ID", L"预订开始时间", L"预订结束时间"
    };
    page11->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page11->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/餐桌.csv", TABLE_HEADERS);

    page11->get_texstbox_message("信息输入");
    page11->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page11->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("管理员总界面");


    }));
    page11->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page11->updata();

    }));
    page11->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page11->extraction_data();

    }));

    page11->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"新建餐桌", [=]() {//

        this->input_information = page11->get_texstbox_message("信息输入");
        std::wstring infor = input_information;


        page11->addRow(infor, page11->get_this_MessageDialo());

    }));
    page11->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找餐桌", [=]() {//
        this->input_information = page11->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page11->Cell_num()) {
            row = page11->search_ID(r, page11->get_this_MessageDialo());
            page11->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page11->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }






    }));
    page11->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"修改餐桌", [=]() {//
        int row = 0;
        int columnstart = 0;
        int columnend = 0;
        this->input_information = page11->get_texstbox_message("信息输入");

        std::wstring Wide_string = input_information;

        std::vector<std::wstring> extracted_data = this->split_input_String_to_updateRow(Wide_string, L'|', row, columnstart, columnend);


        page11->updateRow(row, columnstart, columnend, extracted_data, page11->get_this_MessageDialo());

    }));
    page11->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"删除餐桌", [=]() {//
        this->input_information = page11->get_texstbox_message("信息输入");
        std::wstring input_infor = input_information;


        // 将用户输入转换为数字
        int r = _wtoi(input_infor.c_str());
        if (r > 0 && r < page11->Cell_num()) {
            page11->deleteSelectedRow(r);

        }
        else {
            page11->setMessageDialog(_T("输入ID号错误"));
            //MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }



    }));


    page11->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"餐桌管理界面"));
    pages["餐桌管理界面"] = page11;


}

void Widget::init_page12(int width, int height)//公告管理
{
    auto page12 = std::make_shared<Page_and_table>(width, height, L".//Image//2.jpg");


    std::vector<std::wstring> ANNOUNCEMENT_HEADERS = {
     L"公告ID", L"标题", L"内容", L"发布时间",
     L"是否置顶", L"发布人ID"
    };
    page12->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page12->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/公告表.csv", ANNOUNCEMENT_HEADERS);

    page12->get_texstbox_message("信息输入");
    page12->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page12->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("管理员总界面");


    }));
    page12->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page12->updata();

    }));
    page12->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page12->extraction_data();

    }));

    page12->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"新建公告", [=]() {//

        this->input_information = page12->get_texstbox_message("信息输入");
        std::wstring infor = input_information;


        page12->addRow(infor, page12->get_this_MessageDialo());

    }));
    page12->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找公告", [=]() {//
        this->input_information = page12->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page12->Cell_num()) {
            row = page12->search_ID(r, page12->get_this_MessageDialo());
            page12->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page12->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }






    }));
    page12->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"修改公告", [=]() {//
        int row = 0;
        int columnstart = 0;
        int columnend = 0;
        this->input_information = page12->get_texstbox_message("信息输入");

        std::wstring Wide_string = input_information;

        std::vector<std::wstring> extracted_data = this->split_input_String_to_updateRow(Wide_string, L'|', row, columnstart, columnend);


        page12->updateRow(row, columnstart, columnend, extracted_data, page12->get_this_MessageDialo());

    }));
    page12->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"删除公告", [=]() {//
        this->input_information = page12->get_texstbox_message("信息输入");
        std::wstring input_infor = input_information;


        // 将用户输入转换为数字
        int r = _wtoi(input_infor.c_str());
        if (r > 0 && r < page12->Cell_num()) {
            page12->deleteSelectedRow(r);

        }
        else {
            page12->setMessageDialog(_T("输入ID号错误"));
            //MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }



    }));


    page12->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"公告管理界面"));
    pages["公告管理界面"] = page12;



}

void Widget::init_page13(int width, int height)//库存管理
{
    auto page13 = std::make_shared<Page_and_table>(width, height, L".//Image//2.jpg");


    std::vector<std::wstring> INVENTORY_HEADERS = {
     L"库存ID", L"物品名称", L"单位", L"当前数量",
     L"最低数量", L"最高数量", L"最后采购时间", L"最后采购数量",
     L"最后消耗时间", L"最后消耗数量", L"是否启用", L"备注"
    };
    page13->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page13->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/库存.csv", INVENTORY_HEADERS);

    page13->get_texstbox_message("信息输入");
    page13->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page13->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("管理员总界面");


    }));
    page13->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page13->updata();

    }));
    page13->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page13->extraction_data();

    }));

    page13->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"添加库存", [=]() {//

        this->input_information = page13->get_texstbox_message("信息输入");
        std::wstring infor = input_information;


        page13->addRow(infor, page13->get_this_MessageDialo());

    }));
    page13->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找食材", [=]() {//
        this->input_information = page13->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page13->Cell_num()) {
            row = page13->search_ID(r, page13->get_this_MessageDialo());
            page13->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page13->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }






    }));
    page13->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"修改库存", [=]() {//
        int row = 0;
        int columnstart = 0;
        int columnend = 0;
        this->input_information = page13->get_texstbox_message("信息输入");

        std::wstring Wide_string = input_information;

        std::vector<std::wstring> extracted_data = this->split_input_String_to_updateRow(Wide_string, L'|', row, columnstart, columnend);


        page13->updateRow(row, columnstart, columnend, extracted_data, page13->get_this_MessageDialo());

    }));
    page13->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"删除库存", [=]() {//
        this->input_information = page13->get_texstbox_message("信息输入");
        std::wstring input_infor = input_information;


        // 将用户输入转换为数字
        int r = _wtoi(input_infor.c_str());
        if (r > 0 && r < page13->Cell_num()) {
            page13->deleteSelectedRow(r);

        }
        else {
            page13->setMessageDialog(_T("输入ID号错误"));
            //MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }



    }));


    page13->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"库存管理界面"));
    pages["库存管理界面"] = page13;
    

}

void Widget::init_page14(int width, int height)//活动管理
{
    auto page14 = std::make_shared<Page_and_table>(width, height, L".//Image//2.jpg");


    std::vector<std::wstring> ACTIVITY_HEADERS = {
     L"活动ID", L"活动名称", L"活动描述", L"开始时间",
     L"结束时间", L"优惠类型", L"满减金额", L"折扣金额",
     L"折扣率", L"赠品名称", L"适用菜品ID", L"适用餐桌类型",
     L"活动状态"
    };
    page14->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page14->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/活动.csv", ACTIVITY_HEADERS);

    page14->get_texstbox_message("信息输入");
    page14->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page14->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("管理员总界面");


    }));
    page14->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page14->updata();

    }));
    page14->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page14->extraction_data();

    }));

    page14->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"新建活动", [=]() {//

        this->input_information = page14->get_texstbox_message("信息输入");
        std::wstring infor = input_information;


        page14->addRow(infor, page14->get_this_MessageDialo());

    }));
    page14->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找活动", [=]() {//
        this->input_information = page14->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page14->Cell_num()) {
            row = page14->search_ID(r, page14->get_this_MessageDialo());
            page14->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page14->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }


    }));
    page14->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"修改活动", [=]() {//
        int row = 0;
        int columnstart = 0;
        int columnend = 0;
        this->input_information = page14->get_texstbox_message("信息输入");

        std::wstring Wide_string = input_information;

        std::vector<std::wstring> extracted_data = this->split_input_String_to_updateRow(Wide_string, L'|', row, columnstart, columnend);


        page14->updateRow(row, columnstart, columnend, extracted_data, page14->get_this_MessageDialo());

    }));
    page14->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"删除活动", [=]() {//
        this->input_information = page14->get_texstbox_message("信息输入");
        std::wstring input_infor = input_information;


        // 将用户输入转换为数字
        int r = _wtoi(input_infor.c_str());
        if (r > 0 && r < page14->Cell_num()) {
            page14->deleteSelectedRow(r);

        }
        else {
            page14->setMessageDialog(_T("输入ID号错误"));
            //MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }



    }));


    page14->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"活动管理界面"));
    pages["活动管理界面"] = page14;

}

void Widget::init_page15(int width, int height)//评论管理
{
    auto page15 = std::make_shared<Page_and_table>(width, height, L".//Image//2.jpg");


    std::vector<std::wstring> MESSAGE_HEADERS = {
      L"消息ID", L"发送者ID", L"发送者类型", L"消息标题",
      L"消息内容", L"消息时间", L"订单ID", L"餐桌ID",
      L"处理状态", L"处理时间", L"处理者ID"
    };
    page15->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page15->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/评论表.csv", MESSAGE_HEADERS);

    page15->get_texstbox_message("信息输入");
    page15->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page15->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("管理员总界面");


    }));
    page15->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page15->updata();

    }));
    page15->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page15->extraction_data();

    }));

    page15->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"添加评论", [=]() {//

        this->input_information = page15->get_texstbox_message("信息输入");
        std::wstring infor = input_information;


        page15->addRow(infor, page15->get_this_MessageDialo());

    }));
    page15->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找评论", [=]() {//
        this->input_information = page15->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page15->Cell_num()) {
            row = page15->search_ID(r, page15->get_this_MessageDialo());
            page15->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page15->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }


    }));
    page15->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"修改评论", [=]() {//
        int row = 0;
        int columnstart = 0;
        int columnend = 0;
        this->input_information = page15->get_texstbox_message("信息输入");

        std::wstring Wide_string = input_information;

        std::vector<std::wstring> extracted_data = this->split_input_String_to_updateRow(Wide_string, L'|', row, columnstart, columnend);


        page15->updateRow(row, columnstart, columnend, extracted_data, page15->get_this_MessageDialo());

    }));
    page15->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"删除评论", [=]() {//
        this->input_information = page15->get_texstbox_message("信息输入");
        std::wstring input_infor = input_information;


        // 将用户输入转换为数字
        int r = _wtoi(input_infor.c_str());
        if (r > 0 && r < page15->Cell_num()) {
            page15->deleteSelectedRow(r);

        }
        else {
            page15->setMessageDialog(_T("输入ID号错误"));
            //MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }



    }));


    page15->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"评论管理界面"));
    pages["评论管理界面"] = page15;

}

void Widget::init_page16(int width, int height)//管理员管理界面
{
    auto page16 = std::make_shared<Page_and_table>(width, height, L".//Image//2.jpg");


    std::vector<std::wstring> ADMIN_HEADERS = {
     L"管理员ID", L"管理员用户名", L"管理员密码", L"管理员姓名",
     L"联系方式", L"权限等级", L"权限列表", L"入职日期",
     L"最后登录时间"
    };
    page16->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page16->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/管理员.csv", ADMIN_HEADERS);

    page16->get_texstbox_message("信息输入");
    page16->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page16->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("管理员总界面");


    }));
    page16->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page16->updata();

    }));
    page16->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page16->extraction_data();

    }));

    page16->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"添加员工", [=]() {//

        this->input_information = page16->get_texstbox_message("信息输入");
        std::wstring infor = input_information;


        page16->addRow(infor, page16->get_this_MessageDialo());

    }));
    page16->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找员工", [=]() {//
        this->input_information = page16->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page16->Cell_num()) {
            row = page16->search_ID(r, page16->get_this_MessageDialo());
            page16->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page16->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }


    }));
    page16->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"修改员工", [=]() {//
        int row = 0;
        int columnstart = 0;
        int columnend = 0;
        this->input_information = page16->get_texstbox_message("信息输入");

        std::wstring Wide_string = input_information;

        std::vector<std::wstring> extracted_data = this->split_input_String_to_updateRow(Wide_string, L'|', row, columnstart, columnend);


        page16->updateRow(row, columnstart, columnend, extracted_data, page16->get_this_MessageDialo());

    }));
    page16->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"删除员工", [=]() {//
        this->input_information = page16->get_texstbox_message("信息输入");
        std::wstring input_infor = input_information;


        // 将用户输入转换为数字
        int r = _wtoi(input_infor.c_str());
        if (r > 0 && r < page16->Cell_num()) {
            page16->deleteSelectedRow(r);

        }
        else {
            page16->setMessageDialog(_T("输入ID号错误"));
            //MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }



    }));


    page16->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"员工管理界面"));
    pages["员工管理界面"] = page16;

}

void Widget::init_page17(int width, int height)//点菜
{
    auto page17 = std::make_shared<Page_and_table>(width, height, L".//Image//2.jpg");


    std::vector<std::wstring> DISH_HEADERS = {
    L"菜品ID", L"菜品名称", L"菜品描述", L"菜品价格",
    L"库存数量", L"类别ID", L"类别名称", L"是否可用",
    L"是否推荐"
    };
    page17->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page17->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/菜品.csv", DISH_HEADERS);

    page17->get_texstbox_message("信息输入");
    page17->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page17->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("用户总界面");


    }));
    page17->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page17->updata();

    }));
    page17->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page17->extraction_data();

    }));
    page17->addButton("23", std::make_unique<rect_button>(920, 60, 100, 20, L"评论！", [=]() {//
       

    }));

    page17->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"下单", [=]() {//

        this->input_information = page17->get_texstbox_message("信息输入");
        std::wstring infor = input_information;


        page17->addRow(infor, page17->get_this_MessageDialo());

    }));
    page17->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找菜品", [=]() {//
        this->input_information = page17->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page17->Cell_num()) {
            row = page17->search_ID(r, page17->get_this_MessageDialo());
            page17->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page17->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }


    }));
    page17->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L" 查看活动", [=]() {//
        setCurrentIndex("活动界面");

    }));
    page17->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"查看公告", [=]() {//
        setCurrentIndex("公告界面");


    }));


    page17->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"用户菜单界面"));
    pages["用户菜单界面"] = page17;

}

void Widget::init_page18(int width, int height)//购物车界面
{
    auto page18 = std::make_shared<Page_and_table>(width, height, L".//Image//MAC2.png");


    std::vector<std::wstring> CART_HEADERS = {
    L"购物车ID", L"菜品名称", L"单价", L"数量",
    L"总价", L"添加时间"
    };
    page18->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page18->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/购物车.csv", CART_HEADERS);

    page18->get_texstbox_message("信息输入");
    page18->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page18->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("用户总界面");


    }));
    page18->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page18->updata();

    }));
    page18->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page18->extraction_data();

    }));
    page18->addButton("23", std::make_unique<rect_button>(920, 60, 100, 20, L"评论！", [=]() {//
        setCurrentIndex("用户评论");

    }));

    page18->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"计算总价", [=]() {//

        this->input_information = page18->get_texstbox_message("信息输入");
        std::wstring infor = input_information;


        page18->addRow(infor, page18->get_this_MessageDialo());

    }));
    page18->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找订单", [=]() {//
        this->input_information = page18->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page18->Cell_num()) {
            row = page18->search_ID(r, page18->get_this_MessageDialo());
            page18->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page18->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }


    }));
    page18->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"修改订单", [=]() {//
        int row = 0;
        int columnstart = 0;
        int columnend = 0;
        this->input_information = page18->get_texstbox_message("信息输入");

        std::wstring Wide_string = input_information;

        std::vector<std::wstring> extracted_data = this->split_input_String_to_updateRow(Wide_string, L'|', row, columnstart, columnend);


        page18->updateRow(row, columnstart, columnend, extracted_data, page18->get_this_MessageDialo());

    }));
    page18->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"删除订单", [=]() {//
        this->input_information = page18->get_texstbox_message("信息输入");
        std::wstring input_infor = input_information;


        // 将用户输入转换为数字
        int r = _wtoi(input_infor.c_str());
        if (r > 0 && r < page18->Cell_num()) {
            page18->deleteSelectedRow(r);

        }
        else {
            page18->setMessageDialog(_T("输入ID号错误"));
            //MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }



    }));


    page18->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"购物车界面"));
    pages["购物车界面"] = page18;

}

void Widget::init_page19(int width, int height)//用户公告
{
    auto page19 = std::make_shared<Page_and_table>(width, height, L".//Image//2.jpg");


    std::vector<std::wstring> ANNOUNCEMENT_HEADERS = {
     L"公告ID", L"标题", L"内容", L"发布时间",
     L"是否置顶", L"发布人ID"
    };
    page19->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page19->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/公告表.csv", ANNOUNCEMENT_HEADERS);

    page19->get_texstbox_message("信息输入");
    page19->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page19->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("用户总界面");


    }));
    page19->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page19->updata();

    }));
    page19->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page19->extraction_data();

    }));

    page19->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"去评论", [=]() {//
        setCurrentIndex("用户评论");
       

    }));
    page19->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找公告", [=]() {//
        this->input_information = page19->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page19->Cell_num()) {
            row = page19->search_ID(r, page19->get_this_MessageDialo());
            page19->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page19->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }






    }));
    page19->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"点菜", [=]() {//
        setCurrentIndex("用户菜单界面");

    }));
    page19->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"活动", [=]() {//
        setCurrentIndex("活动界面");



    }));


    page19->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"公告界面"));
    pages["公告界面"] = page19;
}

void Widget::init_page20(int width, int height)//活动界面
{
    auto page20 = std::make_shared<Page_and_table>(width, height, L".//Image//2.jpg");


    std::vector<std::wstring> ACTIVITY_HEADERS = {
     L"活动ID", L"活动名称", L"活动描述", L"开始时间",
     L"结束时间", L"优惠类型", L"满减金额", L"折扣金额",
     L"折扣率", L"赠品名称", L"适用菜品ID", L"适用餐桌类型",
     L"活动状态"
    };
    page20->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page20->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/活动.csv", ACTIVITY_HEADERS);

    page20->get_texstbox_message("信息输入");
    page20->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page20->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("用户总界面");


    }));
    page20->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page20->updata();

    }));
    page20->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page20->extraction_data();

    }));

    page20->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"去评论", [=]() {//
        setCurrentIndex("用户评论");
       

    }));
    page20->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找活动", [=]() {//
        this->input_information = page20->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page20->Cell_num()) {
            row = page20->search_ID(r, page20->get_this_MessageDialo());
            page20->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page20->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }


    }));
    page20->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"点菜", [=]() {//
        setCurrentIndex("用户菜单界面");

    }));
    page20->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"查看公告", [=]() {//
        setCurrentIndex("公告界面");

    }));


    page20->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"活动界面"));
    pages["活动界面"] = page20;

}

void Widget::init_page21(int width, int height)//用户评论
{
    auto page21 = std::make_shared<Page_and_table>(width, height, L".//Image//2.jpg");


    std::vector<std::wstring> MESSAGE_HEADERS = {
      L"消息ID", L"发送者ID", L"发送者类型", L"消息标题",
      L"消息内容", L"消息时间", L"订单ID", L"餐桌ID",
      L"处理状态", L"处理时间", L"处理者ID"
    };
    page21->addtexstbox("信息输入", std::make_unique<Textbox>(100, 88, 900, 30, 100, L"信息输入"));
    page21->maketable(std::make_shared<TableWidget>(100, 120, 920, 300, 8, 5), "data/评论表.csv", MESSAGE_HEADERS);

    page21->get_texstbox_message("信息输入");
    page21->addMessageDialog(std::make_unique<MessageDialog>(220, 450, 585, 60, L"消息弹出框"));
    page21->addButton("1", std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [=]() {//
        //   setCurrentIndex(0);//测试用
        setCurrentIndex("用户总界面");


    }));
    page21->addButton("1111", std::make_unique<rect_button>(920, 30, 100, 20, L"提交！", [=]() {//
        page21->updata();

    }));
    page21->addButton("11", std::make_unique<rect_button>(920, 60, 100, 20, L"获取！", [=]() {//
        page21->extraction_data();

    }));

    page21->addButton("2", std::make_unique<rect_button>(120, 450, 90, 20, L"去评论", [=]() {//

        this->input_information = page21->get_texstbox_message("信息输入");
        std::wstring infor = input_information;


        page21->addRow(infor, page21->get_this_MessageDialo());

    }));
    page21->addButton("3", std::make_unique<rect_button>(820, 450, 90, 20, L"查找评论", [=]() {//
        this->input_information = page21->get_texstbox_message("信息输入");
        std::wstring row = L"";


        // 将用户输入转换为数字
        int r = _wtoi(input_information.c_str());
        if (r > 0 && r < page21->Cell_num()) {
            row = page21->search_ID(r, page21->get_this_MessageDialo());
            page21->setMessageDialog(row);
            // MessageBoxW(NULL, row.c_str(), _T("警告"), MB_OK | MB_ICONWARNING);
        }
        else {
            page21->setMessageDialog(_T("输入ID号错误"));
            // MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }


    }));
    page21->addButton("4", std::make_unique<rect_button>(120, 478, 90, 20, L"修改", [=]() {//
        int row = 0;
        int columnstart = 0;
        int columnend = 0;
        this->input_information = page21->get_texstbox_message("信息输入");

        std::wstring Wide_string = input_information;

        std::vector<std::wstring> extracted_data = this->split_input_String_to_updateRow(Wide_string, L'|', row, columnstart, columnend);


        page21->updateRow(row, columnstart, columnend, extracted_data, page21->get_this_MessageDialo());

    }));
    page21->addButton("5", std::make_unique<rect_button>(820, 478, 90, 20, L"撤回", [=]() {//
        this->input_information = page21->get_texstbox_message("信息输入");
        std::wstring input_infor = input_information;


        // 将用户输入转换为数字
        int r = _wtoi(input_infor.c_str());
        if (r > 0 && r < page21->Cell_num()) {
            page21->deleteSelectedRow(r);

        }
        else {
            page21->setMessageDialog(_T("输入ID号错误"));
            //MessageBoxW(NULL, _T("输入ID号错误"), _T("警告"), MB_OK | MB_ICONWARNING);
        }



    }));


    page21->addButton("6", std::make_unique<Ordinary_button>(300, 0, 400, 50, L"用户评论"));
    pages["用户评论"] = page21;


}

void Widget::init_page22(int width, int height)//将计就计哦加哦i
{ // 创建主界面0
    auto page22 = std::make_shared<Page>(width, height, L".//Image//可爱小狗.png");
    page22->addGIF("GIF3", std::make_unique<AnimatedGifPlayer>(0, 0, 30, 30, L"GIF//3//", 17));



    page22->addButton("订餐服务系统", std::make_unique<Ordinary_button>(300, 0, 400, 100, L"音乐"));
    page22->addButton("退出", std::make_unique<rect_button>(920, 0, 100, 50, L"退出", [=]() {

        exit(0); // 退出程序
    }));
  
    page22->addButton("登录", std::make_unique<rect_button>(200, 450, 150, 50, L"登录", [=]() {
        //  selectbutton(ButtonID::MAIN_LOGIN);
        setCurrentIndex("登录界面");


    }));
    page22->addButton("注册", std::make_unique<rect_button>(600, 450, 150, 50, L"注册", [=]() {
        setCurrentIndex("注册界面");

        //  selectbutton(ButtonID::MAIN_REGISTER);
    }));
    pages["音乐"] = std::move(page22);
}

