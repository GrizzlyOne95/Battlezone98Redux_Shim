            char* slash = std::strrchr(path, '\\');
            if (slash)
                *(slash + 1) = '\0';
            else
                path[0] = '\0';
            return std::string(path) + "openshim.ini";
        }

        bool ProfilerRequested()
        {
            char envValue[64] = {};
            const DWORD envLength = GetEnvironmentVariableA(
                kEnvironmentSwitch,
                envValue,
                static_cast<DWORD>(sizeof(envValue)));
            if (envLength > 0 && envLength < sizeof(envValue))
            {
                g_ProfilerRequestSource = "env";
                return StringIsTruthy(envValue);
            }

            const std::string iniPath = GetOpenShimIniPath();
            char iniValue[64] = {};
            const DWORD iniLength = GetPrivateProfileStringA(
                kIniSection,
                kIniKey,
                "",
                iniValue,
                static_cast<DWORD>(sizeof(iniValue)),
                iniPath.c_str());
            if (iniLength > 0 && iniLength < sizeof(iniValue))
            {
                g_ProfilerRequestSource = "ini";
                return StringIsTruthy(iniValue);
            }

            g_ProfilerRequestSource = "build-default";
            return kDefaultProfilerEnabled != 0;
        }

        uint32_t HashPointer(const void* pointer)
        {
            uintptr_t value = reinterpret_cast<uintptr_t>(pointer);
            value >>= 4;
            uint32_t x = static_cast<uint32_t>(value);
            x ^= x >> 16;
            x *= 0x7feb352du;
            x ^= x >> 15;
            x *= 0x846ca68bu;
            x ^= x >> 16;
            return x;
        }

        void BloomAdd(std::array<std::atomic<uint64_t>, kBloomWords>& bloom, const void* pointer)
        {
            if (!pointer)
                return;
            constexpr uint32_t kBitCount = static_cast<uint32_t>(kBloomWords * 64u);
            const uint32_t bitIndex = HashPointer(pointer) & (kBitCount - 1u);
            const size_t wordIndex = bitIndex >> 6;
            const uint64_t bit = 1ull << (bitIndex & 63u);
            bloom[wordIndex].fetch_or(bit, std::memory_order_relaxed);
        }

        uint64_t ReadQpc()
        {
            LARGE_INTEGER value{};
            QueryPerformanceCounter(&value);
            return static_cast<uint64_t>(value.QuadPart);
        }

        double TicksToMs(uint64_t ticks)
        {
            if (g_QpcFrequency.QuadPart <= 0)
                return 0.0;
            return static_cast<double>(ticks) * 1000.0 /
                static_cast<double>(g_QpcFrequency.QuadPart);
        }

        uint64_t TicksToUs(uint64_t ticks)
        {
            if (g_QpcFrequency.QuadPart <= 0)
                return 0;
            return static_cast<uint64_t>(
                static_cast<double>(ticks) * 1000000.0 /
                static_cast<double>(g_QpcFrequency.QuadPart));
        }

        void AtomicMax(std::atomic<uint64_t>& target, uint64_t value)
        {
            uint64_t current = target.load(std::memory_order_relaxed);
            while (current < value &&
                   !target.compare_exchange_weak(
                       current, value,
                       std::memory_order_relaxed,
                       std::memory_order_relaxed))
            {
            }
        }

        size_t LatencyBucket(uint64_t ticks)
        {
            const double ms = TicksToMs(ticks);
            if (ms < 0.025) return 0;
            if (ms < 0.050) return 1;
            if (ms < 0.100) return 2;
            if (ms < 0.200) return 3;
            if (ms < 0.400) return 4;
            if (ms < 0.800) return 5;
            return 6;
        }

        size_t VertexBucket(size_t vertices)
        {
            if (vertices < 1024) return 0;
            if (vertices < 2048) return 1;
            if (vertices < 4096) return 2;
            if (vertices < 8192) return 3;
            if (vertices < 12288) return 4;
            if (vertices < 16384) return 5;
            if (vertices < 32768) return 6;
            return 7;
        }

        size_t MatrixBucket(size_t matrices)
        {
            if (matrices <= 8) return 0;
            if (matrices <= 16) return 1;
            if (matrices <= 32) return 2;
            if (matrices <= 64) return 3;
            return 4;
        }

        EntityProfileSlot* FindOrClaimEntitySlot(const void* pointer)
        {
            if (!pointer)
                return nullptr;
            const uintptr_t key = reinterpret_cast<uintptr_t>(pointer);
            size_t index = HashPointer(pointer) & (kEntityTableSize - 1);
            for (size_t probe = 0; probe < kProfileProbeCount; ++probe)
            {
                EntityProfileSlot& slot = g_EntityProfileSlots[(index + probe) & (kEntityTableSize - 1)];
                uintptr_t current = slot.key.load(std::memory_order_relaxed);
                if (current == key)
                    return &slot;
                if (current == 0 &&
                    slot.key.compare_exchange_strong(
                        current, key,
                        std::memory_order_relaxed,
                        std::memory_order_relaxed))
                {
                    return &slot;
                }
            }
            return nullptr;
        }

        SourceProfileSlot* FindOrClaimSourceSlot(const void* pointer, size_t sourceVertices)
        {
            if (!pointer)
                return nullptr;
            const uintptr_t key = reinterpret_cast<uintptr_t>(pointer);
            size_t index = HashPointer(pointer) & (kSourceTableSize - 1);
            for (size_t probe = 0; probe < kProfileProbeCount; ++probe)
            {
                SourceProfileSlot& slot = g_SourceProfileSlots[(index + probe) & (kSourceTableSize - 1)];
                uintptr_t current = slot.key.load(std::memory_order_relaxed);
                if (current == key)
                {
                    if (sourceVertices)
                        slot.sourceVertices.store(sourceVertices, std::memory_order_relaxed);
                    return &slot;
                }
                if (current == 0 &&
                    slot.key.compare_exchange_strong(
                        current, key,
                        std::memory_order_relaxed,
                        std::memory_order_relaxed))
                {
                    slot.sourceVertices.store(sourceVertices, std::memory_order_relaxed);
                    return &slot;
                }
            }
            return nullptr;
        }

        void RecordFrameTime(uint64_t ticks)
        {
            if (!ticks)
                return;
            g_FrameTimeSamples.fetch_add(1, std::memory_order_relaxed);
            g_FrameTimeTicks.fetch_add(ticks, std::memory_order_relaxed);
            AtomicMax(g_FrameTimeMaxTicks, ticks);

            const uint64_t us = TicksToUs(ticks);
            size_t bucket = static_cast<size_t>(us / kFrameTimeBucketUs);
            if (bucket >= kFrameTimeBucketCount)
                bucket = kFrameTimeBucketCount - 1;
            g_FrameTimeBuckets[bucket].fetch_add(1, std::memory_order_relaxed);
            if (us > 16667) g_FrameOver1667.fetch_add(1, std::memory_order_relaxed);
            if (us > 25000) g_FrameOver2500.fetch_add(1, std::memory_order_relaxed);
            if (us > 33333) g_FrameOver3333.fetch_add(1, std::memory_order_relaxed);
        }

        double PercentileFromHistogram(
            const std::array<uint64_t, kFrameTimeBucketCount>& buckets,
            uint64_t samples,
            unsigned percentile)
        {
            if (!samples)
                return 0.0;
            const uint64_t target = (samples * percentile + 99u) / 100u;
            uint64_t cumulative = 0;
            for (size_t i = 0; i < buckets.size(); ++i)
            {
                cumulative += buckets[i];
                if (cumulative >= target)
                    return static_cast<double>((i + 1) * kFrameTimeBucketUs) / 1000.0;
            }
            return static_cast<double>(kFrameTimeBucketCount * kFrameTimeBucketUs) / 1000.0;
        }

        size_t ReadVertexCount(const Ogre::VertexData* data)
        {
            if (!data)
                return 0;

            size_t value = 0;
            __try
            {
                value = data->vertexCount;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }

            return value <= kMaxSaneVertexCount ? value : 0;
        }

        bool WriteRel32(uint8_t* operand, int32_t value)
        {
            if (!operand)
                return false;
            DWORD oldProtect = 0;
            if (!VirtualProtect(operand, sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;
            std::memcpy(operand, &value, sizeof(value));
            DWORD ignored = 0;
            VirtualProtect(operand, sizeof(value), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), operand - 1, 5);
            return true;
        }

        bool WritePointer(void** slot, void* value)
        {
            if (!slot)
                return false;
            DWORD oldProtect = 0;
            if (!VirtualProtect(slot, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;
            *slot = value;
            DWORD ignored = 0;
            VirtualProtect(slot, sizeof(void*), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), slot, sizeof(void*));
            return true;
        }

        std::vector<ExportMatch> FindExportsContaining(const char* token)
        {
            std::vector<ExportMatch> matches;
            if (!token || !*token)
                return matches;

            HMODULE module = GetModuleHandleA("OgreMain.dll");
            if (!module)
                return matches;

            auto* base = reinterpret_cast<uint8_t*>(module);
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return matches;
            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return matches;

            const IMAGE_DATA_DIRECTORY& directory =
                nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
            if (!directory.VirtualAddress || !directory.Size)
                return matches;

            auto* exports = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(base + directory.VirtualAddress);
            auto* names = reinterpret_cast<DWORD*>(base + exports->AddressOfNames);
            auto* ordinals = reinterpret_cast<WORD*>(base + exports->AddressOfNameOrdinals);
            auto* functions = reinterpret_cast<DWORD*>(base + exports->AddressOfFunctions);

            for (DWORD i = 0; i < exports->NumberOfNames; ++i)
            {
                const char* name = reinterpret_cast<const char*>(base + names[i]);
                if (!name || std::strstr(name, token) == nullptr)
                    continue;

                const WORD ordinal = ordinals[i];
                if (ordinal >= exports->NumberOfFunctions)
                    continue;
                const DWORD functionRva = functions[ordinal];

                // Ignore forwarded exports.
                if (functionRva >= directory.VirtualAddress &&
                    functionRva < directory.VirtualAddress + directory.Size)
                {
                    continue;
                }

                void* address = base + functionRva;
                if (OgreRuntime::ContainsAddress(address))
                    matches.push_back({ name, address });
            }
            return matches;
        }

        void* FindUniqueFunctionExport(const char* token, const char* label)
        {
            const auto matches = FindExportsContaining(token);
            if (matches.size() != 1)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile] %s export match count=%u token=%s; observer disabled",
                    label,
                    static_cast<unsigned>(matches.size()),
                    token);
                return nullptr;
            }

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] resolved %s export=%s address=0x%p",
                label,
                matches[0].name.c_str(),
                matches[0].address);
            return matches[0].address;
        }

