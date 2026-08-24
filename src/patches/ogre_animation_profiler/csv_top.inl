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

        void ReportRenderContributors(
            double frameDivisor,
            uint64_t totalOgreSubmissions)
        {
            std::vector<RenderContributorSample> samples;
            samples.reserve(256);
            uint64_t attributedCalls = 0;
            uint64_t attributedSubmissions = 0;
            uint64_t attributedDraws = 0;
            uint64_t attributedIndexedDraws = 0;

            for (RenderContributorSlot& slot : g_RenderContributorSlots)
            {
                const uintptr_t key = slot.key.load(std::memory_order_relaxed);
                if (!key)
                    continue;

                RenderContributorSample sample{};
                sample.key = key;
                sample.calls = slot.calls.exchange(0, std::memory_order_acq_rel);
                sample.mainCalls = slot.mainCalls.exchange(
                    0, std::memory_order_acq_rel);
                sample.shadowCalls = slot.shadowCalls.exchange(
                    0, std::memory_order_acq_rel);
                sample.ticks = slot.ticks.exchange(0, std::memory_order_acq_rel);
                sample.ogreSubmissions = slot.ogreSubmissions.exchange(
                    0, std::memory_order_acq_rel);
                sample.operationVertices = slot.operationVertices.exchange(
                    0, std::memory_order_acq_rel);
                sample.operationIndices = slot.operationIndices.exchange(
                    0, std::memory_order_acq_rel);
                sample.draws = slot.draws.exchange(0, std::memory_order_acq_rel);
                sample.indexedDraws = slot.indexedDraws.exchange(
                    0, std::memory_order_acq_rel);
                sample.drawnVertices = slot.drawnVertices.exchange(
                    0, std::memory_order_acq_rel);
                sample.drawnIndices = slot.drawnIndices.exchange(
                    0, std::memory_order_acq_rel);
                sample.renderStates = slot.renderStates.exchange(
                    0, std::memory_order_acq_rel);
                sample.blendStates = slot.blendStates.exchange(
                    0, std::memory_order_acq_rel);
                sample.textureSets = slot.textureSets.exchange(
                    0, std::memory_order_acq_rel);
                sample.textureStageSets = slot.textureStageSets.exchange(
                    0, std::memory_order_acq_rel);
                sample.samplerSets = slot.samplerSets.exchange(
                    0, std::memory_order_acq_rel);
                sample.vertexShaderSets = slot.vertexShaderSets.exchange(
                    0, std::memory_order_acq_rel);
                sample.pixelShaderSets = slot.pixelShaderSets.exchange(
                    0, std::memory_order_acq_rel);
                sample.noDrawSubmissions = slot.noDrawSubmissions.exchange(
                    0, std::memory_order_acq_rel);
                sample.emptyVertexSubmissions =
                    slot.emptyVertexSubmissions.exchange(
                        0, std::memory_order_acq_rel);
                sample.zeroPrimSubmissions = slot.zeroPrimSubmissions.exchange(
                    0, std::memory_order_acq_rel);
                sample.unobservedSubmissions =
                    slot.unobservedSubmissions.exchange(
                        0, std::memory_order_acq_rel);
                sample.metadataReady = slot.metadataState.load(
                    std::memory_order_acquire) == 2;
                if (sample.metadataReady)
                {
                    sample.typeName = slot.typeName;
                    sample.ownerName = slot.ownerName;
                    sample.meshName = slot.meshName;
                    sample.materialName = slot.materialName;
                    sample.techniqueName = slot.techniqueName;
                    sample.schemeName = slot.schemeName;
                    sample.passName = slot.passName;
                    sample.cameraName = slot.cameraName;
                    sample.passIndex = slot.passIndex;
                    sample.lodIndex = slot.lodIndex;
                }
                if (!sample.calls && !sample.ogreSubmissions)
                    continue;
                attributedCalls += sample.calls;
                attributedSubmissions += sample.ogreSubmissions;
                attributedDraws += sample.draws;
                attributedIndexedDraws += sample.indexedDraws;
                samples.push_back(sample);
            }

            const uint64_t drops = g_RenderContributorDrops.exchange(
                0, std::memory_order_acq_rel);
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile][RenderContributorSummary] installed=%s groups=%u renderCalls=%.1f/f OgreSubmit=%.1f/f coverage=%.1f%% Draw=%.1f/f DrawIndexed=%.1f/f drops=%llu noDraw=%.1f/f emptyVerts=%.1f/f zeroPrim=%.1f/f multiDraw=%.1f/f unobserved=%.1f/f",
                g_RenderSingleObjectHookInstalled.load(
                    std::memory_order_acquire) ? "yes" : "no",
                static_cast<unsigned>(samples.size()),
                static_cast<double>(attributedCalls) / frameDivisor,
                static_cast<double>(attributedSubmissions) / frameDivisor,
                totalOgreSubmissions
                    ? 100.0 * static_cast<double>(attributedSubmissions) /
                        static_cast<double>(totalOgreSubmissions)
                    : 0.0,
                static_cast<double>(attributedDraws) / frameDivisor,
                static_cast<double>(attributedIndexedDraws) / frameDivisor,
                static_cast<unsigned long long>(drops),
                static_cast<double>(g_NoDrawSubmissions.exchange(
                    0, std::memory_order_acq_rel)) / frameDivisor,
                static_cast<double>(g_EmptyVertexSubmissions.exchange(
                    0, std::memory_order_acq_rel)) / frameDivisor,
                static_cast<double>(g_ZeroPrimSubmissions.exchange(
                    0, std::memory_order_acq_rel)) / frameDivisor,
                static_cast<double>(g_MultiDrawSubmissions.exchange(
                    0, std::memory_order_acq_rel)) / frameDivisor,
                static_cast<double>(g_UnobservedSubmissions.exchange(
                    0, std::memory_order_acq_rel)) / frameDivisor);

            std::sort(
                samples.begin(), samples.end(),
                [](const RenderContributorSample& left,
                   const RenderContributorSample& right)
                {
                    if (left.ogreSubmissions != right.ogreSubmissions)
                        return left.ogreSubmissions > right.ogreSubmissions;
                    if (left.calls != right.calls)
                        return left.calls > right.calls;
                    return left.ticks > right.ticks;
                });

            const size_t count = (std::min)(
                samples.size(), kRenderContributorTopCount);
            for (size_t i = 0; i < count; ++i)
            {
                const RenderContributorSample& sample = samples[i];
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile][RenderContributorTop] rank=%u type=%s ownerSample=%s mesh=%s material=%s technique=%s scheme=%s lod=%u pass=%u/%s camera=%s main=%.1f/f shadow=%.1f/f renderCalls=%.1f/f OgreSubmit=%.1f/f opVerts=%.0f/f opIndices=%.0f/f Draw=%.1f/f DrawIndexed=%.1f/f drawnVerts=%.0f/f drawnIndices=%.0f/f noDraw=%.1f/f emptyVerts=%.1f/f zeroPrim=%.1f/f unobserved=%.1f/f cpu=%.3fms/f d3d9[state=%.1f blend=%.1f texture=%.1f stage=%.1f sampler=%.1f vs=%.1f ps=%.1f]/f",
                    static_cast<unsigned>(i + 1),
                    sample.metadataReady && sample.typeName[0]
                        ? sample.typeName.data() : "<unknown>",
                    sample.metadataReady && sample.ownerName[0]
                        ? sample.ownerName.data() : "<none>",
                    sample.metadataReady && sample.meshName[0]
                        ? sample.meshName.data() : "<none>",
                    sample.metadataReady && sample.materialName[0]
                        ? sample.materialName.data() : "<unknown>",
                    sample.metadataReady && sample.techniqueName[0]
                        ? sample.techniqueName.data() : "<unnamed>",
                    sample.metadataReady && sample.schemeName[0]
                        ? sample.schemeName.data() : "<default>",
                    sample.lodIndex,
                    sample.passIndex,
                    sample.metadataReady && sample.passName[0]
                        ? sample.passName.data() : "<unnamed>",
                    sample.metadataReady && sample.cameraName[0]
                        ? sample.cameraName.data() : "<unknown>",
                    static_cast<double>(sample.mainCalls) / frameDivisor,
                    static_cast<double>(sample.shadowCalls) / frameDivisor,
                    static_cast<double>(sample.calls) / frameDivisor,
                    static_cast<double>(sample.ogreSubmissions) / frameDivisor,
                    static_cast<double>(sample.operationVertices) / frameDivisor,
                    static_cast<double>(sample.operationIndices) / frameDivisor,
                    static_cast<double>(sample.draws) / frameDivisor,
                    static_cast<double>(sample.indexedDraws) / frameDivisor,
                    static_cast<double>(sample.drawnVertices) / frameDivisor,
                    static_cast<double>(sample.drawnIndices) / frameDivisor,
                    static_cast<double>(sample.noDrawSubmissions) / frameDivisor,
                    static_cast<double>(sample.emptyVertexSubmissions) / frameDivisor,
                    static_cast<double>(sample.zeroPrimSubmissions) / frameDivisor,
                    static_cast<double>(sample.unobservedSubmissions) / frameDivisor,
                    TicksToMs(sample.ticks) / frameDivisor,
                    static_cast<double>(sample.renderStates) / frameDivisor,
                    static_cast<double>(sample.blendStates) / frameDivisor,
                    static_cast<double>(sample.textureSets) / frameDivisor,
                    static_cast<double>(sample.textureStageSets) / frameDivisor,
                    static_cast<double>(sample.samplerSets) / frameDivisor,
                    static_cast<double>(sample.vertexShaderSets) / frameDivisor,
                    static_cast<double>(sample.pixelShaderSets) / frameDivisor);
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
                sample.metadataReady = slot.metadataState.load(
                    std::memory_order_acquire) == 2;
                sample.positionStride = slot.positionStride;
                sample.normalStride = slot.normalStride;
                sample.weightStride = slot.weightStride;
                sample.indexStride = slot.indexStride;
                sample.weightsPerVertex = slot.weightsPerVertex;
                sample.positionShadowed = slot.positionShadowed;
                sample.positionSystemMemory = slot.positionSystemMemory;
                sample.weightShadowed = slot.weightShadowed;
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
                    "[OgreProfile][SkinTop] rank=%u sourceVD=0x%p sourceVerts=%llu calls/f=%.2f verts/f=%.0f swCPU=%.3fms/f layout[pos=%u norm=%u weight=%u index=%u weights=%u posShadow=%s posSystem=%s weightShadow=%s]",
                    static_cast<unsigned>(i + 1),
                    reinterpret_cast<void*>(sample.key),
                    static_cast<unsigned long long>(sample.sourceVertices),
                    static_cast<double>(sample.calls) / frameDivisor,
                    static_cast<double>(sample.vertices) / frameDivisor,
                    TicksToMs(sample.ticks) / frameDivisor,
                    sample.metadataReady ? sample.positionStride : 0,
                    sample.metadataReady ? sample.normalStride : 0,
                    sample.metadataReady ? sample.weightStride : 0,
                    sample.metadataReady ? sample.indexStride : 0,
                    sample.metadataReady ? sample.weightsPerVertex : 0,
                    sample.metadataReady && sample.positionShadowed ? "yes" : "no",
                    sample.metadataReady && sample.positionSystemMemory ? "yes" : "no",
                    sample.metadataReady && sample.weightShadowed ? "yes" : "no");
            }
        }

