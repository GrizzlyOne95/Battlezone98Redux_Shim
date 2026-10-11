#pragma once
#include <Windows.h>

namespace BZROpenShim {
// Keep observational socket queries from changing the API's last-error state,
// including after a successful IOCP dequeue (the native Asio caller reads it).
class Win32LastErrorScope {
    DWORD saved_ = GetLastError();
public:
    Win32LastErrorScope() = default;
    ~Win32LastErrorScope() { Restore(); }
    void Capture() { saved_ = GetLastError(); }
    void Restore() const { SetLastError(saved_); }
    Win32LastErrorScope(const Win32LastErrorScope&) = delete;
    Win32LastErrorScope& operator=(const Win32LastErrorScope&) = delete;
};
}
