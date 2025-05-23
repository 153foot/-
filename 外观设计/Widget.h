#pragma once
#include "ButtonBase.h"
#include <shlobj.h>
#include "PageBase.h"
#include "Page.h"
#include"Page_and_table.h"
#include"TextButton.h"
#include "rect_button.h"    
#include"Ordinary_button.h"
#include "Textbox.h"
#include "TableWidget.h"
#include "AnimatedGifPlayer.h"
#include "MessageDialog.h"
#include "Backgroundmusic.h"
#include "MusicButton.h"
#include <filesystem>
#include <vector>
#include <memory>
#include <map>
class Widget {
private:
    

    int width;
    int height;
    string currentIndex;
    std::map<std::string, std::shared_ptr<PageBase>> pages;
    BackgroundMusic bgMusic;
  
    std::map< std::wstring, std::wstring> userDatabase; // 存储用户名和密码
    std::map< std::wstring,  std::wstring> adminDatabase; // 存储管理员用户名和密码
    std::map<int, const std::wstring> keys;//存储密钥
    std::wstring pas;
    std::wstring name;
    std::wstring input_information;//输入信息
    std::wstring mobile_phone_number;//手机号
    std::wstring confirm_password_again;//再次确认密码
    std::wstring inputkey;//密钥
	//FileHandler fileHandler;
   
 // 定义按钮 ID 枚举
    enum class ButtonID {
        // 主界面按钮
        MAIN_LOGIN,
        MAIN_REGISTER,

        // 登录界面按钮
        LOGIN_RETURN_MAIN,
        LOGIN_USER_ACCOUNT,
        LOGIN_PASSWORD,
        LOGIN_ENTER,
        LOGIN_USER,
        LOGIN_ADMIN,
        LOGIN_GO_REGISTER,
        LOGIN_FORGET_PASSWORD,

        // 注册界面按钮
        REGISTER_RETURN_MAIN,
        REGISTER_USER_ACCOUNT,
        REGISTER_PHONE_NUMBER,
        REGISTER_LOGIN_PASSWORD,
        REGISTER_CONFIRM_PASSWORD,
        REGISTER_CONFIRM,


     
       // 管理员界面按钮
        ADMIN_RETURN_MAIN,//管理员返回主界面
        ADMIN_USER_MANAGEMENT,//管理员用户管理
        ADMIN_MENU_MANAGEMENT,//管理员菜单管理
        ADMIN_ORDER_MANAGEMENT,//管理员订单管理
        ADMIN_TABLE_MANAGEMENT,//管理员餐桌管理
        ADMIN_ANNOUNCEMENT_MANAGEMENT,//管理员公告管理
        ADMIN_INVENTORY_MANAGEMENT,//管理员库存管理
        ADMIN_EXIT,//管理员退出
        // 用户界面 4 的按钮
        USER_PAGE4_RETURN_MAIN,       // 用户界面 4 返回主界面
        USER_PAGE4_EXIT,              // 用户界面 4 退出
        USER_PAGE4_MENU,              // 用户界面 4 菜单
        USER_PAGE4_SHOPPING_CART,     // 用户界面 4 购物车
        USER_PAGE4_CHECK_ANNOUNCEMENT,// 用户界面 4 看看公告
        USER_PAGE4_ACTIVITY,          // 用户界面 4 活动！
        USER_PAGE4_GO_EVALUATE,        // 用户界面 4 去评价
         // 用户菜单界面 5 的按钮
        USER_PAGE5_MENU_TITLE,        // 用户界面 5 菜单标题按钮
        USER_PAGE5_RETURN_MAIN_MENU,  // 用户界面 5 回到主菜单
        USER_PAGE5_RETURN_USER_MAIN,  // 用户界面 5 回到用户主界面
        USER_PAGE5_VIEW_SHOPPING_CART,// 用户界面 5 查看购物车
        USER_PAGE5_VIEW_ANNOUNCEMENT, // 用户界面 5 查看公告
        USER_PAGE5_ACTIVITY,          // 用户界面 5 活动！
        USER_PAGE5_GO_EVALUATE        // 用户界面 5 去评价
    };

private:
    void setwintext() {
       

        // 获得窗口句柄
        HWND hWnd = GetHWnd();
        // 使用 Windows API 修改窗口名称
        SetWindowText(hWnd, L"餐厅管理系统");

    }

    void setCurrentIndex(string index_name);
public:
    Widget(int width, int height);
    ~Widget();
  

    // 登录验证
    bool login(const std::wstring& username, const std::wstring& password, bool isAdmin) {
        auto& database = isAdmin ? adminDatabase : userDatabase;
        auto it = database.find(username);
        if (it != database.end() && it->second == password) {
            return true;
        }
        return false;
    }

    // 注册
    bool registerUser(const std::wstring& username, const std::wstring& password, bool isAdmin) {
        auto& database = isAdmin ? adminDatabase : userDatabase;
        if (database.find(username) == database.end()) {
            database[username] = password;
            return true;
        }
        return false;
    }
    bool checkKey(const std::wstring& inputKey) const {//密钥检测
        for (auto it = keys.begin(); it != keys.end(); ++it) {
            if (it->second == inputKey) {
                return true;
            }
        }
        return false;
    }

    std::vector<std::wstring> split_input_String_to_updateRow(const std::wstring& input, wchar_t delimiter = L'|', 
        int& row = *(new int(0)), int& colume_begin = *(new int(0)), int& colume_end = *(new int(0))) {
       //------------------------------------------------------------------------------------------------
       //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
        std::vector<std::wstring> result;
        size_t start = 0;
        size_t end = 0;

        while ((end = input.find(delimiter, start)) != std::wstring::npos) {
            result.push_back(input.substr(start, end - start));
            start = end + 1;
        }

        // 添加最后一个子字符串（或整个字符串，如果没有找到分隔符）
        if (start != std::wstring::npos) {

            result.push_back(input.substr(start));
        }

        if (result.size() <= 3) {
        
        
            return {};
        
        }

        // 将前两个子字符串转换为整数并赋值给a和b
        if (result.size() > 0) {
            try {
                row = std::stoi(result[0]);
            }
            catch (...) {
                row = 0; // 转换失败时设为默认值
            }
        }

        if (result.size() > 1) {
            try {
                colume_begin = std::stoi(result[1]);
            }
            catch (...) {
                colume_begin = 0; // 转换失败时设为默认值
            }
        }

        if (result.size() > 1) {
            try {
                colume_end = std::stoi(result[2]);
            }
            catch (...) {
                colume_end = 0; // 转换失败时设为默认值
            }
        }
        result.erase(result.begin(), result.begin()+3);//删除前三个分界符内容

        return result;
    }
   
    void init();
    void run();
    void close();

	//void selectbutton(ButtonID id) {//选择按钮
 //       ButtonID button_id = id;
	//	
 //           switch (button_id)
 //           {

	//		case ButtonID::MAIN_LOGIN://主界面
	//		{
 //               setCurrentIndex(1);// 点击按钮2时，执行相关的逻辑
	//			
	//		}
 //         

	//		break;
	//		case ButtonID::MAIN_REGISTER://注册按钮
 //           {
 //               setCurrentIndex(2); // 点击按钮3时，执行相关的逻辑
 //           
 //           
 //           
 //           }
	//			break;
 //               //以下登录ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
	//		case ButtonID::LOGIN_RETURN_MAIN://返回主界面按钮
	//		{
 //               setCurrentIndex(0);
	//			
	//		}
	//	
	//		break;
	//		case ButtonID::LOGIN_USER_ACCOUNT://用户账号按钮
	//		{
	//			wchar_t password[100];
	//			InputBox(password, 100);
	//		}
	//		
 //           break;

	//		case ButtonID::LOGIN_PASSWORD://密码按钮
	//		{
	//			wchar_t password[100];
	//			InputBox(password, 100);
	//		}
	//		break;
 //           case ButtonID::LOGIN_ENTER://进入按钮
 //           {
 //           }
 //           break;
 //           case ButtonID::LOGIN_USER://用户按钮
 //           {
 //               setCurrentIndex(4);
 //           }
 //           break;

	//		case ButtonID::LOGIN_ADMIN://管理员按钮
	//		{
	//			setCurrentIndex(3);
	//		}
	//		break;
 //     
 //           case ButtonID::LOGIN_FORGET_PASSWORD:

 //           {
 //               wchar_t password[100];
 //               InputBox(password, 100);
 //           
 //           
 //           
 //           }

 //           break;
 //           case ButtonID::LOGIN_GO_REGISTER:

 //           {
 //               setCurrentIndex(2);


 //           }

 //           break;
 //           //一下注册ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss

 //           case ButtonID::REGISTER_CONFIRM:

 //           {
 //               setCurrentIndex(1);
 //           }

 //           break;
 //           case ButtonID::REGISTER_CONFIRM_PASSWORD:

 //           {
 //               wchar_t password[100];
 //               InputBox(password, 100);
 //           }

 //           break;
 //           case ButtonID::REGISTER_LOGIN_PASSWORD:

 //           {
 //               wchar_t password[100];
 //               InputBox(password, 100);
 //           }

 //           break;
 //           case ButtonID::REGISTER_PHONE_NUMBER:
 //               
 //           {
 //               wchar_t password[100];
 //               InputBox(password, 100);
 //           }

 //           break;
 //           case ButtonID::REGISTER_RETURN_MAIN:

 //           {
 //               setCurrentIndex(0);
 //           }

 //           break;
 //           case ButtonID::REGISTER_USER_ACCOUNT://账号

 //           {
 //               wchar_t password[100];//用swiTch语句来判断
 //               InputBox(password, 100);
 //           }

 //           break;
 //           //管理员界面按钮
 //           case ButtonID::ADMIN_ANNOUNCEMENT_MANAGEMENT://

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           case ButtonID::ADMIN_EXIT :

 //           {
 //               exit(0); // 退出程序
 //             
 //           }

 //           break;
 //           case ButtonID::ADMIN_INVENTORY_MANAGEMENT:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           case ButtonID::ADMIN_MENU_MANAGEMENT:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           case ButtonID::ADMIN_ORDER_MANAGEMENT:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           case ButtonID::ADMIN_RETURN_MAIN:

 //           {
 //               setCurrentIndex(0);
 //               
 //           }

 //           break;
 //           case ButtonID::ADMIN_TABLE_MANAGEMENT:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           case ButtonID::ADMIN_USER_MANAGEMENT:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           //用户主界面
 //           case ButtonID::USER_PAGE4_ACTIVITY:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;   
 //           case ButtonID::USER_PAGE4_CHECK_ANNOUNCEMENT:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           case ButtonID::USER_PAGE4_EXIT:

 //           {
 //               exit(0); // 退出程序
 //               
 //           }

 //           break;
 //           case ButtonID::USER_PAGE4_GO_EVALUATE:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           case ButtonID::USER_PAGE4_MENU:

 //           {
 //               setCurrentIndex(5);
 //           }

 //           break;
 //           case ButtonID::USER_PAGE4_RETURN_MAIN:

 //           {
 //               setCurrentIndex(0);
 //               
 //           }

 //           break;
 //           case ButtonID::USER_PAGE4_SHOPPING_CART:

 //           {
 //              
 //           }

 //           break;
 //           //AAAAA用户菜单
 //           case ButtonID::USER_PAGE5_ACTIVITY:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           case ButtonID::USER_PAGE5_GO_EVALUATE:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           case ButtonID::USER_PAGE5_MENU_TITLE:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           case ButtonID::USER_PAGE5_RETURN_MAIN_MENU:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           case ButtonID::USER_PAGE5_RETURN_USER_MAIN:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           case ButtonID::USER_PAGE5_VIEW_ANNOUNCEMENT:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           case ButtonID::USER_PAGE5_VIEW_SHOPPING_CART:

 //           {
 //               setCurrentIndex(2);
 //           }

 //           break;
 //           

 //           break;
 //           default:
 //               break;
 //           }


 //       
	//
 //   }   

    void init_page0(int width, int height);
    void init_page1(int width, int height);
    void init_page2(int width, int height);
    void init_page3(int width, int height);
    void init_page4(int width, int height);
    void init_page5(int width, int height);
    void init_page6(int width, int height);
    void init_page7(int width, int height);
    void init_page8(int width, int height);
    void init_page9(int width, int height);
    void init_page10(int width, int height);
    void init_page11(int width, int height);
    void init_page12(int width, int height);
    void init_page13(int width, int height);
    void init_page14(int width, int height);
    void init_page15(int width, int height);
    void init_page16(int width, int height);
    void init_page17(int width, int height);
    void init_page18(int width, int height);
    void init_page19(int width, int height);
    void init_page20(int width, int height);
    void init_page21(int width, int height);
    void init_page22(int width, int height);

};