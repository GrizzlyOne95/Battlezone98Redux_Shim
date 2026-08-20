        size_t PatchDirectCallsInModule(
            HMODULE module,
            void* target,
            void* replacement,
            const char* label)
        {
            if (!module || !target || !replacement)
                return 0;

            auto* base = reinterpret_cast<uint8_t*>(module);
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return 0;
            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return 0;

            const size_t imageSize = nt->OptionalHeader.SizeOfImage;
            auto* section = IMAGE_FIRST_SECTION(nt);
            size_t patched = 0;

            std::lock_guard<std::mutex> lock(g_PatchMutex);
            for (WORD sectionIndex = 0; sectionIndex < nt->FileHeader.NumberOfSections; ++sectionIndex, ++section)
            {
                if ((section->Characteristics & IMAGE_SCN_MEM_EXECUTE) == 0)
                    continue;

                size_t sectionSize = static_cast<size_t>(section->Misc.VirtualSize);
                if (sectionSize == 0)
                    sectionSize = static_cast<size_t>(section->SizeOfRawData);
                if (section->VirtualAddress >= imageSize)
                    continue;
                sectionSize = (std::min)(
                    sectionSize,
                    imageSize - static_cast<size_t>(section->VirtualAddress));
                if (sectionSize < 5)
                    continue;

                uint8_t* code = base + section->VirtualAddress;
                for (size_t i = 0; i + 5 <= sectionSize; ++i)
                {
                    if (code[i] != 0xE8)
                        continue;

                    int32_t relative = 0;
                    std::memcpy(&relative, code + i + 1, sizeof(relative));
                    uint8_t* destination = code + i + 5 + relative;
                    if (destination != target)
                        continue;

                    const intptr_t delta =
                        reinterpret_cast<uint8_t*>(replacement) - (code + i + 5);
                    const int32_t newRelative = static_cast<int32_t>(delta);
                    if (!WriteRel32(code + i + 1, newRelative))
                        continue;

                    g_Rel32Patches.push_back({ code + i + 1, relative });
                    ++patched;
                    i += 4;
                }
            }

            LogShimA(
                patched ? LogLevel::Info : LogLevel::Warn,
                kComponent,
                "[OgreProfile] %s direct-call observers installed=%u module=0x%p",
                label,
                static_cast<unsigned>(patched),
                module);
            return patched;
        }

        size_t PatchIatEntriesByTarget(
            HMODULE module,
            void* target,
            void* replacement,
            const char* label)
        {
            if (!module || !target || !replacement)
                return 0;

            auto* base = reinterpret_cast<uint8_t*>(module);
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return 0;
            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return 0;

            const IMAGE_DATA_DIRECTORY& imports =
                nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
            if (!imports.VirtualAddress)
                return 0;

            size_t patched = 0;
            auto* descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + imports.VirtualAddress);
            std::lock_guard<std::mutex> lock(g_PatchMutex);
            for (; descriptor->Name; ++descriptor)
            {
                auto* thunk = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->FirstThunk);
                for (; thunk->u1.Function; ++thunk)
                {
                    void** slot = reinterpret_cast<void**>(&thunk->u1.Function);
                    if (*slot != target)
                        continue;
                    if (!WritePointer(slot, replacement))
                        continue;
                    g_PointerPatches.push_back({ slot, target });
                    ++patched;
                }
            }

            if (patched)
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile] %s IAT observers installed=%u module=0x%p",
                    label,
                    static_cast<unsigned>(patched),
                    module);
            }
            return patched;
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

