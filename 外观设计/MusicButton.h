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
    // ��ͨ���ְ�ť���캯��
    MusicButton(int x, int y, int width, int height, const wchar_t* text,
        BackgroundMusic* player, const std::wstring& alias,
        COLORREF buttonColor = RGB(255, 189, 225),
        COLORREF textColor = RGB(255, 255, 255),
        COLORREF borderColor = RGB(255, 189, 225))
        : rect_button(x, y, width, height, text, [this]() { this->onMusicButtonClick(); },
            buttonColor, textColor, borderColor),
        musicPlayer(player), musicAlias(alias), isStopButton(false) {
    }

    // ֹͣ�������ְ�ť���캯��
    MusicButton(int x, int y, int width, int height, const wchar_t* text,
        BackgroundMusic* player,
        COLORREF buttonColor = RGB(255, 100, 100),
        COLORREF textColor = RGB(255, 255, 255),
        COLORREF borderColor = RGB(255, 100, 100))
        : rect_button(x, y, width, height, text, [this]() { this->onStopButtonClick(); },
            buttonColor, textColor, borderColor),
        musicPlayer(player), isStopButton(true) {
    }

    // ���ְ�ť�������
    void onMusicButtonClick() {
        if (musicPlayer) {
            musicPlayer->playMusic(musicAlias);
        }
    }

    // ֹͣ��ť�������
    void onStopButtonClick() {
        if (musicPlayer) {
            musicPlayer->stopAllMusic();
        }
    }

    // ���ǻ��ƺ��������ݵ�ǰ״̬��ʾ��ͬ��ʽ
    void draw() override {
        if (isStopButton) {
            // ֹͣ��ť������ʽ
            if (musicPlayer && musicPlayer->isMusicPlaying()) {
                setlinecolor(RGB(255, 50, 50)); // ����ʱ������ʱ�ı߿���ɫ
                setfillcolor(RGB(255, 100, 100)); // ����ʱ������ʱ�������ɫ
            }
            else {
                setlinecolor(RGB(150, 150, 150)); // û�����ֲ���ʱ�ı߿���ɫ
                setfillcolor(RGB(200, 200, 200)); // û�����ֲ���ʱ�������ɫ
            }
        }
        else {
            // ��ͨ���ְ�ť��ʽ
            if (musicPlayer && musicPlayer->getCurrentMusic() == musicAlias) {
                setlinecolor(RGB(100, 255, 100)); // ��ǰ���ڲ��ŵ����ְ�ť�߿���ɫ
                setfillcolor(RGB(150, 255, 150)); // ��ǰ���ڲ��ŵ����ְ�ť�����ɫ
            }
        }

        // ���û�����ƺ���
        rect_button::draw();
    }
};