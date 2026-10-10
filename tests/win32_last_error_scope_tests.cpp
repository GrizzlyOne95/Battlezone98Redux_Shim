#include <winsock2.h>
#include "win32_last_error_scope.h"
#include <cstdio>

static int failures = 0;
static void Check(bool ok, const char* message) {
    if (!ok) { std::fprintf(stderr, "FAIL: %s\n", message); ++failures; }
}
int main() {
    WSADATA data{};
    Check(WSAStartup(MAKEWORD(2, 2), &data) == 0, "Winsock initialized");
    SOCKET socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    HANDLE port = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 1);
    OVERLAPPED sent{}, *received = nullptr;
    Check(PostQueuedCompletionStatus(port, 25, 7, &sent) != FALSE, "completion posted");
    DWORD bytes = 0; ULONG_PTR key = 0;
    SetLastError(0);
    BOOL ok = GetQueuedCompletionStatus(port, &bytes, &key, &received, 1000);
    DWORD completionError = GetLastError();
    {
        BZROpenShim::Win32LastErrorScope preserve;
        sockaddr_storage peer{}; int length = sizeof(peer);
        Check(getpeername(socketHandle, reinterpret_cast<sockaddr*>(&peer), &length) == SOCKET_ERROR,
            "unconnected UDP metadata query fails");
        Check(WSAGetLastError() == WSAENOTCONN, "metadata overwrote last-error with 10057");
    }
    Check(ok && received == &sent && bytes == 25 && key == 7, "successful completion payload preserved");
    Check(GetLastError() == completionError, "successful IOCP error state preserved for native Asio caller");
    received = nullptr;
    ok = GetQueuedCompletionStatus(port, &bytes, &key, &received, 0);
    DWORD timeoutError = GetLastError();
    {
        BZROpenShim::Win32LastErrorScope preserve;
        SetLastError(10057);
    }
    Check(!ok && !received && timeoutError == WAIT_TIMEOUT && GetLastError() == WAIT_TIMEOUT,
        "failed completion error preserved");
    SetLastError(123);
    {
        BZROpenShim::Win32LastErrorScope preserve;
        SetLastError(456); preserve.Restore();
        Check(GetLastError() == 123, "pre-call diagnostic error restored");
        SetLastError(789); preserve.Capture(); SetLastError(10057);
    }
    Check(GetLastError() == 789, "API result replaces pre-call error state");
    closesocket(socketHandle); CloseHandle(port); WSACleanup();
    return failures ? 1 : 0;
}
