#pragma once
#include <atomic>
#include <memory>
#include <string>

namespace BZROpenShim::EmbeddedLan
{
    // Worker thread, once per accepted connection: false refuses it; otherwise
    // fills the Steam id it may log in as ("" = none) and whether a no-auth
    // LAN login is allowed. Null policy: LAN logins only, as before.
    using AdmissionPolicy = bool (*)(const std::string& sourceIPv4, std::string& steamId, bool& lan);
    // Owned by the hosting game. No child process, platform API or remote service.
    class Host
    {
    public:
        Host();
        ~Host();
        bool Start(const std::string& privateIPv4, unsigned short port = 1337, AdmissionPolicy policy = nullptr);
        void Stop();
        bool Running() const;
        std::string Error() const;
    private:
        struct Impl;
        std::unique_ptr<Impl> impl;
    };
}
