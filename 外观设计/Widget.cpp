#include "Widget.h"

#include <conio.h>
#include <iostream>

Widget::Widget(int width, int height) : width(width), height(height), currentIndex(0) {

    //pages.reserve(100);
    pages.reserve(200);

}

Widget::~Widget() {}

void Widget::setCurrentIndex(int index) {
    if (index >= 0 && index < pages.size()) {
        currentIndex = index;
    }
    else
    {
        std::cerr << "shcasidhaoijoaidjia";
    }

}

void Widget::init() {
    initgraph(width, height);
    setwintext();
    reservevector();
    // 创建主界面0
    auto page0 = std::make_unique<Page>(width, height, L".//Image//可爱小狗.png");

    page0->addButton(std::make_unique<AnimatedGifPlayer>(0, 0,30,30, L"GIF//3//",17));//这个以后要优化 自己加载图片


    page0->addButton(std::make_unique<Ordinary_button>(300, 0, 400, 100, L"订餐服务系统"));
    page0->addButton(std::make_unique<rect_button>(920, 0, 100, 50, L"退出", [&]() {
        setCurrentIndex(6);//测试用
		//exit(0); // 退出程序
    }));
  
    page0->addButton(std::make_unique<rect_button>(200,450 , 150, 50, L"登录", [&]() {
        selectbutton(ButtonID::MAIN_LOGIN);
       
    }));
    page0->addButton(std::make_unique<rect_button>(600, 450, 150, 50, L"注册", [&]() {
        
        selectbutton(ButtonID::MAIN_REGISTER);
    }));

    
    pages.push_back(std::move(page0));

	// 创建登录界面1
    auto page1 = std::make_unique<Page>(width, height, L".//Image//可爱小狗.png");
    page1->addButton(std::make_unique<Ordinary_button>(300, 0, 400, 100, L"登录界面"));//按钮0
    page1->addButton(std::make_unique<Ordinary_button>(80, 100, 140, 360, L"          ",RGB(245, 143, 152)));//按钮1
	
	


	page1->addButton(std::make_unique<rect_button>(920, 50, 100, 50, L"返回主界面", [&]() {//按钮2
		
        selectbutton(ButtonID::LOGIN_RETURN_MAIN);//

	}));
  
    page1->addButton(std::make_unique<rect_button>(920, 0, 100, 50,  L"去注册！", [&]() {//按钮3
       
        selectbutton(ButtonID::LOGIN_GO_REGISTER);
    }));
    page1->addButton(std::make_unique<rect_button>(920, 100, 100, 50, L"忘记密码", [&]() {//按钮3
        selectbutton(ButtonID::LOGIN_FORGET_PASSWORD);
    }));
	page1->addButton(std::make_unique<rect_button>(100, 150, 100, 50, L"用户账号", [&]() {//按钮4用户账号
        selectbutton(ButtonID::LOGIN_USER_ACCOUNT);
       

    }));
    page1->addButton(std::make_unique<Textbox>(300, 160, 200, 30, 10, L"请输入用户账号", [&]() {

        selectbutton(ButtonID::MAIN_REGISTER);

    }));
	page1->addButton(std::make_unique<rect_button>(100, 200, 100, 50, L"密码", [&]() {//按钮5密码
       // selectbutton(ButtonID::LOGIN_PASSWORD);InputBox
       
	}));//
    page1->addButton(std::make_unique<Textbox>(300, 210, 200, 30, 10, L"请输入用户密码", [&]() {

        selectbutton(ButtonID::MAIN_REGISTER);

    }));
    page1->addButton(std::make_unique<rect_button>(300, 500, 400, 30, L"进入", [&]() {//按钮6
        selectbutton(ButtonID::LOGIN_ENTER);
        
        

    }));//
    

    page1->addButton(std::make_unique<rect_button>(100, 300, 100, 50, L"用户", [&]() {//按钮7
       selectbutton(ButtonID::LOGIN_USER);

    }));//

	page1->addButton(std::make_unique<rect_button>(100, 350, 100, 50, L"管理员", [&]() {//按钮8
		
        selectbutton(ButtonID::LOGIN_ADMIN);
	}));


    
    pages.push_back(std::move(page1));


    // 创建注册页面2
    auto page2 = std::make_unique<Page>(width, height, L".//Image//MAC.png");
    /*setfillcolor(RED);
    solidrectangle(0, 0, width, height);*/
    page2->addButton(std::make_unique<rect_button>(100, 150, 100, 50, L"回到主界面", [&]() {
       
        selectbutton(ButtonID::REGISTER_RETURN_MAIN);


    }));
    page2->addButton(std::make_unique<Ordinary_button>(300, 0, 400, 100, L"欢迎来注册(ﾉ*･ω･)ﾉ"));

    page2->addButton(std::make_unique<rect_button>(100, 200, 100, 50, L"用户账号", [&]() {
		selectbutton(ButtonID::REGISTER_USER_ACCOUNT);
    }));
    page2->addButton(std::make_unique<Textbox>(300, 210, 200, 30, 10, L"请输入用户账号", [&]() {

        selectbutton(ButtonID::MAIN_REGISTER);

    }));
    page2->addButton(std::make_unique<rect_button>(100, 250, 100, 50, L"手机号", [&]() {
       selectbutton(ButtonID::REGISTER_PHONE_NUMBER);
    }));
    page2->addButton(std::make_unique<Textbox>(300, 260, 200, 30, 10, L"请输入手机号", [&]() {

        selectbutton(ButtonID::MAIN_REGISTER);

    }));

    page2->addButton(std::make_unique<rect_button>(100, 300, 100, 50, L"登录密码", [&]() {
        selectbutton(ButtonID::REGISTER_LOGIN_PASSWORD);
    }));
    page2->addButton(std::make_unique<Textbox>(300, 310, 200, 30, 10, L"请输入密码", [&]() {

        selectbutton(ButtonID::MAIN_REGISTER);

    }));
    page2->addButton(std::make_unique<rect_button>(100, 350, 100, 50, L"确认密码", [&]() {
          selectbutton(ButtonID::REGISTER_CONFIRM_PASSWORD);
    }));
    page2->addButton(std::make_unique<Textbox>(300, 360, 200, 30, 10, L"请再次输入密码", [&]() {

        selectbutton(ButtonID::MAIN_REGISTER);

    }));
    //￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥
    


   
    page2->addButton(std::make_unique<rect_button>(300, 500, 400, 30, L"确认", [&]() {
         selectbutton(ButtonID::REGISTER_CONFIRM);



    }));
    page2->addButton(std::make_unique<rect_button>(920, 0, 100, 50, L"退出", [&]() {
       
        exit(0); // 退出程序
    }));
    pages.push_back(std::move(page2));

     //创建管理员界面3
	auto page3 = std::make_unique<Page>(width, height, L".//Image//MAC1.png");
	page3->addButton(std::make_unique<rect_button>(100, 100, 100, 50, L"返回主界面", [&]() {
		selectbutton(ButtonID::ADMIN_RETURN_MAIN);

	}));
    page3->addButton(std::make_unique<Ordinary_button>(300, 0, 400, 100, L"管理员管理界面"));//

	page3->addButton(std::make_unique<rect_button>(100, 150, 100, 50, L"用户管理", [&]() {
		selectbutton(ButtonID::ADMIN_USER_MANAGEMENT);
		
	}));//
    page3->addButton(std::make_unique<rect_button>(100, 200, 100, 50, L"菜单管理", [&]() {
		wchar_t password[100];
		InputBox(password, 100);
	}));//

	page3->addButton(std::make_unique<rect_button>(100, 250, 100, 50, L"订单管理", [&]() {
		selectbutton(ButtonID::ADMIN_ORDER_MANAGEMENT);
	
	}));//
    page3->addButton(std::make_unique<rect_button>(100, 300, 100, 50, L"餐桌管理", [&]() {
       selectbutton(ButtonID::ADMIN_TABLE_MANAGEMENT);
        
    }));
    page3->addButton(std::make_unique<rect_button>(100, 350, 100, 50, L"公告管理", [&]() {
        selectbutton(ButtonID::ADMIN_ANNOUNCEMENT_MANAGEMENT);
    }));
    page3->addButton(std::make_unique<rect_button>(100, 400, 100, 50, L"库存管理", [&]() {
        selectbutton(ButtonID::ADMIN_INVENTORY_MANAGEMENT);
    }));
    page3->addButton(std::make_unique<rect_button>(100, 450, 100, 50, L"活动管理", [&]() {
        selectbutton(ButtonID::ADMIN_INVENTORY_MANAGEMENT);
    }));

	page3->addButton(std::make_unique<rect_button>(920, 0, 100, 50, L"退出", [&]() {
        selectbutton(ButtonID::ADMIN_EXIT);
       
    }));
   pages.push_back(std::move(page3));
   //创建用户界面4
   auto page4= std::make_unique<Page>(width, height, L".//Image//MAC1.png");

   page4->addButton(std::make_unique<Ordinary_button>(300, 0, 400, 100, L"欢迎来到本餐厅"));
   page4->addButton(std::make_unique<rect_button>(100, 100, 100, 50, L"返回主界面", [&]() {
       selectbutton(ButtonID::USER_PAGE4_RETURN_MAIN);

   }));
   page4->addButton(std::make_unique<rect_button>(920, 0, 100, 50, L"退出", [&]() {
      selectbutton(ButtonID::USER_PAGE4_EXIT);
      
   }));
   page4->addButton(std::make_unique<rect_button>(100, 150, 100, 50, L"菜单", [&]() {//
       selectbutton(ButtonID::USER_PAGE4_MENU);

   }));
   page4->addButton(std::make_unique<rect_button>(100, 200, 100, 50, L"购物车", [&]() {//
       selectbutton(ButtonID::USER_PAGE4_SHOPPING_CART);

   }));
   page4->addButton(std::make_unique<rect_button>(100, 250, 100, 50, L"看看公告", [&]() {//
       selectbutton(ButtonID::USER_PAGE4_CHECK_ANNOUNCEMENT);

   }));
   page4->addButton(std::make_unique<rect_button>(100, 300, 100, 50, L"活动！", [&]() {//
     selectbutton(ButtonID::USER_PAGE4_ACTIVITY);

   }));  
   //page4->addButton(std::make_unique<rect_button>(100, 350, 100, 50, L"去评价", [&]() {//
   //   selectbutton(ButtonID::USER_PAGE4_GO_EVALUATE);

   //}));


   pages.push_back(std::move(page4));
   //用户菜单界面5
   auto page5 = std::make_unique<Page>(width, height, L".//Image//3.jpg");
   page5->addButton(std::make_unique<Ordinary_button>(300, 0, 400, 100, L"菜单"));
   page5->addButton(std::make_unique<rect_button>(0, 0, 100, 20, L"返回", [&]() {
       selectbutton(ButtonID::USER_PAGE5_RETURN_USER_MAIN);

   }));
   page5->addButton(std::make_unique<rect_button>(920, 0, 100, 50, L"用户主界面", [&]() {
       selectbutton(ButtonID::USER_PAGE4_EXIT);

   }));
  
   page5->addButton(std::make_unique<rect_button>(0, 20, 100, 20, L"查看购物车", [&]() {//
       selectbutton(ButtonID::USER_PAGE4_SHOPPING_CART);

   }));
   page5->addButton(std::make_unique<rect_button>(0, 40, 100, 20, L"查看公告", [&]() {//
       selectbutton(ButtonID::USER_PAGE4_CHECK_ANNOUNCEMENT);

   }));
   page5->addButton(std::make_unique<rect_button>(0, 60, 100, 20, L"活动！", [&]() {//
       selectbutton(ButtonID::USER_PAGE4_ACTIVITY);

   }));
   page5->addButton(std::make_unique<rect_button>(0, 80, 100, 20, L"去评价", [&]() {//
       selectbutton(ButtonID::USER_PAGE4_GO_EVALUATE);

   }));//划线了
   pages.push_back(std::move(page5));
   //测试！！！！！！！！！！222！！！￥￥￥￥￥￥￥￥￥
   auto page6= std::make_unique<Page_and_table>(width, height, L".//Image//3.jpg");
   page6->maketable(std::make_unique<TableWidget>(120, 120, 800, 300, 4,5));
   
   page6->addButton(std::make_unique<rect_button>(920, 0, 100, 20, L"返回！", [&]() {//
       setCurrentIndex(0);//测试用

   }));
   //page6->addButton(std::make_unique<rect_button>(0, 100, 90, 20, L"确认下单", [&]() {//
   //    setCurrentIndex(0);//测试用

   //}));
  

   //page6->addButton(std::make_unique<rect_button>(0, 128, 90, 20, L"去评价", [&]() {//
   //    selectbutton(ButtonID::USER_PAGE4_GO_EVALUATE);

   //}));//划线了
   //page6->addButton(std::make_unique<rect_button>(0, 156, 90, 20, L"公告", [&]() {//
   //    setCurrentIndex(0);//测试用

   //}));
   page6->addButton(std::make_unique<rect_button>(120, 450, 90, 20, L"添加活动", [&]() {//
      setCurrentIndex(0);//测试用

   }));
   page6->addButton(std::make_unique<rect_button>(820, 450, 90, 20, L"查看活动", [&]() {//
       setCurrentIndex(0);//测试用

   }));
   page6->addButton(std::make_unique<rect_button>(120, 478, 90, 20, L"修改活动", [&]() {//
       setCurrentIndex(0);//测试用

   }));
   page6->addButton(std::make_unique<rect_button>(820, 478, 90, 20, L"删除活动", [&]() {//
    
   }));


   page6->addButton(std::make_unique<Ordinary_button>(300, 0, 400, 50, L"活动管理界面"));

   pages.push_back(std::move(page6));



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