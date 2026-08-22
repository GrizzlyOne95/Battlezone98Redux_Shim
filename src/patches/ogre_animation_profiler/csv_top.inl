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
                std::fprintf(file, "%s\n", OgreProfilerAlgorithms::kCsvHeader);
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

        void ReportDynamicGeometryContributors(double frameDivisor)
        {
            std::vector<DynamicGeometryTopSample> samples;
            samples.reserve(kDynamicGeometryTableSize);
            for (DynamicGeometryProfileSlot& slot : g_DynamicGeometryProfileSlots)
            {
                const uintptr_t key = slot.key.load(std::memory_order_relaxed);
                if (!key)
                    continue;
                DynamicGeometryTopSample sample{};
                sample.key = key;
                sample.prepareCalls = slot.prepareCalls.exchange(
                    0, std::memory_order_acq_rel);
                sample.rebuilds = slot.rebuilds.exchange(
                    0, std::memory_order_acq_rel);
                sample.prepareTicks = slot.prepareTicks.exchange(
                    0, std::memory_order_acq_rel);
                sample.queueCalls = slot.queueCalls.exchange(
                    0, std::memory_order_acq_rel);
                sample.batches = slot.batches.exchange(
                    0, std::memory_order_acq_rel);
                sample.batchMax = slot.batchMax.exchange(
                    0, std::memory_order_acq_rel);
                if (sample.prepareCalls || sample.queueCalls)
                    samples.push_back(sample);
            }
            std::sort(
                samples.begin(), samples.end(),
                [](const DynamicGeometryTopSample& a,
                   const DynamicGeometryTopSample& b)
                {
                    return a.batches != b.batches
                        ? a.batches > b.batches
                        : a.prepareTicks > b.prepareTicks;
                });
            for (size_t i = 0; i < samples.size(); ++i)
            {
                const DynamicGeometryTopSample& sample = samples[i];
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile][DynamicGeometryTop] rank=%u object=0x%p prepare=%.2f/f rebuilds=%.2f/f queue=%.2f/f batches=%.1f/call batchesMax=%llu cpu=%.3fms/f",
                    static_cast<unsigned>(i + 1),
                    reinterpret_cast<void*>(sample.key),
                    static_cast<double>(sample.prepareCalls) / frameDivisor,
                    static_cast<double>(sample.rebuilds) / frameDivisor,
                    static_cast<double>(sample.queueCalls) / frameDivisor,
                    sample.queueCalls
                        ? static_cast<double>(sample.batches) / sample.queueCalls
                        : 0.0,
                    static_cast<unsigned long long>(sample.batchMax),
                    TicksToMs(sample.prepareTicks) / frameDivisor);
            }

            std::vector<DynamicMaterialTopSample> materials;
            materials.reserve(kDynamicMaterialTableSize);
            for (DynamicMaterialProfileSlot& slot : g_DynamicMaterialProfileSlots)
            {
                const uintptr_t key = slot.key.load(std::memory_order_relaxed);
                if (!key)
                    continue;
                DynamicMaterialTopSample sample{};
                sample.key = key;
                sample.batches = slot.batches.exchange(
                    0, std::memory_order_acq_rel);
                sample.blendedBatches = slot.blendedBatches.exchange(
                    0, std::memory_order_acq_rel);
                sample.metadataReady =
                    slot.metadataState.load(std::memory_order_acquire) == 2;
                if (sample.metadataReady)
                    sample.materialName = slot.materialName;
                if (sample.batches)
                    materials.push_back(sample);
            }
            std::sort(
                materials.begin(), materials.end(),
                [](const DynamicMaterialTopSample& a,
                   const DynamicMaterialTopSample& b)
                {
                    return a.batches != b.batches
                        ? a.batches > b.batches
                        : a.blendedBatches > b.blendedBatches;
                });
            const size_t materialCount = std::min(
                materials.size(), kTopContributorCount);
            for (size_t i = 0; i < materialCount; ++i)
            {
                const DynamicMaterialTopSample& sample = materials[i];
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile][DynamicMaterialTop] rank=%u material=0x%p name=%s batches=%.1f/f blended=%.1f/f",
                    static_cast<unsigned>(i + 1),
                    reinterpret_cast<void*>(sample.key),
                    sample.metadataReady && sample.materialName[0]
                        ? sample.materialName.data() : "<unknown>",
                    static_cast<double>(sample.batches) / frameDivisor,
                    static_cast<double>(sample.blendedBatches) / frameDivisor);
            }
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
                sample.renderQueueCalls = slot.renderQueueCalls.exchange(0, std::memory_order_acq_rel);
                sample.metadataReady =
                    slot.metadataState.load(std::memory_order_acquire) == 2;
                if (sample.metadataReady)
                {
                    sample.entityName = slot.entityName;
                    sample.meshName = slot.meshName;
                    sample.castShadows = slot.castShadows;
                }
                if (sample.animationCalls || sample.skinCalls || sample.renderQueueCalls)
                    entities.push_back(sample);
            }

            std::vector<EntityTopSample> chunkEntities;
            uint64_t chunkRenderQueueCalls = 0;
            uint64_t chunkAnimationCalls = 0;
            uint64_t chunkSkinCalls = 0;
            size_t shadowCastingChunkEntities = 0;
            for (const EntityTopSample& sample : entities)
            {
                if (!IsChunkNamedEntity(sample))
                    continue;
                chunkEntities.push_back(sample);
                chunkRenderQueueCalls += sample.renderQueueCalls;
                chunkAnimationCalls += sample.animationCalls;
                chunkSkinCalls += sample.skinCalls;
                if (sample.castShadows)
                    ++shadowCastingChunkEntities;
            }
            std::sort(
                chunkEntities.begin(), chunkEntities.end(),
                [](const EntityTopSample& a, const EntityTopSample& b)
                {
                    if (a.renderQueueCalls != b.renderQueueCalls)
                        return a.renderQueueCalls > b.renderQueueCalls;
                    return a.skinTicks > b.skinTicks;
                });
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile][ChunkEntitySummary] namedEntities=%u shadows=%u renderQueue=%.2f/f anim=%.2f/f skin=%.2f/f",
                static_cast<unsigned>(chunkEntities.size()),
                static_cast<unsigned>(shadowCastingChunkEntities),
                static_cast<double>(chunkRenderQueueCalls) / frameDivisor,
                static_cast<double>(chunkAnimationCalls) / frameDivisor,
                static_cast<double>(chunkSkinCalls) / frameDivisor);
            for (size_t i = 0; i < chunkEntities.size() && i < 16; ++i)
            {
                const EntityTopSample& sample = chunkEntities[i];
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile][ChunkEntityTop] rank=%u entity=0x%p name=%s mesh=%s shadows=%s renderQueue/f=%.2f animCalls/f=%.2f skinCalls/f=%.2f swCPU=%.3fms/f",
                    static_cast<unsigned>(i + 1),
                    reinterpret_cast<void*>(sample.key),
                    sample.entityName[0] ? sample.entityName.data() : "<unavailable>",
                    sample.meshName[0] ? sample.meshName.data() : "<unavailable>",
                    sample.castShadows ? "yes" : "no",
                    static_cast<double>(sample.renderQueueCalls) / frameDivisor,
                    static_cast<double>(sample.animationCalls) / frameDivisor,
                    static_cast<double>(sample.skinCalls) / frameDivisor,
                    TicksToMs(sample.skinTicks) / frameDivisor);
            }

            std::sort(
                entities.begin(), entities.end(),
                [](const EntityTopSample& a, const EntityTopSample& b)
                {
                    if (a.skinTicks != b.skinTicks)
                        return a.skinTicks > b.skinTicks;
                    if (a.animationTicks != b.animationTicks)
                        return a.animationTicks > b.animationTicks;
                    return a.renderQueueCalls > b.renderQueueCalls;
                });
            for (size_t i = 0; i < entities.size() && i < kTopContributorCount; ++i)
            {
                const EntityTopSample& sample = entities[i];
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile][EntityTop] rank=%u entity=0x%p name=%s mesh=%s shadows=%s renderQueue/f=%.2f animCalls/f=%.2f animCPU=%.3fms/f skinCalls/f=%.2f skinVerts/f=%.0f swCPU=%.3fms/f",
                    static_cast<unsigned>(i + 1),
                    reinterpret_cast<void*>(sample.key),
                    sample.metadataReady && sample.entityName[0]
                        ? sample.entityName.data() : "<unavailable>",
                    sample.metadataReady && sample.meshName[0]
                        ? sample.meshName.data() : "<unavailable>",
                    sample.metadataReady ? (sample.castShadows ? "yes" : "no") : "unknown",
                    static_cast<double>(sample.renderQueueCalls) / frameDivisor,
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

