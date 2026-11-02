#pragma once
#include <atomic>
#include <memory>
#include <string>

namespace BZROpenShim::EmbeddedLan
{
    // Owned by the hosting game. No child process, platform API or remote service.
    class Host
    {
    public:
        Host();
        ~Host();
        bool Start(const std::string& privateIPv4, unsigned short port = 1337);
        void Stop();
        bool Running() const;
        std::string Error() const;
    private:
        struct Impl;
        std::unique_ptr<Impl> impl;
    };
}
