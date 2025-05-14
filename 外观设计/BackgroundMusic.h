#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <unordered_map>

#pragma comment(lib,"winmm.lib")

class BackgroundMusic {
private:
    std::wstring currentMusicAlias; // 当前播放的音乐别名
    std::unordered_map<std::wstring, std::wstring> musicMap; // 音乐文件路径映射表
    bool isPlaying; // 是否正在播放音乐
    bool isMuted; // 是否静音

public:
    BackgroundMusic() : currentMusicAlias(L""), isPlaying(false), isMuted(false) {}

    ~BackgroundMusic() {
        stopAllMusic();
    }

    // 添加背景音乐文件
    void addMusic(const std::wstring& alias, const std::wstring& filePath) {
        musicMap[alias] = filePath;
        mciSendStringW((L"open \"" + filePath + L"\" alias " + alias).c_str(), NULL, 0, NULL);
    }

    // 播放指定别名的背景音乐
    void playMusic(const std::wstring& alias, bool loop = true) {
        if (musicMap.find(alias) == musicMap.end()) {
            return; // 音乐别名不存在
        }

        // 停止当前播放的音乐
        if (!currentMusicAlias.empty()) {
            mciSendStringW((L"stop " + currentMusicAlias).c_str(), NULL, 0, NULL);
        }

        currentMusicAlias = alias;
        isPlaying = true;

        // 播放音乐
        std::wstring command = L"play " + alias;
        if (loop) {
            command += L" repeat";
        }
        mciSendStringW(command.c_str(), NULL, 0, NULL);
    }

    // 停止当前播放的音乐
    void stopCurrentMusic() {
        if (!currentMusicAlias.empty() && isPlaying) {
            mciSendStringW((L"stop " + currentMusicAlias).c_str(), NULL, 0, NULL);
            isPlaying = false;
        }
    }

    // 停止所有音乐
    void stopAllMusic() {
        for (const auto& pair : musicMap) {
            mciSendStringW((L"stop " + pair.first).c_str(), NULL, 0, NULL);
        }
        isPlaying = false;
        currentMusicAlias.clear();
    }

    // 暂停当前音乐
    void pauseCurrentMusic() {
        if (!currentMusicAlias.empty() && isPlaying) {
            mciSendStringW((L"pause " + currentMusicAlias).c_str(), NULL, 0, NULL);
            isPlaying = false;
        }
    }

    // 恢复当前音乐
    void resumeCurrentMusic() {
        if (!currentMusicAlias.empty() && !isPlaying) {
            mciSendStringW((L"resume " + currentMusicAlias).c_str(), NULL, 0, NULL);
            isPlaying = true;
        }
    }

    // 静音/取消静音
    void toggleMute() {
        isMuted = !isMuted;
        for (const auto& pair : musicMap) {
            std::wstring command = L"setaudio " + pair.first + L" volume to ";
            command += isMuted ? L"0" : L"1000";
            mciSendStringW(command.c_str(), NULL, 0, NULL);
        }
    }

    // 获取当前播放的音乐别名
    std::wstring getCurrentMusic() const {
        return currentMusicAlias;
    }

    // 检查是否正在播放音乐
    bool isMusicPlaying() const {
        return isPlaying;
    }
};