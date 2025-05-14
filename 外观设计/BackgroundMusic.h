#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <unordered_map>

#pragma comment(lib,"winmm.lib")

class BackgroundMusic {
private:
    std::wstring currentMusicAlias; // ��ǰ���ŵ����ֱ���
    std::unordered_map<std::wstring, std::wstring> musicMap; // �����ļ�·��ӳ���
    bool isPlaying; // �Ƿ����ڲ�������
    bool isMuted; // �Ƿ���

public:
    BackgroundMusic() : currentMusicAlias(L""), isPlaying(false), isMuted(false) {}

    ~BackgroundMusic() {
        stopAllMusic();
    }

    // ��ӱ��������ļ�
    void addMusic(const std::wstring& alias, const std::wstring& filePath) {
        musicMap[alias] = filePath;
        mciSendStringW((L"open \"" + filePath + L"\" alias " + alias).c_str(), NULL, 0, NULL);
    }

    // ����ָ�������ı�������
    void playMusic(const std::wstring& alias, bool loop = true) {
        if (musicMap.find(alias) == musicMap.end()) {
            return; // ���ֱ���������
        }

        // ֹͣ��ǰ���ŵ�����
        if (!currentMusicAlias.empty()) {
            mciSendStringW((L"stop " + currentMusicAlias).c_str(), NULL, 0, NULL);
        }

        currentMusicAlias = alias;
        isPlaying = true;

        // ��������
        std::wstring command = L"play " + alias;
        if (loop) {
            command += L" repeat";
        }
        mciSendStringW(command.c_str(), NULL, 0, NULL);
    }

    // ֹͣ��ǰ���ŵ�����
    void stopCurrentMusic() {
        if (!currentMusicAlias.empty() && isPlaying) {
            mciSendStringW((L"stop " + currentMusicAlias).c_str(), NULL, 0, NULL);
            isPlaying = false;
        }
    }

    // ֹͣ��������
    void stopAllMusic() {
        for (const auto& pair : musicMap) {
            mciSendStringW((L"stop " + pair.first).c_str(), NULL, 0, NULL);
        }
        isPlaying = false;
        currentMusicAlias.clear();
    }

    // ��ͣ��ǰ����
    void pauseCurrentMusic() {
        if (!currentMusicAlias.empty() && isPlaying) {
            mciSendStringW((L"pause " + currentMusicAlias).c_str(), NULL, 0, NULL);
            isPlaying = false;
        }
    }

    // �ָ���ǰ����
    void resumeCurrentMusic() {
        if (!currentMusicAlias.empty() && !isPlaying) {
            mciSendStringW((L"resume " + currentMusicAlias).c_str(), NULL, 0, NULL);
            isPlaying = true;
        }
    }

    // ����/ȡ������
    void toggleMute() {
        isMuted = !isMuted;
        for (const auto& pair : musicMap) {
            std::wstring command = L"setaudio " + pair.first + L" volume to ";
            command += isMuted ? L"0" : L"1000";
            mciSendStringW(command.c_str(), NULL, 0, NULL);
        }
    }

    // ��ȡ��ǰ���ŵ����ֱ���
    std::wstring getCurrentMusic() const {
        return currentMusicAlias;
    }

    // ����Ƿ����ڲ�������
    bool isMusicPlaying() const {
        return isPlaying;
    }
};