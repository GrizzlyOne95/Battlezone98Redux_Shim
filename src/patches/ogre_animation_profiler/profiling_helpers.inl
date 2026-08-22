            char* slash = std::strrchr(path, '\\');
            if (slash)
                *(slash + 1) = '\0';
            else
                path[0] = '\0';
            return std::string(path) + "openshim.ini";
        }

        DWORD ReadProcessEnvironmentValue(
            const char* name,
            char* value,
            DWORD capacity)
        {
            using FnGetEnvironmentVariableA =
                DWORD(WINAPI*)(LPCSTR, LPSTR, DWORD);
            static const FnGetEnvironmentVariableA getEnvironmentVariable =
                reinterpret_cast<FnGetEnvironmentVariableA>(GetProcAddress(
                    GetModuleHandleA("kernel32.dll"),
                    "GetEnvironmentVariableA"));
            return getEnvironmentVariable
                ? getEnvironmentVariable(name, value, capacity)
                : 0;
        }

        bool ProfilerRequested()
        {
            char envValue[64] = {};
            const DWORD envLength = ReadProcessEnvironmentValue(
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

        bool EnvironmentFlagEnabled(const char* name)
        {
            char value[64] = {};
            const DWORD length = ReadProcessEnvironmentValue(
                name,
                value,
                static_cast<DWORD>(sizeof(value)));
            return length > 0 && length < sizeof(value) && StringIsTruthy(value);
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

        const char* ProfilerStateName(ProfilerState state)
        {
            switch (state)
            {
            case ProfilerState::Disabled: return "Disabled";
            case ProfilerState::WaitingForOgre: return "WaitingForOgre";
            case ProfilerState::OgreReady: return "OgreReady";
            case ProfilerState::WaitingForDX11: return "WaitingForDX11";
            case ProfilerState::FullyActive: return "FullyActive";
            case ProfilerState::PartialDiagnostics: return "PartialDiagnostics";
            case ProfilerState::Failed: return "Failed";
            }
            return "Unknown";
        }

        void SetProfilerState(ProfilerState next, const char* reason)
        {
            const ProfilerState previous =
                g_ProfilerState.exchange(next, std::memory_order_acq_rel);
            if (previous == next)
                return;

            LogShimA(
                next == ProfilerState::Failed ? LogLevel::Warn : LogLevel::Info,
                kComponent,
                "[OgreProfile] state %s -> %s reason=%s ogre=%s renderQueue=%s dx11Context=%s present=%s",
                ProfilerStateName(previous),
                ProfilerStateName(next),
                reason ? reason : "unspecified",
                g_OgreHooksInstalled.load(std::memory_order_acquire) ? "active" : "unavailable",
                g_RenderQueueHookInstalled.load(std::memory_order_acquire) ? "active" : "unavailable",
                g_Dx11ContextObserved.load(std::memory_order_acquire) ? "active" : "unavailable",
                g_PresentObserved.load(std::memory_order_acquire) ? "active" : "unavailable");
        }

        void RefreshProfilerState(const char* reason)
        {
            const bool ogre = g_OgreHooksInstalled.load(std::memory_order_acquire);
            const bool dx11Imports = g_Dx11ImportsPatched.load(std::memory_order_acquire);
            const bool dx11Context = g_Dx11ContextObserved.load(std::memory_order_acquire);
            const bool present = g_PresentObserved.load(std::memory_order_acquire);
            const bool partial =
                g_RenderQueueHookInstalled.load(std::memory_order_acquire) ||
                g_RenderSystemObserverInstalled.load(std::memory_order_acquire);
            SetProfilerState(
                OgreProfilerAlgorithms::ComputeProfilerState(
                    g_Enabled.load(std::memory_order_acquire),
                    g_OgreInstallAttempted.load(std::memory_order_acquire),
                    ogre,
                    dx11Imports,
                    dx11Context,
                    present,
                    partial),
                reason);
        }

        size_t LatencyBucket(uint64_t ticks)
        {
            return OgreProfilerAlgorithms::LatencyBucketFromMicroseconds(TicksToUs(ticks));
        }

        size_t VertexBucket(size_t vertices)
        {
            return OgreProfilerAlgorithms::VertexBucket(vertices);
        }

        size_t MatrixBucket(size_t matrices)
        {
            return OgreProfilerAlgorithms::MatrixBucket(matrices);
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

        void CopyEntityMetadataString(
            std::array<char, kEntityMetadataLength>& destination,
            const std::string& source)
        {
            const size_t count = (std::min)(source.size(), destination.size() - 1);
            if (count)
                std::memcpy(destination.data(), source.data(), count);
            destination[count] = '\0';
        }

        void CaptureEntityMetadata(EntityProfileSlot* slot, const void* entity)
        {
            if (!slot || !entity || !g_OgreGetEntityName || !g_OgreEntityGetMesh ||
                !g_OgreGetResourceName || !g_OgreGetCastShadows)
            {
                return;
            }

            uint32_t expected = 0;
            if (!slot->metadataState.compare_exchange_strong(
                    expected, 1, std::memory_order_acq_rel, std::memory_order_relaxed))
            {
                return;
            }

            __try
            {
                CopyEntityMetadataString(slot->entityName, g_OgreGetEntityName(entity));
                const void* meshSharedPtr = g_OgreEntityGetMesh(entity);
                const void* mesh = meshSharedPtr
                    ? *reinterpret_cast<void* const*>(meshSharedPtr)
                    : nullptr;
                if (mesh)
                    CopyEntityMetadataString(slot->meshName, g_OgreGetResourceName(mesh));
                slot->castShadows = g_OgreGetCastShadows(entity);
                slot->metadataState.store(2, std::memory_order_release);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                slot->entityName[0] = '\0';
                slot->meshName[0] = '\0';
                slot->castShadows = false;
                slot->metadataState.store(2, std::memory_order_release);
            }
        }

        bool IsChunkNamedEntity(const EntityTopSample& sample)
        {
            return sample.metadataReady &&
                (OgreProfilerAlgorithms::ContainsAsciiCaseInsensitive(
                     sample.entityName.data(), "chunk") ||
                 OgreProfilerAlgorithms::ContainsAsciiCaseInsensitive(
                     sample.meshName.data(), "chunk"));
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

        DynamicGeometryProfileSlot* FindOrClaimDynamicGeometrySlot(
            const void* pointer)
        {
            if (!pointer)
                return nullptr;
            const uintptr_t key = reinterpret_cast<uintptr_t>(pointer);
            const size_t start = HashPointer(pointer) % kDynamicGeometryTableSize;
            for (size_t probe = 0; probe < kDynamicGeometryTableSize; ++probe)
            {
                DynamicGeometryProfileSlot& slot =
                    g_DynamicGeometryProfileSlots[
                        (start + probe) % kDynamicGeometryTableSize];
                uintptr_t current = slot.key.load(std::memory_order_relaxed);
                if (current == key)
                    return &slot;
                if (current == 0 && slot.key.compare_exchange_strong(
                        current, key,
                        std::memory_order_relaxed,
                        std::memory_order_relaxed))
                {
                    return &slot;
                }
            }
            return nullptr;
        }

        DynamicMaterialProfileSlot* FindOrClaimDynamicMaterialSlot(
            const void* pointer)
        {
            if (!pointer)
                return nullptr;
            const uintptr_t key = reinterpret_cast<uintptr_t>(pointer);
            const size_t start = HashPointer(pointer) % kDynamicMaterialTableSize;
            for (size_t probe = 0; probe < kDynamicMaterialTableSize; ++probe)
            {
                DynamicMaterialProfileSlot& slot =
                    g_DynamicMaterialProfileSlots[
                        (start + probe) % kDynamicMaterialTableSize];
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

        void CaptureDynamicMaterialMetadata(
            DynamicMaterialProfileSlot* slot,
            const void* material)
        {
            if (!slot || !material || !g_OgreGetResourceName)
                return;
            uint32_t expected = 0;
            if (!slot->metadataState.compare_exchange_strong(
                    expected, 1, std::memory_order_acq_rel, std::memory_order_relaxed))
            {
                return;
            }
            __try
            {
                CopyEntityMetadataString(
                    slot->materialName,
                    g_OgreGetResourceName(material));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                slot->materialName[0] = '\0';
            }
            slot->metadataState.store(2, std::memory_order_release);
        }

        void RecordFrameTime(uint64_t ticks)
        {
            if (!ticks)
                return;
            g_FrameTimeSamples.fetch_add(1, std::memory_order_relaxed);
            g_FrameTimeTicks.fetch_add(ticks, std::memory_order_relaxed);
            AtomicMax(g_FrameTimeMaxTicks, ticks);

            const uint64_t us = TicksToUs(ticks);
            const size_t bucket = OgreProfilerAlgorithms::FrameBucket(us);
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
            return OgreProfilerAlgorithms::PercentileFromHistogram(
                buckets, samples, percentile, kFrameTimeBucketUs);
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

        bool ModuleContainsAddress(HMODULE module, const void* address)
        {
            if (!module || !address)
                return false;
            const auto* base = reinterpret_cast<const uint8_t*>(module);
            const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return false;
            const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return false;
            const auto* candidate = static_cast<const uint8_t*>(address);
            return candidate >= base &&
                candidate < base + nt->OptionalHeader.SizeOfImage;
        }

        bool IsExecutableModuleAddress(HMODULE module, const void* address)
        {
            if (!ModuleContainsAddress(module, address))
                return false;
            MEMORY_BASIC_INFORMATION mbi{};
            if (VirtualQuery(address, &mbi, sizeof(mbi)) != sizeof(mbi) ||
                mbi.State != MEM_COMMIT || (mbi.Protect & PAGE_GUARD) != 0)
            {
                return false;
            }
            const DWORD protection = mbi.Protect & 0xffu;
            return protection == PAGE_EXECUTE ||
                protection == PAGE_EXECUTE_READ ||
                protection == PAGE_EXECUTE_READWRITE ||
                protection == PAGE_EXECUTE_WRITECOPY;
        }

        bool IsExecutableOgreAddress(const void* address)
        {
            return IsExecutableModuleAddress(GetModuleHandleA("OgreMain.dll"), address);
        }

        void* ResolveModuleExportImplementation(
            HMODULE module,
            void* exportAddress,
            const char* label)
        {
            if (!IsExecutableModuleAddress(module, exportAddress))
                return nullptr;

            uint8_t* current = static_cast<uint8_t*>(exportAddress);
            unsigned depth = 0;
            for (; depth < kMaxExportThunkDepth; ++depth)
            {
                if (current[0] != 0xE9)
                    break;

                int32_t relative = 0;
                std::memcpy(&relative, current + 1, sizeof(relative));
                uint8_t* destination = current + 5 + relative;
                if (!IsExecutableModuleAddress(module, destination) || destination == current)
                {
                    LogShimA(
                        LogLevel::Warn,
                        kComponent,
                        "[OgreProfile] %s unsupported export thunk depth=%u export=0x%p source=0x%p destination=0x%p",
                        label,
                        depth,
                        exportAddress,
                        current,
                        destination);
                    return nullptr;
                }
                current = destination;
            }

            if (depth == kMaxExportThunkDepth && current[0] == 0xE9)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile] %s export thunk exceeded maximum depth=%u export=0x%p",
                    label,
                    kMaxExportThunkDepth,
                    exportAddress);
                return nullptr;
            }

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] resolved %s implementation export=0x%p implementation=0x%p thunkDepth=%u",
                label,
                exportAddress,
                current,
                depth);
            return current;
        }

        void* ResolveOgreExportImplementation(void* exportAddress, const char* label)
        {
            return ResolveModuleExportImplementation(
                GetModuleHandleA("OgreMain.dll"), exportAddress, label);
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

