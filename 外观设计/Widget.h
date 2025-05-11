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
#include <vector>
#include <memory>
#include <map>
class Widget {
private:
    // ȫ�ֹ��Ӿ��
    static  HHOOK g_hHook;
    int width;
    int height;
    int currentIndex;
    std::vector<std::shared_ptr<PageBase>> pages;
    void setCurrentIndex(int index);
    std::map<std::wstring, std::wstring> userDatabase; // �洢�û���������
    std::map<std::wstring, std::wstring> adminDatabase; // �洢����Ա�û���������
    std::wstring pas;
    std::wstring name;
   
 // ���尴ť ID ö��
    enum class ButtonID {
        // �����水ť
        MAIN_LOGIN,
        MAIN_REGISTER,

        // ��¼���水ť
        LOGIN_RETURN_MAIN,
        LOGIN_USER_ACCOUNT,
        LOGIN_PASSWORD,
        LOGIN_ENTER,
        LOGIN_USER,
        LOGIN_ADMIN,
        LOGIN_GO_REGISTER,
        LOGIN_FORGET_PASSWORD,

        // ע����水ť
        REGISTER_RETURN_MAIN,
        REGISTER_USER_ACCOUNT,
        REGISTER_PHONE_NUMBER,
        REGISTER_LOGIN_PASSWORD,
        REGISTER_CONFIRM_PASSWORD,
        REGISTER_CONFIRM,


     
       // ����Ա���水ť
        ADMIN_RETURN_MAIN,//����Ա����������
        ADMIN_USER_MANAGEMENT,//����Ա�û�����
        ADMIN_MENU_MANAGEMENT,//����Ա�˵�����
        ADMIN_ORDER_MANAGEMENT,//����Ա��������
        ADMIN_TABLE_MANAGEMENT,//����Ա��������
        ADMIN_ANNOUNCEMENT_MANAGEMENT,//����Ա�������
        ADMIN_INVENTORY_MANAGEMENT,//����Ա������
        ADMIN_EXIT,//����Ա�˳�
        // �û����� 4 �İ�ť
        USER_PAGE4_RETURN_MAIN,       // �û����� 4 ����������
        USER_PAGE4_EXIT,              // �û����� 4 �˳�
        USER_PAGE4_MENU,              // �û����� 4 �˵�
        USER_PAGE4_SHOPPING_CART,     // �û����� 4 ���ﳵ
        USER_PAGE4_CHECK_ANNOUNCEMENT,// �û����� 4 ��������
        USER_PAGE4_ACTIVITY,          // �û����� 4 ���
        USER_PAGE4_GO_EVALUATE,        // �û����� 4 ȥ����
         // �û��˵����� 5 �İ�ť
        USER_PAGE5_MENU_TITLE,        // �û����� 5 �˵����ⰴť
        USER_PAGE5_RETURN_MAIN_MENU,  // �û����� 5 �ص����˵�
        USER_PAGE5_RETURN_USER_MAIN,  // �û����� 5 �ص��û�������
        USER_PAGE5_VIEW_SHOPPING_CART,// �û����� 5 �鿴���ﳵ
        USER_PAGE5_VIEW_ANNOUNCEMENT, // �û����� 5 �鿴����
        USER_PAGE5_ACTIVITY,          // �û����� 5 ���
        USER_PAGE5_GO_EVALUATE        // �û����� 5 ȥ����
    };

private:
    void setwintext() {
       

        // ��ô��ھ��
        HWND hWnd = GetHWnd();
        // ʹ�� Windows API �޸Ĵ�������
        SetWindowText(hWnd, L"��������ϵͳ");

    }


public:
    Widget(int width, int height);
    ~Widget();
    void reservevector() {
    
        pages.reserve(300);
    
    
    }
  

    // ���̹��Ӵ�����
    static  LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
        if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
            KBDLLHOOKSTRUCT* kb = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

            // ���Ctrl+C��Ctrl+V
            bool ctrlPressed = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
            if (ctrlPressed) {
                switch (kb->vkCode) {
                case 'C':
                    std::cout << "Ctrl+C ��ϼ�������" << std::endl;
                    return 1; // ���ذ���
                case 'V':
                    std::cout << "Ctrl+V ��ϼ�������" << std::endl;
                    return 1; // ���ذ���
                }
            }

            // ���Shift+�����Shift+�Ҽ�
            bool shiftPressed = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
            if (shiftPressed) {
                switch (kb->vkCode) {
                case VK_LEFT:
                    std::cout << "Shift+��� ��ϼ�������" << std::endl;
                    return 1; // ���ذ���
                case VK_RIGHT:
                    std::cout << "Shift+�Ҽ� ��ϼ�������" << std::endl;
                    return 1; // ���ذ���
                }
            }
        }
        return CallNextHookEx(g_hHook, nCode, wParam, lParam);
    }

    // ��¼��֤
    bool login(const std::wstring& username, const std::wstring& password, bool isAdmin) {
        auto& database = isAdmin ? adminDatabase : userDatabase;
        auto it = database.find(username);
        if (it != database.end() && it->second == password) {
            return true;
        }
        return false;
    }

    // ע��
    bool registerUser(const std::wstring& username, const std::wstring& password, bool isAdmin) {
        auto& database = isAdmin ? adminDatabase : userDatabase;
        if (database.find(username) == database.end()) {
            database[username] = password;
            return true;
        }
        return false;
    }
   
    void init();
    void run();
    void close();

	void selectbutton(ButtonID id) {//ѡ��ť
        ButtonID button_id = id;
		
            switch (button_id)
            {

			case ButtonID::MAIN_LOGIN://������
			{
                setCurrentIndex(1);// �����ť2ʱ��ִ����ص��߼�
				
			}
          

			break;
			case ButtonID::MAIN_REGISTER://ע�ᰴť
            {
                setCurrentIndex(2); // �����ť3ʱ��ִ����ص��߼�
            
            
            
            }
				break;
                //���µ�¼ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
			case ButtonID::LOGIN_RETURN_MAIN://���������水ť
			{
                setCurrentIndex(0);
				
			}
		
			break;
			case ButtonID::LOGIN_USER_ACCOUNT://�û��˺Ű�ť
			{
				wchar_t password[100];
				InputBox(password, 100);
			}
			
            break;

			case ButtonID::LOGIN_PASSWORD://���밴ť
			{
				wchar_t password[100];
				InputBox(password, 100);
			}
			break;
            case ButtonID::LOGIN_ENTER://���밴ť
            {
            }
            break;
            case ButtonID::LOGIN_USER://�û���ť
            {
                setCurrentIndex(4);
            }
            break;

			case ButtonID::LOGIN_ADMIN://����Ա��ť
			{
				setCurrentIndex(3);
			}
			break;
      
            case ButtonID::LOGIN_FORGET_PASSWORD:

            {
                wchar_t password[100];
                InputBox(password, 100);
            
            
            
            }

            break;
            case ButtonID::LOGIN_GO_REGISTER:

            {
                setCurrentIndex(2);


            }

            break;
            //һ��ע��ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss

            case ButtonID::REGISTER_CONFIRM:

            {
                setCurrentIndex(1);
            }

            break;
            case ButtonID::REGISTER_CONFIRM_PASSWORD:

            {
                wchar_t password[100];
                InputBox(password, 100);
            }

            break;
            case ButtonID::REGISTER_LOGIN_PASSWORD:

            {
                wchar_t password[100];
                InputBox(password, 100);
            }

            break;
            case ButtonID::REGISTER_PHONE_NUMBER:
                
            {
                wchar_t password[100];
                InputBox(password, 100);
            }

            break;
            case ButtonID::REGISTER_RETURN_MAIN:

            {
                setCurrentIndex(0);
            }

            break;
            case ButtonID::REGISTER_USER_ACCOUNT://�˺�

            {
                wchar_t password[100];//��swiTch������ж�
                InputBox(password, 100);
            }

            break;
            //����Ա���水ť
            case ButtonID::ADMIN_ANNOUNCEMENT_MANAGEMENT://

            {
                setCurrentIndex(2);
            }

            break;
            case ButtonID::ADMIN_EXIT :

            {
                exit(0); // �˳�����
              
            }

            break;
            case ButtonID::ADMIN_INVENTORY_MANAGEMENT:

            {
                setCurrentIndex(2);
            }

            break;
            case ButtonID::ADMIN_MENU_MANAGEMENT:

            {
                setCurrentIndex(2);
            }

            break;
            case ButtonID::ADMIN_ORDER_MANAGEMENT:

            {
                setCurrentIndex(2);
            }

            break;
            case ButtonID::ADMIN_RETURN_MAIN:

            {
                setCurrentIndex(0);
                
            }

            break;
            case ButtonID::ADMIN_TABLE_MANAGEMENT:

            {
                setCurrentIndex(2);
            }

            break;
            case ButtonID::ADMIN_USER_MANAGEMENT:

            {
                setCurrentIndex(2);
            }

            break;
            //�û�������
            case ButtonID::USER_PAGE4_ACTIVITY:

            {
                setCurrentIndex(2);
            }

            break;   
            case ButtonID::USER_PAGE4_CHECK_ANNOUNCEMENT:

            {
                setCurrentIndex(2);
            }

            break;
            case ButtonID::USER_PAGE4_EXIT:

            {
                exit(0); // �˳�����
                
            }

            break;
            case ButtonID::USER_PAGE4_GO_EVALUATE:

            {
                setCurrentIndex(2);
            }

            break;
            case ButtonID::USER_PAGE4_MENU:

            {
                setCurrentIndex(5);
            }

            break;
            case ButtonID::USER_PAGE4_RETURN_MAIN:

            {
                setCurrentIndex(0);
                
            }

            break;
            case ButtonID::USER_PAGE4_SHOPPING_CART:

            {
               
            }

            break;
            //AAAAA�û��˵�
            case ButtonID::USER_PAGE5_ACTIVITY:

            {
                setCurrentIndex(2);
            }

            break;
            case ButtonID::USER_PAGE5_GO_EVALUATE:

            {
                setCurrentIndex(2);
            }

            break;
            case ButtonID::USER_PAGE5_MENU_TITLE:

            {
                setCurrentIndex(2);
            }

            break;
            case ButtonID::USER_PAGE5_RETURN_MAIN_MENU:

            {
                setCurrentIndex(2);
            }

            break;
            case ButtonID::USER_PAGE5_RETURN_USER_MAIN:

            {
                setCurrentIndex(2);
            }

            break;
            case ButtonID::USER_PAGE5_VIEW_ANNOUNCEMENT:

            {
                setCurrentIndex(2);
            }

            break;
            case ButtonID::USER_PAGE5_VIEW_SHOPPING_CART:

            {
                setCurrentIndex(2);
            }

            break;
            

            break;
            default:
                break;
            }


        
	
    }   

    void init_page0(int width, int height);
    void init_page1(int width, int height);
    void init_page2(int width, int height);
    void init_page3(int width, int height);
    void init_page4(int width, int height);
    void init_page5(int width, int height);
    void init_page6(int width, int height);
   
};