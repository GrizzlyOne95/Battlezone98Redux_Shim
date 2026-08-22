            char* slash = std::strrchr(path, '\\');
            if (slash)
                *(slash + 1) = '\0';
            else
                path[0] = '\0';
            return std::string(path) + "openshim.ini";
        }

        enum class ConfiguredRenderer
        {
            Unknown,
            Direct3D9,
            Direct3D11,
            Other,
        };

        const char* ConfiguredRendererName(ConfiguredRenderer renderer)
        {
            switch (renderer)
            {
            case ConfiguredRenderer::Direct3D9:
                return "Direct3D9";
            case ConfiguredRenderer::Direct3D11:
                return "Direct3D11";
            case ConfiguredRenderer::Other:
                return "other";
            default:
                return "unknown";
            }
        }

        ConfiguredRenderer ReadConfiguredRenderer()
        {
            char path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
            if (!length || length >= MAX_PATH)
                return ConfiguredRenderer::Unknown;

            char* slash = std::strrchr(path, '\\');
            if (!slash)
                return ConfiguredRenderer::Unknown;
            const size_t directoryLength = static_cast<size_t>(slash + 1 - path);
            if (directoryLength + sizeof("Ogre.cfg") > MAX_PATH)
                return ConfiguredRenderer::Unknown;
            strcpy_s(slash + 1, MAX_PATH - directoryLength, "Ogre.cfg");

            HANDLE file = CreateFileA(
                path,
                GENERIC_READ,
                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                nullptr,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                nullptr);
            if (file == INVALID_HANDLE_VALUE)
                return ConfiguredRenderer::Unknown;

            char contents[4096] = {};
            DWORD bytesRead = 0;
            const BOOL readOk = ReadFile(
                file,
                contents,
                static_cast<DWORD>(sizeof(contents) - 1),
                &bytesRead,
                nullptr);
            CloseHandle(file);
            if (!readOk || !bytesRead)
                return ConfiguredRenderer::Unknown;
            contents[bytesRead] = '\0';

            const char key[] = "Render System=";
            const char* value = std::strstr(contents, key);
            if (!value)
                return ConfiguredRenderer::Unknown;
            value += sizeof(key) - 1;
            if (std::strncmp(value, "Direct3D9 Rendering Subsystem", 29) == 0)
                return ConfiguredRenderer::Direct3D9;
            if (std::strncmp(value, "Direct3D11 Rendering Subsystem", 30) == 0)
                return ConfiguredRenderer::Direct3D11;
            return ConfiguredRenderer::Other;
        }

        bool ModuleImageMatches(
            HMODULE module,
            DWORD expectedTimestamp,
            DWORD expectedImageSize)
        {
            if (!module)
                return false;
            __try
            {
                const auto* base = reinterpret_cast<const uint8_t*>(module);
                const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
                if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                    return false;
                const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(
                    base + dos->e_lfanew);
                return nt->Signature == IMAGE_NT_SIGNATURE &&
                    nt->FileHeader.TimeDateStamp == expectedTimestamp &&
                    nt->OptionalHeader.SizeOfImage == expectedImageSize;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool IsValidatedGogChunkShadowRuntime(HMODULE ogreModule)
        {
            // Battlezone 2.2.301 GOG executable SHA-256:
            // 8D71F56C1314E69A8AD38F4EEAF20A8FF825965A84CF196E5F77EA4CC3377413.
            // Retail OgreMain.dll SHA-256:
            // E5E693960B95AD0D60733A3B688464A6C6CBA234E86950698F9C2BEA4ACFEB45.
            // PE identity is checked before touching a vtable; exports and the
            // exact target function pointer provide a second ABI check.
            return ModuleImageMatches(
                       GetModuleHandleA(nullptr), 0x58D9D6CCu, 0x0290F000u) &&
                ModuleImageMatches(ogreModule, 0x5866BF6Au, 0x00A65000u);
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
            case ProfilerState::WaitingForRenderer: return "WaitingForRenderer";
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
                "[OgreProfile] state %s -> %s reason=%s ogre=%s renderQueue=%s dx11Context=%s d3d9Device=%s present=%s",
                ProfilerStateName(previous),
                ProfilerStateName(next),
                reason ? reason : "unspecified",
                g_OgreHooksInstalled.load(std::memory_order_acquire) ? "active" : "unavailable",
                g_RenderQueueHookInstalled.load(std::memory_order_acquire) ? "active" : "unavailable",
                g_Dx11ContextObserved.load(std::memory_order_acquire) ? "active" : "unavailable",
                g_D3D9DeviceObserved.load(std::memory_order_acquire) ? "active" : "unavailable",
                g_PresentObserved.load(std::memory_order_acquire) ? "active" : "unavailable");
        }

        void RefreshProfilerState(const char* reason)
        {
            const bool ogre = g_OgreHooksInstalled.load(std::memory_order_acquire);
            const bool dx11Imports = g_Dx11ImportsPatched.load(std::memory_order_acquire);
            const bool dx11Context = g_Dx11ContextObserved.load(std::memory_order_acquire);
            const bool d3d9Device = g_D3D9DeviceObserved.load(std::memory_order_acquire);
            const bool present = g_PresentObserved.load(std::memory_order_acquire);
            const bool partial =
                g_RenderQueueHookInstalled.load(std::memory_order_acquire) ||
                g_RenderSystemObserverInstalled.load(std::memory_order_acquire);
            SetProfilerState(
                OgreProfilerAlgorithms::ComputeProfilerState(
                    g_Enabled.load(std::memory_order_acquire),
                    g_OgreInstallAttempted.load(std::memory_order_acquire),
                    ogre,
                    dx11Imports ||
                        g_D3D9RenderSystemObserverInstalled.load(
                            std::memory_order_acquire),
                    dx11Context || d3d9Device,
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

        CameraProfileSlot* FindOrClaimCameraSlot(const void* pointer)
        {
            if (!pointer)
                return nullptr;
            const uintptr_t key = reinterpret_cast<uintptr_t>(pointer);
            const size_t start = HashPointer(pointer) & (kCameraTableSize - 1);
            for (size_t probe = 0; probe < kCameraTableSize; ++probe)
            {
                CameraProfileSlot& slot =
                    g_CameraProfileSlots[(start + probe) & (kCameraTableSize - 1)];
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

        void CaptureCameraMetadata(CameraProfileSlot* slot, const void* camera)
        {
            if (!slot || !camera || !g_OgreGetEntityName)
                return;

            uint32_t expected = 0;
            if (!slot->metadataState.compare_exchange_strong(
                    expected, 1, std::memory_order_acq_rel,
                    std::memory_order_relaxed))
            {
                return;
            }

            __try
            {
                // Camera derives from MovableObject in the validated Ogre ABI,
                // so the existing name accessor safely identifies render targets.
                CopyEntityMetadataString(
                    slot->cameraName, g_OgreGetEntityName(camera));
                slot->metadataState.store(2, std::memory_order_release);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                slot->cameraName[0] = '\0';
                slot->metadataState.store(2, std::memory_order_release);
            }
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

        uintptr_t MixRenderContributorKey(uintptr_t hash, uintptr_t value)
        {
            // 32-bit FNV-1a is sufficient here because the immutable identity
            // fields are also retained for diagnostics and the table is small.
            hash ^= value;
            hash *= static_cast<uintptr_t>(16777619u);
            return hash;
        }

        RenderContributorSlot* FindOrClaimRenderContributorSlot(
            const void* renderable,
            const void* pass,
            const void* camera,
            const void* mesh)
        {
            if (!renderable || !pass)
                return nullptr;

            uintptr_t vtable = 0;
            __try
            {
                vtable = reinterpret_cast<uintptr_t>(
                    *reinterpret_cast<void* const*>(renderable));
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
            if (!vtable)
                return nullptr;

            uintptr_t key = static_cast<uintptr_t>(2166136261u);
            key = MixRenderContributorKey(key, vtable);
            key = MixRenderContributorKey(key, reinterpret_cast<uintptr_t>(pass));
            key = MixRenderContributorKey(key, reinterpret_cast<uintptr_t>(camera));
            key = MixRenderContributorKey(key, reinterpret_cast<uintptr_t>(mesh));
            if (!key)
                key = 1;

            const size_t start = key & (kRenderContributorTableSize - 1);
            for (size_t probe = 0; probe < kRenderContributorProbeCount; ++probe)
            {
                RenderContributorSlot& slot = g_RenderContributorSlots[
                    (start + probe) & (kRenderContributorTableSize - 1)];
                uintptr_t current = slot.key.load(std::memory_order_relaxed);
                if (current == key)
                    return &slot;
                if (current == 0 && slot.key.compare_exchange_strong(
                        current, key,
                        std::memory_order_relaxed,
                        std::memory_order_relaxed))
                {
                    slot.renderableVtable = vtable;
                    slot.pass = reinterpret_cast<uintptr_t>(pass);
                    slot.camera = reinterpret_cast<uintptr_t>(camera);
                    slot.mesh = reinterpret_cast<uintptr_t>(mesh);
                    return &slot;
                }
            }
            g_RenderContributorDrops.fetch_add(1, std::memory_order_relaxed);
            return nullptr;
        }

        void CopyRttiTypeName(
            std::array<char, kEntityMetadataLength>& destination,
            const void* renderable)
        {
            destination[0] = '\0';
            if (!renderable)
                return;

            struct CompleteObjectLocator32
            {
                uint32_t signature;
                uint32_t offset;
                uint32_t constructorDisplacement;
                const void* typeDescriptor;
                const void* classDescriptor;
            };

            __try
            {
                void* const* vtable = *reinterpret_cast<void* const* const*>(
                    renderable);
                const CompleteObjectLocator32* locator = vtable
                    ? reinterpret_cast<const CompleteObjectLocator32*>(vtable[-1])
                    : nullptr;
                const char* name = locator && locator->typeDescriptor
                    ? static_cast<const char*>(locator->typeDescriptor) + 8
                    : nullptr;
                if (!name)
                    return;
                size_t length = 0;
                while (length + 1 < destination.size() && name[length])
                    ++length;
                if (length)
                    std::memcpy(destination.data(), name, length);
                destination[length] = '\0';
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                destination[0] = '\0';
            }
        }

        void CaptureRenderContributorMetadata(
            RenderContributorSlot* slot,
            const void* renderable,
            const void* pass,
            const void* camera,
            const void* owner,
            const void* mesh)
        {
            if (!slot)
                return;
            uint32_t expected = 0;
            if (!slot->metadataState.compare_exchange_strong(
                    expected, 1, std::memory_order_acq_rel,
                    std::memory_order_relaxed))
            {
                return;
            }

            __try
            {
                CopyRttiTypeName(slot->typeName, renderable);
                if (owner && g_OgreGetEntityName)
                    CopyEntityMetadataString(slot->ownerName, g_OgreGetEntityName(owner));
                if (mesh && g_OgreGetResourceName)
                    CopyEntityMetadataString(slot->meshName, g_OgreGetResourceName(mesh));
                if (camera && g_OgreGetEntityName)
                    CopyEntityMetadataString(slot->cameraName, g_OgreGetEntityName(camera));

                if (pass && g_OgrePassGetParent && g_OgreTechniqueGetParent &&
                    g_OgreGetResourceName)
                {
                    const void* technique = g_OgrePassGetParent(pass);
                    const void* material = technique
                        ? g_OgreTechniqueGetParent(technique)
                        : nullptr;
                    if (material)
                    {
                        CopyEntityMetadataString(
                            slot->materialName,
                            g_OgreGetResourceName(material));
                    }
                }
                if (pass && g_OgrePassGetIndex)
                    slot->passIndex = g_OgrePassGetIndex(pass);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                // A malformed or transient diagnostic object must never alter
                // the stock render path. Keep whatever metadata was safe.
            }
            slot->metadataState.store(2, std::memory_order_release);
        }

        void ResolveSubEntityOwnerAndMesh(
            const void* renderable,
            const void*& owner,
            const void*& mesh)
        {
            owner = nullptr;
            mesh = nullptr;
            if (!renderable || !g_OgreSubEntityVtable ||
                !g_OgreSubEntityGetParent || !g_OgreEntityGetMesh)
            {
                return;
            }
            __try
            {
                const void* vtable = *reinterpret_cast<void* const*>(renderable);
                if (vtable != g_OgreSubEntityVtable)
                    return;
                owner = g_OgreSubEntityGetParent(renderable);
                const void* sharedMesh = owner ? g_OgreEntityGetMesh(owner) : nullptr;
                mesh = sharedMesh ? *reinterpret_cast<void* const*>(sharedMesh) : nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                owner = nullptr;
                mesh = nullptr;
            }
        }

        void RecordCurrentRenderOperation(const void* operation)
        {
            RenderContributorSlot* slot = t_CurrentRenderContributor;
            if (!slot)
                return;
            slot->ogreSubmissions.fetch_add(1, std::memory_order_relaxed);
            if (!operation)
                return;
            __try
            {
                const Ogre::RenderOperation* renderOperation =
                    static_cast<const Ogre::RenderOperation*>(operation);
                if (renderOperation->vertexData &&
                    renderOperation->vertexData->vertexCount <= kMaxSaneVertexCount)
                {
                    slot->operationVertices.fetch_add(
                        renderOperation->vertexData->vertexCount,
                        std::memory_order_relaxed);
                }
                if (renderOperation->useIndexes && renderOperation->indexData &&
                    renderOperation->indexData->indexCount <= kMaxSaneVertexCount * 6u)
                {
                    slot->operationIndices.fetch_add(
                        renderOperation->indexData->indexCount,
                        std::memory_order_relaxed);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                // Retail RenderOperation layout is only diagnostic metadata;
                // preserve submission attribution if count fields ever differ.
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

        uint32_t ReadVertexBufferStride(
            const Ogre::VertexData* vertexData,
            const Ogre::VertexElement* element)
        {
            // Keep the SharedPtr temporary outside the SEH-guarded caller;
            // MSVC cannot unwind C++ objects from a function containing __try.
            const auto& buffer = vertexData->vertexBufferBinding->getBuffer(
                g_OgreVertexElementGetSource(element));
            const void* rawBuffer = *reinterpret_cast<void* const*>(&buffer);
            return static_cast<uint32_t>(
                g_OgreVertexBufferGetVertexSize(rawBuffer));
        }

        const void* ReadVertexBufferPointer(
            const Ogre::VertexData* vertexData,
            const Ogre::VertexElement* element)
        {
            const auto& buffer = vertexData->vertexBufferBinding->getBuffer(
                g_OgreVertexElementGetSource(element));
            return *reinterpret_cast<void* const*>(&buffer);
        }

        bool RetrofitVertexSourceShadow(
            const Ogre::VertexData* vertexData,
            unsigned short source)
        {
            if (!vertexData || !vertexData->vertexBufferBinding ||
                !g_OgreHardwareBufferHasShadow ||
                !g_OgreHardwareBufferGetSizeInBytes ||
                !g_OgreHardwareBufferGetUsage ||
                !g_OgreVertexBufferGetVertexSize ||
                !g_OgreHardwareBufferManagerGetSingletonPtr ||
                !g_OgreHardwareBufferManagerCreateVertexBuffer ||
                !g_OgreHardwareBufferLock || !g_OgreHardwareBufferUnlock ||
                !g_OgreVertexBufferBindingSetBinding ||
                !g_OgreHardwareVertexBufferSharedPtrDestructor)
            {
                return false;
            }

            const Ogre::HardwareVertexBufferSharedPtr& currentSharedPtr =
                vertexData->vertexBufferBinding->getBuffer(source);
            void* currentBuffer =
                *reinterpret_cast<void* const*>(&currentSharedPtr);
            if (!currentBuffer || g_OgreHardwareBufferHasShadow(currentBuffer))
            {
                return true;
            }

            g_Dx11SkinSourceShadowQueries.fetch_add(1, std::memory_order_relaxed);
            std::lock_guard<std::mutex> guard(g_Dx11SkinSourceShadowMutex);

            // Re-read the binding after taking the lock. Multiple Entity instances
            // normally share this VertexData, so the first repair serves all of them.
            const Ogre::HardwareVertexBufferSharedPtr& oldSharedPtr =
                vertexData->vertexBufferBinding->getBuffer(source);
            void* oldBuffer = *reinterpret_cast<void* const*>(&oldSharedPtr);
            if (!oldBuffer || g_OgreHardwareBufferHasShadow(oldBuffer))
                return true;

            const size_t vertexSize = g_OgreVertexBufferGetVertexSize(oldBuffer);
            const size_t sizeBytes = g_OgreHardwareBufferGetSizeInBytes(oldBuffer);
            if (!vertexSize || !sizeBytes || sizeBytes % vertexSize != 0 ||
                sizeBytes / vertexSize > kMaxSaneVertexCount)
            {
                g_Dx11SkinSourceShadowFailureStage.store(
                    1, std::memory_order_relaxed);
                g_Dx11SkinSourceShadowFailures.fetch_add(1, std::memory_order_relaxed);
                g_Dx11SkinSourceShadowPolicyEnabled.store(
                    false, std::memory_order_release);
                return false;
            }

            void* manager = g_OgreHardwareBufferManagerGetSingletonPtr();
            if (!manager)
            {
                g_Dx11SkinSourceShadowFailureStage.store(
                    2, std::memory_order_relaxed);
                g_Dx11SkinSourceShadowFailures.fetch_add(1, std::memory_order_relaxed);
                g_Dx11SkinSourceShadowPolicyEnabled.store(
                    false, std::memory_order_release);
                return false;
            }

            bool oldLocked = false;
            bool replacementLocked = false;
            bool replacementConstructed = false;
            uint32_t failureStage = 3;
            struct SharedPtrStorage
            {
                void* object = nullptr;
                void* control = nullptr;
            } replacement;
            static_assert(
                sizeof(SharedPtrStorage) == sizeof(void*) * 2,
                "validated Ogre SharedPtr ABI uses two pointers");
            try
            {
                // Pay the D3D11 staging readback once, then preserve the exact
                // interleaved source bytes in a normal Ogre CPU-shadowed buffer.
                // Subsequent software skinning reads the shadow instead of forcing
                // CopyResource + Map synchronization every Entity every frame.
                std::vector<uint8_t> copy(sizeBytes);
                const void* sourceBytes = g_OgreHardwareBufferLock(
                    oldBuffer,
                    Ogre::HardwareBuffer::HBL_READ_ONLY,
                    Ogre::HardwareBuffer::HBU_DEFAULT);
                oldLocked = true;
                if (!sourceBytes)
                    throw std::bad_alloc();
                std::memcpy(copy.data(), sourceBytes, sizeBytes);
                g_OgreHardwareBufferUnlock(oldBuffer);
                oldLocked = false;

                failureStage = 4;
                g_OgreHardwareBufferManagerCreateVertexBuffer(
                    manager,
                    &replacement,
                    vertexSize,
                    sizeBytes / vertexSize,
                    g_OgreHardwareBufferGetUsage(oldBuffer),
                    true);
                replacementConstructed = true;
                if (!replacement.object)
                    throw std::bad_alloc();

                failureStage = 5;
                void* destinationBytes = g_OgreHardwareBufferLock(
                    replacement.object,
                    Ogre::HardwareBuffer::HBL_DISCARD,
                    Ogre::HardwareBuffer::HBU_DEFAULT);
                replacementLocked = true;
                if (!destinationBytes)
                    throw std::bad_alloc();
                std::memcpy(destinationBytes, copy.data(), sizeBytes);
                g_OgreHardwareBufferUnlock(replacement.object);
                replacementLocked = false;

                failureStage = 6;
                g_OgreVertexBufferBindingSetBinding(
                    vertexData->vertexBufferBinding, source, &replacement);
                g_OgreHardwareVertexBufferSharedPtrDestructor(&replacement);
                replacementConstructed = false;
                g_Dx11SkinSourceShadowRepairs.fetch_add(1, std::memory_order_relaxed);
                g_Dx11SkinSourceShadowRepairBytes.fetch_add(
                    sizeBytes, std::memory_order_relaxed);
                return true;
            }
            catch (...)
            {
                g_Dx11SkinSourceShadowFailureStage.store(
                    failureStage, std::memory_order_relaxed);
                if (replacementLocked && replacement.object)
                {
                    try { g_OgreHardwareBufferUnlock(replacement.object); }
                    catch (...) {}
                }
                if (oldLocked)
                {
                    try { g_OgreHardwareBufferUnlock(oldBuffer); }
                    catch (...) {}
                }
                if (replacementConstructed)
                {
                    try
                    {
                        g_OgreHardwareVertexBufferSharedPtrDestructor(
                            &replacement);
                    }
                    catch (...) {}
                }
                g_Dx11SkinSourceShadowFailures.fetch_add(1, std::memory_order_relaxed);
                // A failed retrofit must remain stock behavior, not become a
                // repeated allocation/readback attempt on this hot path.
                g_Dx11SkinSourceShadowPolicyEnabled.store(
                    false, std::memory_order_release);
                return false;
            }
        }

        void EnsureDx11SoftwareSkinSourceShadows(
            const Ogre::VertexData* vertexData)
        {
            if (!g_Dx11SkinSourceShadowPolicyEnabled.load(
                    std::memory_order_relaxed) ||
                !vertexData || !vertexData->vertexDeclaration)
            {
                return;
            }
            if (!g_OgreVertexElementGetSource)
                return;

            const Ogre::VertexElement* position =
                vertexData->vertexDeclaration->findElementBySemantic(
                    Ogre::VES_POSITION);
            const Ogre::VertexElement* normal =
                vertexData->vertexDeclaration->findElementBySemantic(
                    Ogre::VES_NORMAL);
            if (position)
            {
                const unsigned short positionSource =
                    g_OgreVertexElementGetSource(position);
                RetrofitVertexSourceShadow(vertexData, positionSource);
                if (normal)
                {
                    const unsigned short normalSource =
                        g_OgreVertexElementGetSource(normal);
                    if (normalSource != positionSource)
                        RetrofitVertexSourceShadow(vertexData, normalSource);
                }
            }
            else if (normal)
            {
                RetrofitVertexSourceShadow(
                    vertexData, g_OgreVertexElementGetSource(normal));
            }
        }

        void CaptureSourceLayout(
            SourceProfileSlot* slot,
            const Ogre::VertexData* vertexData)
        {
            if (!slot || !vertexData || !vertexData->vertexDeclaration ||
                !vertexData->vertexBufferBinding ||
                !g_OgreVertexElementGetSource ||
                !g_OgreVertexElementGetType ||
                !g_OgreVertexElementGetTypeCount ||
                !g_OgreVertexBufferGetVertexSize ||
                !g_OgreHardwareBufferHasShadow ||
                !g_OgreHardwareBufferIsSystemMemory)
            {
                return;
            }

            uint32_t expected = 0;
            if (!slot->metadataState.compare_exchange_strong(
                    expected, 1, std::memory_order_acq_rel,
                    std::memory_order_relaxed))
            {
                return;
            }

            __try
            {
                const Ogre::VertexElement* position =
                    vertexData->vertexDeclaration->findElementBySemantic(
                        Ogre::VES_POSITION);
                const Ogre::VertexElement* normal =
                    vertexData->vertexDeclaration->findElementBySemantic(
                        Ogre::VES_NORMAL);
                const Ogre::VertexElement* weights =
                    vertexData->vertexDeclaration->findElementBySemantic(
                        Ogre::VES_BLEND_WEIGHTS);
                const Ogre::VertexElement* indices =
                    vertexData->vertexDeclaration->findElementBySemantic(
                        Ogre::VES_BLEND_INDICES);
                if (position)
                {
                    slot->positionStride =
                        ReadVertexBufferStride(vertexData, position);
                    const void* positionBuffer =
                        ReadVertexBufferPointer(vertexData, position);
                    slot->positionShadowed =
                        g_OgreHardwareBufferHasShadow(positionBuffer);
                    slot->positionSystemMemory =
                        g_OgreHardwareBufferIsSystemMemory(positionBuffer);
                }
                if (normal)
                {
                    slot->normalStride =
                        ReadVertexBufferStride(vertexData, normal);
                }
                if (weights)
                {
                    slot->weightStride =
                        ReadVertexBufferStride(vertexData, weights);
                    slot->weightShadowed = g_OgreHardwareBufferHasShadow(
                        ReadVertexBufferPointer(vertexData, weights));
                    slot->weightsPerVertex = static_cast<uint32_t>(
                        g_OgreVertexElementGetTypeCount(
                            g_OgreVertexElementGetType(weights)));
                }
                if (indices)
                {
                    slot->indexStride =
                        ReadVertexBufferStride(vertexData, indices);
                }
                slot->metadataState.store(2, std::memory_order_release);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                slot->metadataState.store(2, std::memory_order_release);
            }
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

