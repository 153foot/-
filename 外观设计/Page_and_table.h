#pragma once
#include "MediaPlayerBase.h"
#include "TextboxBase.h"
#include "PageBase.h"
#include "TableWidgetBase.h"
#include <easyx.h>
#include <memory>
#include <map>
class Page_and_table : public PageBase {
private:
    
    int width;
    int height;
    std::unique_ptr<IMAGE> pageImage;
    std::unique_ptr<TableWidgetBase> table;
   
    std::map<std::string, std::unique_ptr<ButtonBase>> buttons;
    std::map<std::string, std::shared_ptr<TextboxBase>> texstboxs;
    std::map<std::string, std::shared_ptr<MediaPlayerBase>> mediaPlayers;
    

public:
    Page_and_table(int width, int height, const wchar_t* imagePath);


    virtual ~Page_and_table();
 

   
    virtual void addButton(std::string name, std::unique_ptr<ButtonBase> button) {//添加按钮

        buttons.insert(std::pair<const std::string, std::unique_ptr<ButtonBase>>(name, move(button)));

    }


    virtual void addtexstbox(std::string name, std::shared_ptr<TextboxBase>  texstbox) {//添加输入框

        texstboxs.insert(std::pair<const std::string, std::shared_ptr<TextboxBase>>(name, texstbox));

    }
    virtual void addGIF(std::string name, std::shared_ptr<MediaPlayerBase> GIF) {//添加GIF 动图

        mediaPlayers.insert(std::pair<const std::string, std::shared_ptr<MediaPlayerBase>>(name,GIF));

    }

    virtual void addTable(std::unique_ptr<TableWidgetBase>& Table) {
     
        table = std::move(Table);
    }

    virtual void draw() {//把所有组件添加到一个界面中
        if (pageImage.get() != nullptr) {
            putimage(0, 0, pageImage.get());
        }
       

        if (table) {
            table->draw();
        }
            
        if (!buttons.empty()) {
            for (auto& button : buttons) {
                button.second->draw();
            }
        }
        if (!texstboxs.empty()) {
            for (auto& texstbox : texstboxs) {
                texstbox.second->draw();
            }
        }
        if (!mediaPlayers.empty()) {//
            for (auto& mediaPlayer : mediaPlayers) {
                mediaPlayer.second->draw();
            }
        }

    }

    virtual void mouseClick(int mouseX, int mouseY) {
        if (table) {
            table->handleMouseClick(mouseX, mouseY);
        }
        for (auto& button : buttons) {
            if (button.second->checkClick(mouseX, mouseY)) {
                break;
            }
        }
        for (auto& texstbox : texstboxs) {
            if (texstbox.second->checkClick(mouseX, mouseY)) {
                break;
            }
        }
       
            
        
    }

    virtual void mouseMove(int mouseX, int mouseY) {
        for (auto& button : buttons) {
            button.second->checkMouseOver(mouseX, mouseY);
        }
        for (auto& texstbox : texstboxs) {
            texstbox.second->checkMouseOver(mouseX, mouseY);
        }
    }

    virtual void mouseWheel(int mouseX, int mouseY, int wheel) {
       
            if (table) {
                table->scroll(mouseX, mouseY, wheel);
            }
        
    }

    void maketable(std::unique_ptr<TableWidgetBase> tablePtr) {//要改
        tablePtr->setData({
            {L"活动ID", L"活动名称", L"开始时间", L"结束时间", L"活动内容", L"活动规则", L"参与条件", L"活动状态"},
            {L"1", L"夏日清凉特惠", L"2025-07-01 00:00:00", L"2025-07-31 23:59:59", L"全店商品 8 折优惠", L"直接在结算时享受折扣", L"无", L"未开始"},
            {L"2", L"会员专享满减", L"2025-05-15 00:00:00", L"2025-05-31 23:59:59", L"会员消费满 500 减 100", L"会员身份且消费金额达到要求", L"会员用户", L"已结束"},
            {L"3", L"新用户注册有礼", L"2025-06-01 00:00:00", L"2025-06-30 23:59:59", L"新用户注册送精美礼品一份", L"成功注册新用户即可领取", L"非注册用户", L"已结束"},
            {L"4", L"国庆狂欢大促", L"2025-10-01 00:00:00", L"2025-10-07 23:59:59", L"部分商品 7 折起", L"购买指定商品可享受折扣", L"无", L"未开始"},
            {L"5", L"店庆感恩回馈", L"2025-08-18 00:00:00", L"2025-08-20 23:59:59", L"消费满 200 元可参与抽奖", L"根据抽奖结果获得相应奖品", L"消费满 200 元", L"未开始"},
            {L"6", L"冬季暖心套餐", L"2025-12-01 00:00:00", L"2025-12-31 23:59:59", L"推出冬季特色套餐", L"直接购买套餐即可", L"无", L"未开始"},
            {L"7", L"情人节浪漫特惠", L"2025-02-14 00:00:00", L"2025-02-15 23:59:59", L"情侣商品 9 折优惠", L"情侣双方共同购买商品可享受折扣", L"情侣用户", L"已结束"},
            {L"8", L"母亲节感恩特惠", L"2025-05-11 00:00:00", L"2025-05-12 23:59:59", L"消费满 300 送鲜花一束", L"消费金额达到要求即可获赠", L"无", L"已结束"},
            {L"9", L"开学季大优惠", L"2025-09-01 00:00:00", L"2025-09-10 23:59:59", L"学生用品 8.5 折", L"凭学生证购买学生用品可享受折扣", L"学生用户", L"未开始"},
            {L"10", L"圣诞节惊喜活动", L"2025-12-25 00:00:00", L"2025-12-26 23:59:59", L"消费满 100 可参与抽奖", L"根据抽奖结果获得相应奖品", L"消费满 100 元", L"未开始"}
            });
        addTable(tablePtr);
       
    }
};