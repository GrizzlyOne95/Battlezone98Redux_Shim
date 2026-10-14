#pragma once
#include <Windows.h>
#include <memory>
#include <string>
namespace BZROpenShim::FrameBridge
{
    class OwnWindowRecorder
    {
    public:
        OwnWindowRecorder();
        ~OwnWindowRecorder();
        // Own helper window only. No desktop, foreign HWND, or input APIs.
        void Start(HWND window,const std::string& path);
        void Stop();
    private:
        struct Impl;
        std::shared_ptr<Impl> impl_;
    };
}
