        struct SuspendedThreadSet
        {
            std::array<HANDLE, kMaxSuspendedThreads> handles{};
            size_t count = 0;
            bool ready = false;
            DWORD failureError = ERROR_SUCCESS;
            DWORD blockingThreadId = 0;
            uintptr_t blockingInstruction = 0;

            SuspendedThreadSet(const uint8_t* patchBegin, size_t patchLength)
            {
                const DWORD processId = GetCurrentProcessId();
                const DWORD currentThreadId = GetCurrentThreadId();
                HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
                if (snapshot == INVALID_HANDLE_VALUE)
                {
                    failureError = GetLastError();
                    return;
                }

                THREADENTRY32 entry{};
                entry.dwSize = sizeof(entry);
                bool success = true;
                BOOL hasEntry = Thread32First(snapshot, &entry);
                if (!hasEntry)
                    success = false;
                while (success && hasEntry)
                {
                    if (entry.th32OwnerProcessID == processId &&
                        entry.th32ThreadID != currentThreadId)
                    {
                        if (count == handles.size())
                        {
                            failureError = ERROR_INSUFFICIENT_BUFFER;
                            success = false;
                            break;
                        }

                        HANDLE thread = OpenThread(
                            THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION,
                            FALSE,
                            entry.th32ThreadID);
                        if (!thread)
                        {
                            if (GetLastError() != ERROR_INVALID_PARAMETER)
                            {
                                failureError = GetLastError();
                                success = false;
                            }
                        }
                        else if (SuspendThread(thread) == static_cast<DWORD>(-1))
                        {
                            failureError = GetLastError();
                            CloseHandle(thread);
                            success = false;
                        }
                        else
                        {
                            CONTEXT context{};
                            context.ContextFlags = CONTEXT_CONTROL;
                            if (!GetThreadContext(thread, &context))
                            {
                                failureError = GetLastError();
                                ResumeThread(thread);
                                CloseHandle(thread);
                                success = false;
                            }
                            else
                            {
                                const uintptr_t instruction = static_cast<uintptr_t>(context.Eip);
                                const uintptr_t begin = reinterpret_cast<uintptr_t>(patchBegin);
                                if (instruction >= begin && instruction < begin + patchLength)
                                {
                                    failureError = ERROR_BUSY;
                                    blockingThreadId = entry.th32ThreadID;
                                    blockingInstruction = instruction;
                                    ResumeThread(thread);
                                    CloseHandle(thread);
                                    success = false;
                                }
                                else
                                {
                                    handles[count++] = thread;
                                }
                            }
                        }
                    }

                    if (success)
                        hasEntry = Thread32Next(snapshot, &entry);
                }
                CloseHandle(snapshot);

                if (!success)
                {
                    Release();
                    return;
                }
                ready = true;
            }

            ~SuspendedThreadSet()
            {
                Release();
            }

            void Release()
            {
                while (count != 0)
                {
                    HANDLE thread = handles[--count];
                    ResumeThread(thread);
                    CloseHandle(thread);
                }
                ready = false;
            }
        };

        bool InstallEntryDetour32(
            EntryDetour32& detour,
            HMODULE ownerModule,
            void* target,
            void* hook,
            const uint8_t* expectedBytes,
            size_t patchLength,
            const char* label)
        {
            if (!target || !hook || !expectedBytes ||
                patchLength > detour.original.size() ||
                !IsExecutableModuleAddress(ownerModule, target))
            {
                return false;
            }

            std::lock_guard<std::mutex> lock(g_PatchMutex);
            if (detour.trampoline)
                return detour.target == target && detour.hook == hook;
            if (!OgreProfilerAlgorithms::ValidateDetourPrologue(
                    static_cast<const uint8_t*>(target), expectedBytes,
                    patchLength, detour.original.size()))
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile] %s implementation prologue is unsupported address=0x%p length=%u",
                    label,
                    target,
                    static_cast<unsigned>(patchLength));
                return false;
            }

            auto* trampoline = static_cast<uint8_t*>(VirtualAlloc(
                nullptr,
                patchLength + 5,
                MEM_COMMIT | MEM_RESERVE,
                PAGE_READWRITE));
            if (!trampoline)
                return false;

            std::memcpy(trampoline, target, patchLength);
            trampoline[patchLength] = 0xE9;
            const intptr_t resumeDelta =
                (static_cast<uint8_t*>(target) + patchLength) -
                (trampoline + patchLength + 5);
            if (resumeDelta < (std::numeric_limits<int32_t>::min)() ||
                resumeDelta > (std::numeric_limits<int32_t>::max)())
            {
                VirtualFree(trampoline, 0, MEM_RELEASE);
                return false;
            }
            const int32_t resumeRelative = static_cast<int32_t>(resumeDelta);
            std::memcpy(trampoline + patchLength + 1, &resumeRelative, sizeof(resumeRelative));
            DWORD ignored = 0;
            if (!VirtualProtect(trampoline, patchLength + 5, PAGE_EXECUTE_READ, &ignored))
            {
                VirtualFree(trampoline, 0, MEM_RELEASE);
                return false;
            }
            FlushInstructionCache(GetCurrentProcess(), trampoline, patchLength + 5);

            std::array<uint8_t, kEntryDetourMaxPatchLen> replacement{};
            replacement.fill(0x90);
            replacement[0] = 0xE9;
            const intptr_t hookDelta = static_cast<uint8_t*>(hook) -
                (static_cast<uint8_t*>(target) + 5);
            if (hookDelta < (std::numeric_limits<int32_t>::min)() ||
                hookDelta > (std::numeric_limits<int32_t>::max)())
            {
                VirtualFree(trampoline, 0, MEM_RELEASE);
                return false;
            }
            const int32_t hookRelative = static_cast<int32_t>(hookDelta);
            std::memcpy(replacement.data() + 1, &hookRelative, sizeof(hookRelative));

            SuspendedThreadSet suspended(static_cast<uint8_t*>(target), patchLength);
            if (!suspended.ready || std::memcmp(target, expectedBytes, patchLength) != 0)
            {
                g_EntryInstallRetryRequested = !suspended.ready &&
                    std::memcmp(target, expectedBytes, patchLength) == 0;
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile] deferred %s entry observer target=0x%p suspendReady=%s error=%lu blockingThread=%lu blockingEip=0x%p bytesStillMatch=%s",
                    label,
                    target,
                    suspended.ready ? "yes" : "no",
                    suspended.failureError,
                    suspended.blockingThreadId,
                    reinterpret_cast<void*>(suspended.blockingInstruction),
                    std::memcmp(target, expectedBytes, patchLength) == 0 ? "yes" : "no");
                VirtualFree(trampoline, 0, MEM_RELEASE);
                return false;
            }

            DWORD oldProtection = 0;
            if (!VirtualProtect(target, patchLength, PAGE_EXECUTE_READWRITE, &oldProtection))
            {
                VirtualFree(trampoline, 0, MEM_RELEASE);
                return false;
            }
            std::memcpy(detour.original.data(), target, patchLength);
            std::memcpy(target, replacement.data(), patchLength);
            FlushInstructionCache(GetCurrentProcess(), target, patchLength);
            DWORD restoredProtection = 0;
            VirtualProtect(target, patchLength, oldProtection, &restoredProtection);

            detour.target = static_cast<uint8_t*>(target);
            detour.hook = hook;
            detour.trampoline = trampoline;
            detour.patchLen = patchLength;
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] installed %s entry observer implementation=0x%p trampoline=0x%p prologueBytes=%u",
                label,
                target,
                trampoline,
                static_cast<unsigned>(patchLength));
            return true;
        }

        size_t PatchEntityVtables(void* target, void* replacement)
        {
            const auto vtables = FindExportsContaining("??_7Entity@Ogre@@");
            size_t patched = 0;
            std::lock_guard<std::mutex> lock(g_PatchMutex);

            for (const auto& match : vtables)
            {
                auto** vtable = reinterpret_cast<void**>(match.address);
                for (size_t i = 0; i < kMaxVtableEntriesToProbe; ++i)
                {
                    void** slot = &vtable[i];
                    if (!OgreRuntime::ContainsAddress(slot))
                        break;

                    void* entry = *slot;
                    if (entry != target)
                        continue;
                    if (!WritePointer(slot, replacement))
                        continue;

                    g_PointerPatches.push_back({ slot, target });
                    ++patched;
                    LogShimA(
                        LogLevel::Info,
                        kComponent,
                        "[OgreProfile] Entity vtable render-queue observer export=%s slot=%u",
                        match.name.c_str(),
                        static_cast<unsigned>(i));
                }
            }
            return patched;
        }

        bool PatchIatFunctionByName(
            HMODULE module,
            const char* importedDll,
            const char* functionName,
            void* replacement,
            void** original)
        {
            if (!module || !importedDll || !functionName || !replacement || !original)
                return false;

            auto* base = reinterpret_cast<uint8_t*>(module);
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return false;
            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return false;

            const IMAGE_DATA_DIRECTORY& imports =
                nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
            if (!imports.VirtualAddress)
                return false;

            auto* descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + imports.VirtualAddress);
            for (; descriptor->Name; ++descriptor)
            {
                const char* dllName = reinterpret_cast<const char*>(base + descriptor->Name);
                if (_stricmp(dllName, importedDll) != 0)
                    continue;
                if (!descriptor->OriginalFirstThunk)
                    return false;

                auto* names = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->OriginalFirstThunk);
                auto* thunks = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->FirstThunk);
                for (; names->u1.AddressOfData && thunks->u1.Function; ++names, ++thunks)
                {
                    if (IMAGE_SNAP_BY_ORDINAL(names->u1.Ordinal))
                        continue;
                    auto* byName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(base + names->u1.AddressOfData);
                    if (std::strcmp(reinterpret_cast<const char*>(byName->Name), functionName) != 0)
                        continue;

                    void** slot = reinterpret_cast<void**>(&thunks->u1.Function);
                    std::lock_guard<std::mutex> lock(g_PatchMutex);
                    if (*slot == replacement)
                        return true;
                    if (*original == nullptr)
                        *original = *slot;
                    if (!WritePointer(slot, replacement))
                        return false;
                    g_PointerPatches.push_back({ slot, *original });
                    return true;
                }
            }
            return false;
        }

        template <typename T>
        bool PatchComVtableEntry(
            void* object,
            size_t index,
            T hook,
            T& original,
            const char* label)
        {
            if (!object)
                return false;

            std::lock_guard<std::mutex> lock(g_PatchMutex);
            void*** objectVtable = reinterpret_cast<void***>(object);
            if (!objectVtable || !*objectVtable)
                return false;
            void** vtable = *objectVtable;
            void* current = vtable[index];
            if (current == reinterpret_cast<void*>(hook))
                return true;

            if (original && current != reinterpret_cast<void*>(original))
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile] %s already wrapped by another observer; leaving it untouched",
                    label);
                return false;
            }

            if (!original)
                original = reinterpret_cast<T>(current);
            if (!WritePointer(&vtable[index], reinterpret_cast<void*>(hook)))
                return false;
            g_PointerPatches.push_back({ &vtable[index], reinterpret_cast<void*>(original) });

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] installed %s observer vtable[%u]",
                label,
                static_cast<unsigned>(index));
            return true;
        }

        struct CurrentEntityScope
        {
            void* previousEntity;
            uint32_t previousBlendCalls;
            uint64_t previousBlendVertices;

            explicit CurrentEntityScope(void* current)
                : previousEntity(t_CurrentAnimationEntity),
                  previousBlendCalls(t_CurrentAnimationBlendCalls),
                  previousBlendVertices(t_CurrentAnimationBlendVertices)
            {
                t_CurrentAnimationEntity = current;
                t_CurrentAnimationBlendCalls = 0;
                t_CurrentAnimationBlendVertices = 0;
            }

            ~CurrentEntityScope()
            {
                t_CurrentAnimationEntity = previousEntity;
                t_CurrentAnimationBlendCalls = previousBlendCalls;
                t_CurrentAnimationBlendVertices = previousBlendVertices;
            }
        };

        struct RenderQueueScope
        {
            void* previous;
            explicit RenderQueueScope(void* current)
                : previous(t_RenderQueueEntity)
            {
                t_RenderQueueEntity = current;
            }
            ~RenderQueueScope()
            {
                t_RenderQueueEntity = previous;
            }
        };

        struct SoftwareBlendScope
        {
            SoftwareBlendScope() { ++t_SoftwareBlendDepth; }
            ~SoftwareBlendScope() { --t_SoftwareBlendDepth; }
        };

