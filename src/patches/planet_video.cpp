#include "planet_video.h"
#include "planet_video_policy.h"
#include "bzr_string.h"
#include "hook_engine.h"
#include "shim_log.h"
#include <Windows.h>
#include <string>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        using Play = void(__thiscall*)(void*, bool);
        using PlayLoop = void(__thiscall*)(void*, int, bool);
        using IntroSound = void(__thiscall*)(void*, const char*);
        using GetSize = size_t(__cdecl*)(const char*);
        using UseItem = void*(__cdecl*)(const char*);
        using UnlockItem = void(__cdecl*)(const char*);
        Play g_Play = nullptr;
        PlayLoop g_PlayLoop = nullptr;
        IntroSound g_IntroSound = nullptr;
        GetSize g_GetSize = nullptr;
        UseItem g_UseItem = nullptr;
        UnlockItem g_UnlockItem = nullptr;
        uintptr_t g_MissionSlot = 0;

        // The guarded cUI_View play/loop wrappers read Ogre clip at +0x140.
        constexpr uintptr_t kVideoClipOffset = 0x140;

        template<class T> T Export(HMODULE module, const char* name)
        {
            return reinterpret_cast<T>(GetProcAddress(module, name));
        }

        struct VideoApi
        {
            using GetClip = void*(__thiscall*)(void*);
            using GetName = const BzrString*(__thiscall*)(void*);
            using Fps = float(__thiscall*)(void*);
            using Count = int(__thiscall*)(void*);
            GetClip getClip = nullptr;
            GetName getName = nullptr;
            Fps fps = nullptr;
            Count count = nullptr;

            bool Bind()
            {
                // Only use modules the game has already loaded; no alternate
                // DLL search path, private player, or dependency is introduced.
                auto plugin = GetModuleHandleW(L"Plugin_TheoraVideoSystem.dll");
                auto player = GetModuleHandleW(L"libtheoraplayer.dll");
                if (!plugin || !player) return false;
                getClip = Export<GetClip>(plugin, "?getClip@OgreTheoraVideoClip@Ogre@@QBEPAVVideoClip@theoraplayer@@XZ");
                getName = Export<GetName>(plugin, "?getName@OgreTheoraVideoClip@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
                fps = Export<Fps>(player, "?getFps@VideoClip@theoraplayer@@QBEMXZ");
                count = Export<Count>(player, "?getFramesCount@VideoClip@theoraplayer@@QBEHXZ");
                return getClip && getName && fps && count;
            }
        };

        bool ReadName(const BzrString* value, std::string& out)
        {
            BzrString copy{};
            if (!value || !HookEngine::ReadMemory(reinterpret_cast<uintptr_t>(value), &copy, sizeof(copy)) ||
                copy.size == 0 || copy.size > 63 || copy.capacity < copy.size ||
                (copy.capacity <= 15 && copy.size > 15)) return false;
            char bytes[64]{};
            const void* data = copy.capacity > 15 ? static_cast<void*>(copy.heap) : copy.small;
            if (copy.capacity > 15)
            {
                if (!copy.heap || !HookEngine::ReadMemory(reinterpret_cast<uintptr_t>(data), bytes, copy.size)) return false;
            }
            else memcpy(bytes, copy.small, copy.size);
            out.assign(bytes, copy.size);
            return PlanetVideo::IsResourceName(out, ".ogv");
        }

        // The engine VFS keeps its own item locks. Never retain a pointer into
        // it after UnlockItem, and release exactly one successful UseItem.
        struct ItemLock
        {
            const char* name;
            ~ItemLock() { g_UnlockItem(name); }
        };

        bool ReadSidecar(const std::string& name, std::string& text)
        {
            const size_t size = g_GetSize(name.c_str());
            if (!size || size > PlanetVideo::kMaxConfigBytes) return false;
            const void* data = g_UseItem(name.c_str());
            if (!data) return false;
            ItemLock lock{name.c_str()};
            text.resize(size);
            return HookEngine::ReadMemory(reinterpret_cast<uintptr_t>(data), text.data(), size);
        }

        bool TryPlay(void* view, void* constructorOwner)
        {
            uintptr_t mission = 0, wrapper = 0;
            const auto address = reinterpret_cast<uintptr_t>(view);
            if (!view || !HookEngine::ReadMemory(g_MissionSlot, &mission, sizeof(mission)) || !mission ||
                mission != reinterpret_cast<uintptr_t>(constructorOwner) ||
                !HookEngine::ReadMemory(address + kVideoClipOffset, &wrapper, sizeof(wrapper)) || !wrapper) return false;
            VideoApi api;
            if (!api.Bind()) return false;
            std::string name;
            if (!ReadName(api.getName(reinterpret_cast<void*>(wrapper)), name)) return false;
            const auto sidecar = PlanetVideo::SidecarName(name);
            std::string text;
            if (sidecar.empty() || !ReadSidecar(sidecar, text)) return false;
            PlanetVideo::Config config;
            std::string error;
            if (!PlanetVideo::Parse(text, config, error))
            {
                LogShimA(LogLevel::Warn, "planet-video", "%s: %s; keeping stock playback", sidecar.c_str(), error.c_str());
                return false;
            }
            void* clip = api.getClip(reinterpret_cast<void*>(wrapper));
            if (!clip) return false;
            int loopFrame = 0;
            const float fps = api.fps(clip);
            if (!PlanetVideo::LoopFrame(config, fps, api.count(clip), loopFrame))
            {
                LogShimA(LogLevel::Warn, "planet-video", "%s: loop start outside video; keeping stock playback", sidecar.c_str());
                return false;
            }
            // Redux and its plugin own playback, the clip, and the sound handle.
            // No frame polling, retained engine pointers, or cleanup hooks.
            g_PlayLoop(view, loopFrame, config.startAtLoop);
            if (!config.startAtLoop && !config.introSound.empty())
            {
                // Once the loop is committed, an optional audio failure must
                // not reset it by falling through to whole-file playback.
                try { g_IntroSound(reinterpret_cast<void*>(mission), config.introSound.c_str()); }
                catch (...) { LogShimA(LogLevel::Warn, "planet-video", "%s: intro sound failed; video loop retained", name.c_str()); }
            }
            LogShimA(LogLevel::Info, "planet-video", "%s: fps=%.3f loop=%d (%.3fs) start=%s sound=%s",
                name.c_str(), static_cast<double>(fps), loopFrame, config.loopStartSeconds,
                config.startAtLoop ? "loop" : "intro",
                !config.startAtLoop && !config.introSound.empty() ? config.introSound.c_str() : "none");
            return true;
        }

        void __fastcall CustomPlanetPlay(void* view, void* constructorOwner, bool loop)
        {
            try { if (loop && TryPlay(view, constructorOwner)) return; }
            catch (...) { LogShimA(LogLevel::Warn, "planet-video", "configuration failed; keeping stock playback"); }
            g_Play(view, loop);
        }

        // This CALL executes inside the guarded GOG cUI_Mission constructor,
        // before its movie is added to Middle_Overlay at the following call.
        // Pass that constructor's saved this in EDX; fastcall consumes the
        // original bool from the stack and returns with the same RET 4 ABI.
        // The MissionSlot signature independently verifies this frame slot.
        __declspec(naked) void CustomPlanetPlayEntry()
        {
            __asm {
                mov edx, dword ptr [ebp - 01F530h]
                jmp CustomPlanetPlay
            }
        }
    }

    void* PrepareCustomPlanetVideoHook(uint32_t callAddress)
    {
        void* original = HookEngine::ResolveRelCallTarget(callAddress);
        const auto expected = HookEngine::ResolveNamedAddress("PlanetVideo::ViewPlay");
        const auto playLoop = HookEngine::ResolveNamedAddress("PlanetVideo::ViewPlayLoop");
        const auto sound = HookEngine::ResolveNamedAddress("PlanetVideo::MissionIntroSound");
        const auto mission = HookEngine::ResolveNamedAddress("PlanetVideo::MissionSlot");
        const auto size = HookEngine::ResolveNamedAddress("PlanetVideo::GetItemSize");
        const auto use = HookEngine::ResolveNamedAddress("PlanetVideo::UseItem");
        const auto unlock = HookEngine::ResolveNamedAddress("PlanetVideo::UnlockItem");
        if (!original || reinterpret_cast<uintptr_t>(original) != expected || !playLoop || !sound ||
            !mission || !size || !use || !unlock)
        {
            LogShimA(LogLevel::Warn, "planet-video", "custom play binding incomplete; hook not installed");
            return nullptr;
        }
        g_Play = reinterpret_cast<Play>(original);
        g_PlayLoop = reinterpret_cast<PlayLoop>(playLoop);
        g_IntroSound = reinterpret_cast<IntroSound>(sound);
        g_MissionSlot = mission;
        g_GetSize = reinterpret_cast<GetSize>(size);
        g_UseItem = reinterpret_cast<UseItem>(use);
        g_UnlockItem = reinterpret_cast<UnlockItem>(unlock);
        return reinterpret_cast<void*>(CustomPlanetPlayEntry);
    }
}
