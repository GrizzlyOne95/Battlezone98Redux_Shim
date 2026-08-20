        void AppendCsvRow(
            ULONGLONG tickMs,
            double fps,
            double frameMeanMs,
            double frameP50Ms,
            double frameP95Ms,
            double frameP99Ms,
            double frameMaxMs,
            uint64_t animationCalls,
            uint64_t renderDrivenCalls,
            uint64_t externalCalls,
            double animationMsPerFrame,
            double nonBlendMsPerFrame,
            uint64_t blendCalls,
            uint64_t blendVertices,
            double blendMsPerFrame,
            uint64_t duplicateAnimation,
            uint64_t duplicateSkin,
            uint64_t orphanBlendCalls,
            double matrixAverage,
            uint64_t matrixMax,
            uint64_t mapCalls,
            uint64_t mapDuringAnimation,
            uint64_t mapDuringBlend,
            double mapMsPerFrame,
            uint64_t updateCalls,
            uint64_t updateDuringAnimation,
            uint64_t drawCalls,
            uint64_t drawIndexedCalls,
            uint64_t drawInstancedCalls,
            uint64_t drawIndexedInstancedCalls)
        {
            const std::string iniPath = GetOpenShimIniPath();
            const size_t slash = iniPath.find_last_of("\\/");
            const std::string csvPath =
                (slash == std::string::npos)
                    ? "openshim_ogre_profile.csv"
                    : iniPath.substr(0, slash + 1) + "openshim_ogre_profile.csv";

            FILE* file = nullptr;
            if (fopen_s(&file, csvPath.c_str(), "a+") != 0 || !file)
                return;

            fseek(file, 0, SEEK_END);
            const long size = ftell(file);
            if (size == 0)
            {
                std::fputs(
                    "tick_ms,fps,frame_mean_ms,frame_p50_ms,frame_p95_ms,frame_p99_ms,frame_max_ms,"
                    "anim_calls,anim_render_driven,anim_external,anim_ms_per_frame,nonblend_ms_per_frame,"
                    "skin_calls,skin_vertices,skin_ms_per_frame,dup_anim_same_frame,dup_skin_same_frame,"
                    "orphan_skin_calls,matrix_avg,matrix_max,map_calls,map_during_anim,map_during_blend,"
                    "map_ms_per_frame,update_subresource_calls,update_during_anim,draw_calls,draw_indexed_calls,"
                    "draw_instanced_calls,draw_indexed_instanced_calls\n",
                    file);
            }

            std::fprintf(
                file,
                "%llu,%.3f,%.4f,%.4f,%.4f,%.4f,%.4f,%llu,%llu,%llu,%.4f,%.4f,"
                "%llu,%llu,%.4f,%llu,%llu,%llu,%.3f,%llu,%llu,%llu,%llu,%.4f,"
                "%llu,%llu,%llu,%llu,%llu,%llu\n",
                static_cast<unsigned long long>(tickMs),
                fps, frameMeanMs, frameP50Ms, frameP95Ms, frameP99Ms, frameMaxMs,
                static_cast<unsigned long long>(animationCalls),
                static_cast<unsigned long long>(renderDrivenCalls),
                static_cast<unsigned long long>(externalCalls),
                animationMsPerFrame, nonBlendMsPerFrame,
                static_cast<unsigned long long>(blendCalls),
                static_cast<unsigned long long>(blendVertices),
                blendMsPerFrame,
                static_cast<unsigned long long>(duplicateAnimation),
                static_cast<unsigned long long>(duplicateSkin),
                static_cast<unsigned long long>(orphanBlendCalls),
                matrixAverage,
                static_cast<unsigned long long>(matrixMax),
                static_cast<unsigned long long>(mapCalls),
                static_cast<unsigned long long>(mapDuringAnimation),
                static_cast<unsigned long long>(mapDuringBlend),
                mapMsPerFrame,
                static_cast<unsigned long long>(updateCalls),
                static_cast<unsigned long long>(updateDuringAnimation),
                static_cast<unsigned long long>(drawCalls),
                static_cast<unsigned long long>(drawIndexedCalls),
                static_cast<unsigned long long>(drawInstancedCalls),
                static_cast<unsigned long long>(drawIndexedInstancedCalls));
            std::fclose(file);
        }

        void ReportTopContributors(double frameDivisor)
        {
            std::vector<EntityTopSample> entities;
            entities.reserve(64);
            for (size_t i = 0; i < g_EntityProfileSlots.size(); ++i)
            {
                EntityProfileSlot& slot = g_EntityProfileSlots[i];
                const uintptr_t key = slot.key.load(std::memory_order_relaxed);
                if (!key)
                    continue;
                EntityTopSample sample{};
                sample.key = key;
                sample.animationCalls = slot.animationCalls.exchange(0, std::memory_order_acq_rel);
                sample.animationTicks = slot.animationTicks.exchange(0, std::memory_order_acq_rel);
                sample.skinCalls = slot.skinCalls.exchange(0, std::memory_order_acq_rel);
                sample.skinVertices = slot.skinVertices.exchange(0, std::memory_order_acq_rel);
                sample.skinTicks = slot.skinTicks.exchange(0, std::memory_order_acq_rel);
                if (sample.animationCalls || sample.skinCalls)
                    entities.push_back(sample);
            }
            std::sort(
                entities.begin(), entities.end(),
                [](const EntityTopSample& a, const EntityTopSample& b)
                {
                    return a.skinTicks != b.skinTicks
                        ? a.skinTicks > b.skinTicks
                        : a.animationTicks > b.animationTicks;
                });
            for (size_t i = 0; i < entities.size() && i < kTopContributorCount; ++i)
            {
                const EntityTopSample& sample = entities[i];
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile][EntityTop] rank=%u entity=0x%p animCalls/f=%.2f animCPU=%.3fms/f skinCalls/f=%.2f skinVerts/f=%.0f swCPU=%.3fms/f",
                    static_cast<unsigned>(i + 1),
                    reinterpret_cast<void*>(sample.key),
                    static_cast<double>(sample.animationCalls) / frameDivisor,
                    TicksToMs(sample.animationTicks) / frameDivisor,
                    static_cast<double>(sample.skinCalls) / frameDivisor,
                    static_cast<double>(sample.skinVertices) / frameDivisor,
                    TicksToMs(sample.skinTicks) / frameDivisor);
            }

            std::vector<SourceTopSample> sources;
            sources.reserve(64);
            for (size_t i = 0; i < g_SourceProfileSlots.size(); ++i)
            {
                SourceProfileSlot& slot = g_SourceProfileSlots[i];
                const uintptr_t key = slot.key.load(std::memory_order_relaxed);
                if (!key)
                    continue;
                SourceTopSample sample{};
                sample.key = key;
                sample.calls = slot.calls.exchange(0, std::memory_order_acq_rel);
                sample.vertices = slot.vertices.exchange(0, std::memory_order_acq_rel);
                sample.ticks = slot.ticks.exchange(0, std::memory_order_acq_rel);
                sample.sourceVertices = slot.sourceVertices.load(std::memory_order_relaxed);
                if (sample.calls)
                    sources.push_back(sample);
            }
            std::sort(
                sources.begin(), sources.end(),
                [](const SourceTopSample& a, const SourceTopSample& b)
                {
                    return a.ticks > b.ticks;
                });
            for (size_t i = 0; i < sources.size() && i < kTopContributorCount; ++i)
            {
                const SourceTopSample& sample = sources[i];
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile][SkinTop] rank=%u sourceVD=0x%p sourceVerts=%llu calls/f=%.2f verts/f=%.0f swCPU=%.3fms/f",
                    static_cast<unsigned>(i + 1),
                    reinterpret_cast<void*>(sample.key),
                    static_cast<unsigned long long>(sample.sourceVertices),
                    static_cast<double>(sample.calls) / frameDivisor,
                    static_cast<double>(sample.vertices) / frameDivisor,
                    TicksToMs(sample.ticks) / frameDivisor);
            }
        }

