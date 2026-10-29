#pragma once
#include "direct_lan_mesh.h"
#include "direct_lan_redux_adapter.h"

namespace BZROpenShim::DirectLan::Redux
{
    // Receive packet callbacks borrow sender/data only for the duration of
    // the call. The caller owns every handler and clears it before destruction.
    using PacketHandler = void(*)(void* context, void* peerObject, const Identity&, const uint8_t*, uint32_t);
    class PeerBridge
    {
    public:
        PeerBridge(Adapter&, Mesh&);
        ~PeerBridge();
        PeerBridge(const PeerBridge&) = delete;
        PeerBridge& operator=(const PeerBridge&) = delete;
        void SetHandler(uint8_t kind, PacketHandler, void* context);
        void RemoveHandler(uint8_t kind, PacketHandler, void* context);
        void SetDefaultHandler(PacketHandler, void* context);
        void ClearHandlers();
        bool Send(const Identity&, const void* data, uint32_t size, bool reliable);
        void Pump();
#if defined(_MSC_VER) && defined(_M_IX86)
        // Qualified receive ABI: native handler vtable +4, ECX=handler,
        // stack=(peerObject, sender identity pointer, bytes, count), ret 16.
        void SetNativeHandler(uint8_t kind, void* handler);
        void RemoveNativeHandler(uint8_t kind, void* handler);
        void SetNativeDefaultHandler(void* handler);
#endif
#ifdef OPENSHIM_DIRECT_LAN_ABI_TEST
        // Full four-entry P2P query/send/pump surface for isolated tests only.
        // Does not implement the engine's base registration-map layout.
        void* QualificationObject();
#endif
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
