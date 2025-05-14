#pragma once
#include "rect_button.h"
#include "BackgroundMusic.h"
#include <functional>

class MusicButton : public rect_button {
private:
    BackgroundMusic* musicPlayer;
    std::wstring musicAlias;
    bool isStopButton;

public:
    // 普通音乐按钮构造函数
    MusicButton(int x, int y, int width, int height, const wchar_t* text,
        BackgroundMusic* player, const std::wstring& alias,
        COLORREF buttonColor = RGB(255, 189, 225),
        COLORREF textColor = RGB(255, 255, 255),
        COLORREF borderColor = RGB(255, 189, 225))
        : rect_button(x, y, width, height, text, [this]() { this->onMusicButtonClick(); },
            buttonColor, textColor, borderColor),
        musicPlayer(player), musicAlias(alias), isStopButton(false) {
    }

    // 停止所有音乐按钮构造函数
    MusicButton(int x, int y, int width, int height, const wchar_t* text,
        BackgroundMusic* player,
        COLORREF buttonColor = RGB(255, 100, 100),
        COLORREF textColor = RGB(255, 255, 255),
        COLORREF borderColor = RGB(255, 100, 100))
        : rect_button(x, y, width, height, text, [this]() { this->onStopButtonClick(); },
            buttonColor, textColor, borderColor),
        musicPlayer(player), isStopButton(true) {
    }

    // 音乐按钮点击处理
    void onMusicButtonClick() {
        if (musicPlayer) {
            musicPlayer->playMusic(musicAlias);
        }
    }

    // 停止按钮点击处理
    void onStopButtonClick() {
        if (musicPlayer) {
            musicPlayer->stopAllMusic();
        }
    }

    // 覆盖绘制函数，根据当前状态显示不同样式
    void draw() override {
        if (isStopButton) {
            // 停止按钮特殊样式
            if (musicPlayer && musicPlayer->isMusicPlaying()) {
                setlinecolor(RGB(255, 50, 50)); // 播放时有音乐时的边框颜色
                setfillcolor(RGB(255, 100, 100)); // 播放时有音乐时的填充颜色
            }
            else {
                setlinecolor(RGB(150, 150, 150)); // 没有音乐播放时的边框颜色
                setfillcolor(RGB(200, 200, 200)); // 没有音乐播放时的填充颜色
            }
        }
        else {
            // 普通音乐按钮样式
            if (musicPlayer && musicPlayer->getCurrentMusic() == musicAlias) {
                setlinecolor(RGB(100, 255, 100)); // 当前正在播放的音乐按钮边框颜色
                setfillcolor(RGB(150, 255, 150)); // 当前正在播放的音乐按钮填充颜色
            }
        }

        // 调用基类绘制函数
        rect_button::draw();
    }
};