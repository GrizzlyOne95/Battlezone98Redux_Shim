#include "gas_copy_pool.h"
#include "bzr_hooks_internal.h"
#include "hook_engine.h"
#include "openshim_env_config.h"
#include "patcher.h"
#include <Windows.h>
#include <cstdint>
#include <cstring>

// GAS (the sound layer) gives every playing sound one entry from a fixed pool
// of 100 "copies"; LinkCopy (0x0043BDC0) chains it to the other playing
// instances of the same sample, and 0x0043B520 refuses to start a sound when
// the pool is empty. In a big fight the pool runs dry long before the voice
// cap does (SoundChannels raises that to 256), so sounds drop and every drop
// logs "LinkCopy out of copies".
//
// The pool is read and written by six functions and nowhere else (every
// reference to 0x0260C2E8..0x0260C927 in the image is inside them). The four
// small ones - init, the two chain walkers and the per-frame counter reset -
// carry the pool size as imm8 loop bounds, so they are replaced outright; the
// other two, LinkCopy and UnlinkCopy, only need their six array-base
// immediates pointed at the new array. The free-list head, free count and
// low-water mark stay at their stock globals.
namespace BZROpenShim::Hooks
{
    namespace
    {
        struct GasCopy
        {
            int32_t prev;
            int32_t next;
            int32_t counter;
            void* object;
        };
        static_assert(sizeof(GasCopy) == 16, "stock copy entries are 16 bytes");

        constexpr int32_t kPoolSize = 512;
        constexpr int32_t kStockPoolSize = 100;
        // gas_object field holding its copy index (-1 when unlinked).
        constexpr size_t kObjectCopyIndexOffset = 0x64;
        // Immediates inside the verified GasCopyPoolInit bytes.
        constexpr size_t kInitOldBaseImm = 0x09;
        constexpr size_t kInitFreeHeadImm = 0x61;
        constexpr size_t kInitFreeCountImm = 0x6A;
        constexpr size_t kInitMinFreeImm = 0x74;

        GasCopy g_Copies[kPoolSize];
        volatile int32_t* g_FreeHead = nullptr;
        volatile int32_t* g_FreeCount = nullptr;
        volatile int32_t* g_MinFree = nullptr;

        bool ValidIndex(int32_t index)
        {
            return index >= 0 && index < kPoolSize;
        }

        int32_t ChainHead(int32_t index)
        {
            for (int32_t steps = 0; steps <= kPoolSize && ValidIndex(g_Copies[index].prev); ++steps)
                index = g_Copies[index].prev;
            return index;
        }

        int32_t CopyIndexOf(const uint8_t* object)
        {
            int32_t index = -1;
            std::memcpy(&index, object + kObjectCopyIndexOffset, sizeof(index));
            return index;
        }

        // 0x0043BD20: every entry free, chained high to low.
        void __cdecl GasCopyPoolInit()
        {
            for (int32_t i = 0; i < kPoolSize; ++i)
                g_Copies[i] = { -1, i - 1, 0, nullptr };
            *g_FreeHead = kPoolSize - 1;
            *g_FreeCount = kPoolSize;
            *g_MinFree = kPoolSize;
        }

        // 0x0043C070: bumps the counter shared by every playing instance of
        // the object's sample and returns it.
        int __cdecl GasCopyBumpCounter(const uint8_t* object)
        {
            int32_t index = CopyIndexOf(object);
            if (!ValidIndex(index))
                return 1;
            index = ChainHead(index);
            const int32_t value = g_Copies[index].counter + 1;
            for (int32_t steps = 0; steps <= kPoolSize && ValidIndex(index); ++steps)
            {
                g_Copies[index].counter = value;
                index = g_Copies[index].next;
            }
            return value;
        }

        // 0x0043C120: how many instances of the object's sample are playing.
        int __cdecl GasCopyChainLength(const uint8_t* object)
        {
            int32_t index = CopyIndexOf(object);
            if (!ValidIndex(index))
                return 0;
            index = ChainHead(index);
            int count = 0;
            for (int32_t steps = 0; steps <= kPoolSize && ValidIndex(index); ++steps)
            {
                ++count;
                index = g_Copies[index].next;
            }
            return count;
        }

        // 0x0043C1C0: per-frame reset of the counters of in-use entries.
        void __cdecl GasCopyClearCounters()
        {
            for (GasCopy& copy : g_Copies)
            {
                if (copy.object)
                    copy.counter = 0;
            }
        }

        struct WrittenSite
        {
            uint32_t address;
            uint8_t original[5];
        };

        bool WriteSite(uint32_t address, const uint8_t (&bytes)[5], size_t len,
                       WrittenSite* written, size_t& writtenCount)
        {
            WrittenSite site = { address, {} };
            std::memcpy(site.original, reinterpret_cast<const void*>(static_cast<uintptr_t>(address)), len);
            if (!WritePatchBytes(address, bytes, len))
                return false;
            written[writtenCount++] = site;
            return true;
        }

        void BuildJump(uint32_t site, const void* target, uint8_t (&out)[5])
        {
            out[0] = 0xE9;
            const int32_t relative = static_cast<int32_t>(reinterpret_cast<uintptr_t>(target)) -
                                     static_cast<int32_t>(site + 5);
            std::memcpy(out + 1, &relative, sizeof(relative));
        }
    }

    void InstallGasCopyPoolIfPossible()
    {
        static bool s_done = false;
        if (s_done)
            return;
        s_done = true;
        if (EnvFlagEnabled("OPENSHIM_STOCK_SOUND_COPY_POOL"))
        {
            Log(L"[SOUND] copy pool: stock 100 kept (OPENSHIM_STOCK_SOUND_COPY_POOL)\n");
            return;
        }

        uint32_t init = 0, bump = 0, length = 0, clear = 0;
        uint32_t linkA = 0, linkB = 0, linkC = 0, unlinkA = 0, unlinkB = 0, unlinkC = 0;
        const HookEngine::EngineRow rows[] = {
            { "GasCopyPoolInit", &init },
            { "GasCopyBumpCounter", &bump },
            { "GasCopyChainLength", &length },
            { "GasCopyClearCounters", &clear },
            { "LinkCopyPoolBaseA", &linkA },
            { "LinkCopyPoolBaseB", &linkB },
            { "LinkCopyPoolBaseC", &linkC },
            { "UnlinkCopyPoolBaseA", &unlinkA },
            { "UnlinkCopyPoolBaseB", &unlinkB },
            { "UnlinkCopyPoolBaseC", &unlinkC },
        };
        if (!HookEngine::BindEngineRows("Sound copy pool", rows))
            return;

        const uint8_t* initBytes = reinterpret_cast<const uint8_t*>(static_cast<uintptr_t>(init));
        uint32_t oldBase = 0, freeHead = 0, freeCount = 0, minFree = 0;
        std::memcpy(&oldBase, initBytes + kInitOldBaseImm, sizeof(oldBase));
        std::memcpy(&freeHead, initBytes + kInitFreeHeadImm, sizeof(freeHead));
        std::memcpy(&freeCount, initBytes + kInitFreeCountImm, sizeof(freeCount));
        std::memcpy(&minFree, initBytes + kInitMinFreeImm, sizeof(minFree));
        g_FreeHead = reinterpret_cast<volatile int32_t*>(static_cast<uintptr_t>(freeHead));
        g_FreeCount = reinterpret_cast<volatile int32_t*>(static_cast<uintptr_t>(freeCount));
        g_MinFree = reinterpret_cast<volatile int32_t*>(static_cast<uintptr_t>(minFree));

        // Audio already up: live entries sit in the stock array, so moving it
        // under the game thread is not safe.
        if (*g_FreeCount != 0)
        {
            Log(L"[SOUND] copy pool: audio already initialised (free=%d); stock 100 kept\n",
                static_cast<int>(*g_FreeCount));
            return;
        }

        const uint32_t newBase = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&g_Copies[0]));
        uint8_t baseImm[5] = {};
        std::memcpy(baseImm, &newBase, sizeof(newBase));
        // Opcode length before each site's imm32: 81 /0 id is two bytes,
        // 05 id (add eax) one.
        const struct { uint32_t address; size_t immOffset; } baseSites[] = {
            { linkA, 2 }, { linkB, 2 }, { linkC, 2 },
            { unlinkA, 1 }, { unlinkB, 1 }, { unlinkC, 2 },
        };
        const struct { uint32_t address; const void* target; } jumps[] = {
            // Init last: until it is redirected the stock init would fill the
            // old array the patched sites no longer read.
            { bump, reinterpret_cast<const void*>(&GasCopyBumpCounter) },
            { length, reinterpret_cast<const void*>(&GasCopyChainLength) },
            { clear, reinterpret_cast<const void*>(&GasCopyClearCounters) },
            { init, reinterpret_cast<const void*>(&GasCopyPoolInit) },
        };

        WrittenSite written[_countof(baseSites) + _countof(jumps)] = {};
        size_t writtenCount = 0;
        bool ok = true;
        for (size_t i = 0; ok && i < _countof(baseSites); ++i)
        {
            ok = WriteSite(baseSites[i].address + static_cast<uint32_t>(baseSites[i].immOffset),
                           baseImm, sizeof(newBase), written, writtenCount);
        }
        for (size_t i = 0; ok && i < _countof(jumps); ++i)
        {
            uint8_t jump[5] = {};
            BuildJump(jumps[i].address, jumps[i].target, jump);
            ok = WriteSite(jumps[i].address, jump, sizeof(jump), written, writtenCount);
        }
        if (!ok)
        {
            for (size_t i = writtenCount; i-- > 0;)
            {
                const size_t len = i < _countof(baseSites) ? sizeof(newBase) : 5;
                WritePatchBytes(written[i].address, written[i].original, len);
            }
            Log(L"[SOUND] copy pool: patch write failed; restored %u site(s), stock 100 kept\n",
                static_cast<unsigned>(writtenCount));
            return;
        }

        // The stock init ran between the check above and the init redirect:
        // take its (still empty) entries over and free the rest.
        if (*g_FreeCount != 0)
        {
            std::memcpy(g_Copies, reinterpret_cast<const void*>(static_cast<uintptr_t>(oldBase)),
                        sizeof(GasCopy) * kStockPoolSize);
            for (int32_t i = kStockPoolSize; i < kPoolSize; ++i)
            {
                g_Copies[i] = { -1, *g_FreeHead, 0, nullptr };
                *g_FreeHead = i;
            }
            *g_FreeCount += kPoolSize - kStockPoolSize;
            *g_MinFree += kPoolSize - kStockPoolSize;
            Log(L"[SOUND] copy pool: stock init raced the install; migrated\n");
        }
        Log(L"[SOUND] copy pool: %d entries (stock %d)\n", kPoolSize, kStockPoolSize);
    }
}
