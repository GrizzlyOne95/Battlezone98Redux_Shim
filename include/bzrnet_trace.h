#pragma once

#include <cstdint>
#include <string>

namespace BZROpenShim
{
    struct BzrNetTraceConfig
    {
        bool enabled = false;
        bool privateForensic = false;
        uint32_t queueCapacity = 4096;
        uint32_t flushIntervalMs = 500;
    };

    bool InitializeBzrNetTrace(const BzrNetTraceConfig& config);
    void ShutdownBzrNetTrace();
    bool IsBzrNetTraceEnabled();
    bool IsBzrNetPrivateForensicTrace();
    const std::string& GetBzrNetCaptureId();

    // A Windows SOCKET value may be recycled after closesocket(). The trace
    // generation makes each lifetime unique even when the numeric handle is
    // reused later in the process.
    uint32_t BzrNetTraceRememberSocket(uintptr_t socketHandle);
    uint32_t BzrNetTraceSocketGeneration(uintptr_t socketHandle);
    void BzrNetTraceForgetSocket(uintptr_t socketHandle);

    // detailsJson must be a complete JSON object. Producer threads only enqueue
    // compact records; disk serialization/writes are owned by the writer thread.
    void EmitBzrNetTrace(
        const char* layer,
        const char* event,
        const char* direction,
        uint32_t socketId,
        uint32_t socketGeneration,
        const char* messageType,
        const std::string& detailsJson);
}
