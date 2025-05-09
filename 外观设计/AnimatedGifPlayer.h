#pragma once
#include "MediaPlayerBase.h"
#include <windows.h>
#include <easyx.h>

#include <string>
#include <algorithm>
#include <filesystem>
#include <vector>
#include "memory"
#include <chrono>
#include <thread>  // 用于轻量级等待
#include <cwctype>
#include"iostream"
#pragma comment(lib, "MSIMG32.LIB")

class AnimatedGifPlayer :
    public MediaPlayerBase
{
private:
    std::vector<std::shared_ptr<IMAGE>> frames;
    size_t currentFrame;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
    int frameRate;//FPS
    const std::wstring& basePath;
    int Maxpng;
public:
    AnimatedGifPlayer(int x, int y, int width, int height,const std::wstring& basePath, int Maxpng) :
        MediaPlayerBase(x, y, width, height), currentFrame(0), frameRate(30), basePath(basePath), Maxpng(Maxpng){

        lastFrameTime = std::chrono::high_resolution_clock::now();
        frames.reserve(100);
       // loadImages( basePath,  Maxpng);
        loadImages(basePath, Maxpng);
        this->width = width;
        this->height = height;
    }

    ~AnimatedGifPlayer() {
    
    }

    bool loadImages(const std::wstring& basePath, int INdex) {

        int frameIndex = 1;
        while (frameIndex <= INdex) {
            std::wstring filename = basePath + std::to_wstring(frameIndex) + L".png";
            auto img = std::make_shared<IMAGE>();
            if (frames.size() >= frames.capacity()) {
                frames.reserve(frames.size() + 10);
            }
           
            frames.push_back(img);
            loadimage(img.get(), filename.c_str());
          
           
            std::wcerr << "成功加载图片: " << filename << std::endl;
            frameIndex++;


        }
        return !frames.empty();
    }


    void updateFrame() {
        if (frames.empty()) {
          
            return;
        
        }
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = currentTime - lastFrameTime;

        if (elapsed >= std::chrono::milliseconds(frameRate)) {
            currentFrame = (currentFrame + 1) % frames.size();
            lastFrameTime = currentTime;
        }
    }


   virtual void draw() {
       
       updateFrame();
       if (!frames.empty()) {
           transparentimage3(NULL, x, y, frames[currentFrame].get());
       }
   }

    void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg) {
        HDC dstDC = GetImageHDC(dstimg);
        HDC srcDC = GetImageHDC(srcimg);
       


       int w1 = srcimg->getwidth();
       int h1 = srcimg->getheight(); 

        BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
        AlphaBlend(dstDC, x, y, w1, h1, srcDC, 0, 0, w1, h1, bf);
    }
};
//bool loadImagesFromUserPath(const std::wstring& basePath) {
//    namespace fs = std::filesystem;
//    int loadedCount = 0;

//    try {
//        for (const auto& entry : fs::directory_iterator(basePath)) {
//            if (entry.is_regular_file() && entry.path().extension() == L".png") {
//                auto img = std::make_unique<IMAGE>();
//                if (frames.size() >= frames.capacity()) {
//                    try {
//                        frames.reserve(frames.size() + 10);
//                    }
//                    catch (const std::bad_alloc& e) {
//                        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
//                        return false;
//                    }
//                }
//                Resize(img.get(), width, height);
//                loadimage(img.get(), entry.path().wstring().c_str());
//                    if (img->getwidth() > 0 && img->getheight() > 0) {
//                        // 调用 Resize 函数调整图片大小
//                        
//                        frames.push_back(img);
//                        ++loadedCount;
//                    }
//                    
//               
//               
//            }
//        }
//    }
//    catch (const fs::filesystem_error& e) {
//        std::wcerr << L"Filesystem error: " << e.what() << std::endl;
//        return false;
//    }

//    return loadedCount > 0;
//}