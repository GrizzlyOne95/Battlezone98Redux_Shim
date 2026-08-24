        void ReportAndResetInterval(ULONGLONG intervalMs)
        {
            const uint64_t animationCalls = g_AnimationCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t animationTicks = g_AnimationTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t renderDrivenCalls = g_RenderDrivenAnimationCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t renderDrivenTicks = g_RenderDrivenAnimationTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t externalCalls = g_ExternalAnimationCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t externalTicks = g_ExternalAnimationTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t animationWithBlend = g_AnimationWithBlendCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t animationWithoutBlend = g_AnimationWithoutBlendCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t blendCallsInAnimations = g_BlendCallsInAnimations.exchange(0, std::memory_order_acq_rel);
            const uint64_t blendVerticesInAnimations = g_BlendVerticesInAnimations.exchange(0, std::memory_order_acq_rel);
            const uint64_t duplicateAnimation = g_DuplicateAnimationSameFrame.exchange(0, std::memory_order_acq_rel);
            const uint64_t duplicateSkin = g_DuplicateSkinSameFrame.exchange(0, std::memory_order_acq_rel);
            const uint64_t duplicateRenderQueue =
                g_DuplicateRenderQueueSameFrame.exchange(0, std::memory_order_acq_rel);
            const uint64_t blendCalls = g_SoftwareBlendCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t blendVertices = g_SoftwareBlendVertices.exchange(0, std::memory_order_acq_rel);
            const uint64_t blendTicks = g_SoftwareBlendTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t blendTicksInAnimation = g_SoftwareBlendTicksInAnimation.exchange(0, std::memory_order_acq_rel);
            const uint64_t orphanBlendCalls = g_OrphanBlendCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t matrixTotal = g_BlendMatrixTotal.exchange(0, std::memory_order_acq_rel);
            const uint64_t matrixMax = g_BlendMatrixMax.exchange(0, std::memory_order_acq_rel);
            const uint64_t blendNormals = g_BlendNormalsCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t animationMaxTicks = g_AnimationMaxTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t blendMaxTicks = g_SoftwareBlendMaxTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t renderCalls = g_RenderQueueCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t sceneRenderCalls =
                g_SceneRenderCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t shadowSceneRenderCalls =
                g_ShadowSceneRenderCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t mainRenderQueueCalls =
                g_MainRenderQueueCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t shadowRenderQueueCalls =
                g_ShadowRenderQueueCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t mainAnimationCalls =
                g_MainAnimationCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t shadowAnimationCalls =
                g_ShadowAnimationCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t mainSoftwareBlendCalls =
                g_MainSoftwareBlendCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t shadowSoftwareBlendCalls =
                g_ShadowSoftwareBlendCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t renderSystemSubmissions =
                g_RenderSystemSubmissions.exchange(0, std::memory_order_acq_rel);
            const uint64_t renderSystemSubmissionTicks =
                g_RenderSystemSubmissionTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t renderSystemSubmissionMaxTicks =
                g_RenderSystemSubmissionMaxTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t contextVtableRefreshes =
                g_ContextVtableRefreshes.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawCalls = g_DrawCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawVertices = g_DrawVertices.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawIndexedCalls = g_DrawIndexedCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawIndexedIndices = g_DrawIndexedIndices.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawIndexedInstancedCalls = g_DrawIndexedInstancedCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawIndexedInstancedIndices = g_DrawIndexedInstancedIndices.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawInstancedCalls = g_DrawInstancedCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawInstancedVertices = g_DrawInstancedVertices.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawIndexedIndirectCalls = g_DrawIndexedInstancedIndirectCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawIndirectCalls = g_DrawInstancedIndirectCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t mapCalls = g_MapCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t mapDuringAnimation = g_MapDuringAnimationCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t mapDuringBlend = g_MapDuringBlendCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t mapTicks = g_MapTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t mapMaxTicks = g_MapMaxTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t mapWrite = g_MapWriteCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t mapDiscard = g_MapWriteDiscardCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t mapNoOverwrite = g_MapWriteNoOverwriteCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t mapOther = g_MapOtherCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t unmapCalls = g_UnmapCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t unmapDuringAnimation = g_UnmapDuringAnimationCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t updateCalls = g_UpdateSubresourceCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t updateDuringAnimation = g_UpdateSubresourceDuringAnimationCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t updateDuringBlend = g_UpdateSubresourceDuringBlendCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t updateTicks = g_UpdateSubresourceTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t updateMaxTicks = g_UpdateSubresourceMaxTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t presents = g_Presents.exchange(0, std::memory_order_acq_rel);
            const uint64_t d3d9RenderStates =
                g_D3D9RenderStateCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t d3d9BlendStates =
                g_D3D9BlendStateCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t d3d9Textures =
                g_D3D9TextureCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t d3d9TextureStages =
                g_D3D9TextureStageStateCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t d3d9Samplers =
                g_D3D9SamplerStateCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t d3d9VertexShaders =
                g_D3D9VertexShaderCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t d3d9PixelShaders =
                g_D3D9PixelShaderCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t frameSamples = g_FrameTimeSamples.exchange(0, std::memory_order_acq_rel);
            const uint64_t frameTicks = g_FrameTimeTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t frameMaxTicks = g_FrameTimeMaxTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t over1667 = g_FrameOver1667.exchange(0, std::memory_order_acq_rel);
            const uint64_t over2500 = g_FrameOver2500.exchange(0, std::memory_order_acq_rel);
            const uint64_t over3333 = g_FrameOver3333.exchange(0, std::memory_order_acq_rel);
            const uint64_t nativeChunkSimCalls = g_NativeChunkSimCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t nativeChunkSimTicks = g_NativeChunkSimTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t nativeChunkActiveTotal = g_NativeChunkActiveTotal.exchange(0, std::memory_order_acq_rel);
            const uint64_t nativeChunkActiveMax = g_NativeChunkActiveMax.exchange(0, std::memory_order_acq_rel);
            const uint64_t dynamicPrepareCalls =
                g_DynamicGeometryPrepareCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t dynamicRebuilds =
                g_DynamicGeometryRebuilds.exchange(0, std::memory_order_acq_rel);
            const uint64_t dynamicPrepareTicks =
                g_DynamicGeometryPrepareTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t dynamicPrepareMaxTicks =
                g_DynamicGeometryPrepareMaxTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t dynamicQueueCalls =
                g_DynamicGeometryQueueCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t dynamicBatchTotal =
                g_DynamicGeometryBatchTotal.exchange(0, std::memory_order_acq_rel);
            const uint64_t dynamicBatchMax =
                g_DynamicGeometryBatchMax.exchange(0, std::memory_order_acq_rel);
            const uint64_t dynamicMergeableBatches =
                g_DynamicGeometryMergeableBatchTotal.exchange(
                    0, std::memory_order_acq_rel);
            const uint64_t dynamicBlendedBatches =
                g_DynamicGeometryBlendedBatchTotal.exchange(
                    0, std::memory_order_acq_rel);
            const uint64_t dynamicDistinctMaterials =
                g_DynamicGeometryDistinctMaterialTotal.exchange(
                    0, std::memory_order_acq_rel);
            const uint64_t dynamicVertices =
                g_DynamicGeometryVertexTotal.exchange(
                    0, std::memory_order_acq_rel);
            const uint64_t dynamicIndices =
                g_DynamicGeometryIndexTotal.exchange(
                    0, std::memory_order_acq_rel);
            const uint64_t chunkShadowQueries =
                g_ChunkShadowQueries.exchange(0, std::memory_order_acq_rel);
            const uint64_t chunkShadowSuppressions =
                g_ChunkShadowSuppressions.exchange(0, std::memory_order_acq_rel);
            const uint64_t skinSourceShadowQueries =
                g_Dx11SkinSourceShadowQueries.exchange(
                    0, std::memory_order_acq_rel);
            const uint64_t skinSourceShadowRepairs =
                g_Dx11SkinSourceShadowRepairs.exchange(
                    0, std::memory_order_acq_rel);
            const uint64_t skinSourceShadowRepairBytes =
                g_Dx11SkinSourceShadowRepairBytes.exchange(
                    0, std::memory_order_acq_rel);
            const uint64_t skinSourceShadowFailures =
                g_Dx11SkinSourceShadowFailures.exchange(
                    0, std::memory_order_acq_rel);

            uint64_t animationUnique = 0;
            uint64_t skinnedUnique = 0;
            uint64_t renderUnique = 0;
            uint64_t skinnedNotRendered = 0;
            for (size_t i = 0; i < kBloomWords; ++i)
            {
                const uint64_t animationWord = g_AnimationEntityBloom[i].exchange(0, std::memory_order_acq_rel);
                const uint64_t skinnedWord = g_SkinnedEntityBloom[i].exchange(0, std::memory_order_acq_rel);
                const uint64_t renderWord = g_RenderEntityBloom[i].exchange(0, std::memory_order_acq_rel);
                animationUnique += static_cast<uint64_t>(std::popcount(animationWord));
                skinnedUnique += static_cast<uint64_t>(std::popcount(skinnedWord));
                renderUnique += static_cast<uint64_t>(std::popcount(renderWord));
                skinnedNotRendered += static_cast<uint64_t>(std::popcount(skinnedWord & ~renderWord));
            }

            std::array<uint64_t, kLatencyBucketCount> animationLatency{};
            std::array<uint64_t, kLatencyBucketCount> blendLatency{};
            for (size_t i = 0; i < kLatencyBucketCount; ++i)
            {
                animationLatency[i] = g_AnimationLatencyBuckets[i].exchange(0, std::memory_order_acq_rel);
                blendLatency[i] = g_SoftwareBlendLatencyBuckets[i].exchange(0, std::memory_order_acq_rel);
            }

            std::array<uint64_t, kVertexBucketCount> vertexCalls{};
            std::array<uint64_t, kVertexBucketCount> vertexVertices{};
            std::array<uint64_t, kVertexBucketCount> vertexTicks{};
            for (size_t i = 0; i < kVertexBucketCount; ++i)
            {
                vertexCalls[i] = g_VertexBucketCalls[i].exchange(0, std::memory_order_acq_rel);
                vertexVertices[i] = g_VertexBucketVertices[i].exchange(0, std::memory_order_acq_rel);
                vertexTicks[i] = g_VertexBucketTicks[i].exchange(0, std::memory_order_acq_rel);
            }

            std::array<uint64_t, kMatrixBucketCount> matrixBuckets{};
            for (size_t i = 0; i < kMatrixBucketCount; ++i)
                matrixBuckets[i] = g_MatrixBucketCalls[i].exchange(0, std::memory_order_acq_rel);

            std::array<uint64_t, kFrameTimeBucketCount> frameBuckets{};
            for (size_t i = 0; i < kFrameTimeBucketCount; ++i)
                frameBuckets[i] = g_FrameTimeBuckets[i].exchange(0, std::memory_order_acq_rel);

            const double frameDivisor = presents ? static_cast<double>(presents) : 1.0;
            const double animationMs = TicksToMs(animationTicks);
            const double blendMs = TicksToMs(blendTicks);
            const uint64_t nonBlendTicks = animationTicks > blendTicksInAnimation
                ? animationTicks - blendTicksInAnimation
                : 0;
            const double unnecessaryPct = skinnedUnique
                ? (100.0 * static_cast<double>(skinnedNotRendered) / static_cast<double>(skinnedUnique))
                : 0.0;
            const double renderDrivenPct = animationCalls
                ? (100.0 * static_cast<double>(renderDrivenCalls) / static_cast<double>(animationCalls))
                : 0.0;
            const double matrixAverage = blendCalls
                ? static_cast<double>(matrixTotal) / static_cast<double>(blendCalls)
                : 0.0;
            const double fps = intervalMs
                ? static_cast<double>(presents) * 1000.0 / static_cast<double>(intervalMs)
                : 0.0;
            const double frameMeanMs = frameSamples ? TicksToMs(frameTicks) / frameSamples : 0.0;
            const double frameP50Ms = PercentileFromHistogram(frameBuckets, frameSamples, 50);
            const double frameP95Ms = PercentileFromHistogram(frameBuckets, frameSamples, 95);
            const double frameP99Ms = PercentileFromHistogram(frameBuckets, frameSamples, 99);
            const double frameMaxMs = TicksToMs(frameMaxTicks);
            const double nativeChunkActiveAverage = nativeChunkSimCalls
                ? static_cast<double>(nativeChunkActiveTotal) /
                    static_cast<double>(nativeChunkSimCalls)
                : 0.0;

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] fps=%.1f frameMean=%.2f p50=%.2f p95=%.2f p99=%.2f max=%.2f | anim=%.1f/f renderDriven=%.1f%% external=%.2f/f animCPU=%.3fms/f nonBlend=%.3fms/f | skin=%.1f/f verts=%.0f/f swCPU=%.3fms/f dupAnim=%llu dupSkin=%llu orphan=%llu",
                fps, frameMeanMs, frameP50Ms, frameP95Ms, frameP99Ms, frameMaxMs,
                static_cast<double>(animationCalls) / frameDivisor,
                renderDrivenPct,
                static_cast<double>(externalCalls) / frameDivisor,
                animationMs / frameDivisor,
                TicksToMs(nonBlendTicks) / frameDivisor,
                static_cast<double>(blendCalls) / frameDivisor,
                static_cast<double>(blendVertices) / frameDivisor,
                blendMs / frameDivisor,
                static_cast<unsigned long long>(duplicateAnimation),
                static_cast<unsigned long long>(duplicateSkin),
                static_cast<unsigned long long>(orphanBlendCalls));

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile][Chunk] activeAvg=%.1f activeMax=%llu simCalls=%llu simCPU=%.3fms/f maxAttribution=stock-native-only",
                nativeChunkActiveAverage,
                static_cast<unsigned long long>(nativeChunkActiveMax),
                static_cast<unsigned long long>(nativeChunkSimCalls),
                TicksToMs(nativeChunkSimTicks) / frameDivisor);

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile][DynamicGeometry] prepare=%.2f/f rebuilds=%.2f/f queue=%.2f/f batchesAvg=%.1f batchesMax=%llu mergeable=%.1f/call blended=%.1f/call materials=%.1f/call vertices=%.0f/call indices=%.0f/call cpu=%.3fms/f max=%.3fms",
                static_cast<double>(dynamicPrepareCalls) / frameDivisor,
                static_cast<double>(dynamicRebuilds) / frameDivisor,
                static_cast<double>(dynamicQueueCalls) / frameDivisor,
                dynamicQueueCalls
                    ? static_cast<double>(dynamicBatchTotal) / dynamicQueueCalls
                    : 0.0,
                static_cast<unsigned long long>(dynamicBatchMax),
                dynamicQueueCalls
                    ? static_cast<double>(dynamicMergeableBatches) / dynamicQueueCalls
                    : 0.0,
                dynamicQueueCalls
                    ? static_cast<double>(dynamicBlendedBatches) / dynamicQueueCalls
                    : 0.0,
                dynamicQueueCalls
                    ? static_cast<double>(dynamicDistinctMaterials) / dynamicQueueCalls
                    : 0.0,
                dynamicQueueCalls
                    ? static_cast<double>(dynamicVertices) / dynamicQueueCalls
                    : 0.0,
                dynamicQueueCalls
                    ? static_cast<double>(dynamicIndices) / dynamicQueueCalls
                    : 0.0,
                TicksToMs(dynamicPrepareTicks) / frameDivisor,
                TicksToMs(dynamicPrepareMaxTicks));
            ReportDynamicGeometryContributors(frameDivisor);

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile][ChunkShadowPolicy] enabled=%s installed=%s queries=%.2f/f suppressed=%.2f/f",
                g_ChunkShadowPolicyEnabled.load(std::memory_order_acquire) ? "yes" : "no",
                g_ChunkShadowHookInstalled.load(std::memory_order_acquire) ? "yes" : "no",
                static_cast<double>(chunkShadowQueries) / frameDivisor,
                static_cast<double>(chunkShadowSuppressions) / frameDivisor);

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile][DX11SkinSourceShadow] enabled=%s installed=%s queries=%llu repairs=%llu bytes=%llu failures=%llu failureStage=%u",
                g_Dx11SkinSourceShadowPolicyEnabled.load(
                    std::memory_order_acquire) ? "yes" : "no",
                g_Dx11SkinSourceShadowHookInstalled.load(
                    std::memory_order_acquire) ? "yes" : "no",
                static_cast<unsigned long long>(skinSourceShadowQueries),
                static_cast<unsigned long long>(skinSourceShadowRepairs),
                static_cast<unsigned long long>(skinSourceShadowRepairBytes),
                static_cast<unsigned long long>(skinSourceShadowFailures),
                g_Dx11SkinSourceShadowFailureStage.load(
                    std::memory_order_relaxed));

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile][Anim] renderDriven=%llu cpu=%.3fms/f external=%llu cpu=%.3fms/f withBlend=%llu withoutBlend=%llu blendCalls/anim=%.2f verts/anim=%.0f maxAnim=%.3fms latency=[%llu,%llu,%llu,%llu,%llu,%llu,%llu]",
                static_cast<unsigned long long>(renderDrivenCalls), TicksToMs(renderDrivenTicks) / frameDivisor,
                static_cast<unsigned long long>(externalCalls), TicksToMs(externalTicks) / frameDivisor,
                static_cast<unsigned long long>(animationWithBlend),
                static_cast<unsigned long long>(animationWithoutBlend),
                animationCalls ? static_cast<double>(blendCallsInAnimations) / animationCalls : 0.0,
                animationCalls ? static_cast<double>(blendVerticesInAnimations) / animationCalls : 0.0,
                TicksToMs(animationMaxTicks),
                static_cast<unsigned long long>(animationLatency[0]),
                static_cast<unsigned long long>(animationLatency[1]),
                static_cast<unsigned long long>(animationLatency[2]),
                static_cast<unsigned long long>(animationLatency[3]),
                static_cast<unsigned long long>(animationLatency[4]),
                static_cast<unsigned long long>(animationLatency[5]),
                static_cast<unsigned long long>(animationLatency[6]));

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile][SkinSize] calls=[%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu] verts/f=[%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f] cpuMs/f=[%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f] maxSkin=%.3fms latency=[%llu,%llu,%llu,%llu,%llu,%llu,%llu]",
                static_cast<unsigned long long>(vertexCalls[0]), static_cast<unsigned long long>(vertexCalls[1]),
                static_cast<unsigned long long>(vertexCalls[2]), static_cast<unsigned long long>(vertexCalls[3]),
                static_cast<unsigned long long>(vertexCalls[4]), static_cast<unsigned long long>(vertexCalls[5]),
                static_cast<unsigned long long>(vertexCalls[6]), static_cast<unsigned long long>(vertexCalls[7]),
                static_cast<double>(vertexVertices[0]) / frameDivisor, static_cast<double>(vertexVertices[1]) / frameDivisor,
                static_cast<double>(vertexVertices[2]) / frameDivisor, static_cast<double>(vertexVertices[3]) / frameDivisor,
                static_cast<double>(vertexVertices[4]) / frameDivisor, static_cast<double>(vertexVertices[5]) / frameDivisor,
                static_cast<double>(vertexVertices[6]) / frameDivisor, static_cast<double>(vertexVertices[7]) / frameDivisor,
                TicksToMs(vertexTicks[0]) / frameDivisor, TicksToMs(vertexTicks[1]) / frameDivisor,
                TicksToMs(vertexTicks[2]) / frameDivisor, TicksToMs(vertexTicks[3]) / frameDivisor,
                TicksToMs(vertexTicks[4]) / frameDivisor, TicksToMs(vertexTicks[5]) / frameDivisor,
                TicksToMs(vertexTicks[6]) / frameDivisor, TicksToMs(vertexTicks[7]) / frameDivisor,
                TicksToMs(blendMaxTicks),
                static_cast<unsigned long long>(blendLatency[0]), static_cast<unsigned long long>(blendLatency[1]),
                static_cast<unsigned long long>(blendLatency[2]), static_cast<unsigned long long>(blendLatency[3]),
                static_cast<unsigned long long>(blendLatency[4]), static_cast<unsigned long long>(blendLatency[5]),
                static_cast<unsigned long long>(blendLatency[6]));

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile][SkinMeta] matrices avg=%.1f max=%llu buckets=[%llu,%llu,%llu,%llu,%llu] blendNormals=%.1f%% | renderQueue=%.1f/f duplicateRenderQueue=%llu anim/render=%.2f skin/render=%.2f unique anim~=%llu skin~=%llu render~=%llu skinNotRendered~=%llu (%.1f%%)",
                matrixAverage,
                static_cast<unsigned long long>(matrixMax),
                static_cast<unsigned long long>(matrixBuckets[0]), static_cast<unsigned long long>(matrixBuckets[1]),
                static_cast<unsigned long long>(matrixBuckets[2]), static_cast<unsigned long long>(matrixBuckets[3]),
                static_cast<unsigned long long>(matrixBuckets[4]),
                blendCalls ? 100.0 * static_cast<double>(blendNormals) / blendCalls : 0.0,
                static_cast<double>(renderCalls) / frameDivisor,
                static_cast<unsigned long long>(duplicateRenderQueue),
                renderCalls ? static_cast<double>(animationCalls) / renderCalls : 0.0,
                renderCalls ? static_cast<double>(blendCalls) / renderCalls : 0.0,
                static_cast<unsigned long long>(animationUnique),
                static_cast<unsigned long long>(skinnedUnique),
                static_cast<unsigned long long>(renderUnique),
                static_cast<unsigned long long>(skinnedNotRendered),
                unnecessaryPct);

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile][Passes] scene=%.2f/f shadowScene=%.2f/f | rqMain=%.2f/f rqShadow=%.2f/f | animMain=%.2f/f animShadow=%.2f/f | skinMain=%.2f/f skinShadow=%.2f/f",
                static_cast<double>(sceneRenderCalls) / frameDivisor,
                static_cast<double>(shadowSceneRenderCalls) / frameDivisor,
                static_cast<double>(mainRenderQueueCalls) / frameDivisor,
                static_cast<double>(shadowRenderQueueCalls) / frameDivisor,
                static_cast<double>(mainAnimationCalls) / frameDivisor,
                static_cast<double>(shadowAnimationCalls) / frameDivisor,
                static_cast<double>(mainSoftwareBlendCalls) / frameDivisor,
                static_cast<double>(shadowSoftwareBlendCalls) / frameDivisor);

            for (CameraProfileSlot& cameraSlot : g_CameraProfileSlots)
            {
                const uint64_t calls = cameraSlot.renderCalls.exchange(
                    0, std::memory_order_acq_rel);
                const uint64_t nestedCalls = cameraSlot.nestedRenderCalls.exchange(
                    0, std::memory_order_acq_rel);
                if (!calls)
                    continue;
                const bool metadataReady = cameraSlot.metadataState.load(
                    std::memory_order_acquire) == 2;
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile][Camera] camera=0x%p name=%s renders=%.2f/f nested=%.2f/f",
                    reinterpret_cast<void*>(cameraSlot.key.load(
                        std::memory_order_relaxed)),
                    metadataReady && cameraSlot.cameraName[0]
                        ? cameraSlot.cameraName.data()
                        : "<unknown>",
                    static_cast<double>(calls) / frameDivisor,
                    static_cast<double>(nestedCalls) / frameDivisor);
            }

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile][Uploads] Map=%llu anim=%llu blend=%llu cpu=%.3fms/f max=%.3fms types[W=%llu WD=%llu WNO=%llu other=%llu] Unmap=%llu anim=%llu | Update=%llu anim=%llu blend=%llu cpu=%.3fms/f max=%.3fms",
                static_cast<unsigned long long>(mapCalls),
                static_cast<unsigned long long>(mapDuringAnimation),
                static_cast<unsigned long long>(mapDuringBlend),
                TicksToMs(mapTicks) / frameDivisor,
                TicksToMs(mapMaxTicks),
                static_cast<unsigned long long>(mapWrite),
                static_cast<unsigned long long>(mapDiscard),
                static_cast<unsigned long long>(mapNoOverwrite),
                static_cast<unsigned long long>(mapOther),
                static_cast<unsigned long long>(unmapCalls),
                static_cast<unsigned long long>(unmapDuringAnimation),
                static_cast<unsigned long long>(updateCalls),
                static_cast<unsigned long long>(updateDuringAnimation),
                static_cast<unsigned long long>(updateDuringBlend),
                TicksToMs(updateTicks) / frameDivisor,
                TicksToMs(updateMaxTicks));

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile][Render] OgreSubmit=%.1f/f cpu=%.3fms/f max=%.3fms Draw=%.1f/f verts=%.0f/f DrawIndexed=%.1f/f indices=%.0f/f DrawInstanced=%.1f/f verts=%.0f/f DrawIndexedInstanced=%.1f/f indices=%.0f/f indirect=[%.2f,%.2f]/f contextRefresh=%llu frameSlow[>16.67=%llu >25=%llu >33.33=%llu]",
                static_cast<double>(renderSystemSubmissions) / frameDivisor,
                TicksToMs(renderSystemSubmissionTicks) / frameDivisor,
                TicksToMs(renderSystemSubmissionMaxTicks),
                static_cast<double>(drawCalls) / frameDivisor,
                static_cast<double>(drawVertices) / frameDivisor,
                static_cast<double>(drawIndexedCalls) / frameDivisor,
                static_cast<double>(drawIndexedIndices) / frameDivisor,
                static_cast<double>(drawInstancedCalls) / frameDivisor,
                static_cast<double>(drawInstancedVertices) / frameDivisor,
                static_cast<double>(drawIndexedInstancedCalls) / frameDivisor,
                static_cast<double>(drawIndexedInstancedIndices) / frameDivisor,
                static_cast<double>(drawIndirectCalls) / frameDivisor,
                static_cast<double>(drawIndexedIndirectCalls) / frameDivisor,
                static_cast<unsigned long long>(contextVtableRefreshes),
                static_cast<unsigned long long>(over1667),
                static_cast<unsigned long long>(over2500),
                static_cast<unsigned long long>(over3333));

            const unsigned isolationMask =
                g_IsolationMask.load(std::memory_order_relaxed);
            const uint64_t isolatedRenderables =
                g_IsolatedRenderables.exchange(0, std::memory_order_acq_rel);
            if (isolationMask != 0 || isolatedRenderables != 0)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile][Isolation] mask=0x%X suppressed=%.1f/f -- capture is NOT stock rendering",
                    isolationMask,
                    static_cast<double>(isolatedRenderables) / frameDivisor);
            }

            ReportRenderContributors(frameDivisor, renderSystemSubmissions);

            if (g_D3D9DeviceObserved.load(std::memory_order_acquire))
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile][D3D9] DrawPrimitive=%.1f/f DrawIndexedPrimitive=%.1f/f renderState=%.1f/f blendState=%.1f/f texture=%.1f/f textureStage=%.1f/f sampler=%.1f/f vertexShader=%.1f/f pixelShader=%.1f/f",
                    static_cast<double>(drawCalls) / frameDivisor,
                    static_cast<double>(drawIndexedCalls) / frameDivisor,
                    static_cast<double>(d3d9RenderStates) / frameDivisor,
                    static_cast<double>(d3d9BlendStates) / frameDivisor,
                    static_cast<double>(d3d9Textures) / frameDivisor,
                    static_cast<double>(d3d9TextureStages) / frameDivisor,
                    static_cast<double>(d3d9Samplers) / frameDivisor,
                    static_cast<double>(d3d9VertexShaders) / frameDivisor,
                    static_cast<double>(d3d9PixelShaders) / frameDivisor);
            }

            if (duplicateSkin || duplicateAnimation || duplicateRenderQueue)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile][WARN] same-frame repeat detected duplicateAnimation=%llu duplicateSkin=%llu duplicateRenderQueue=%llu",
                    static_cast<unsigned long long>(duplicateAnimation),
                    static_cast<unsigned long long>(duplicateSkin),
                    static_cast<unsigned long long>(duplicateRenderQueue));
            }

            ReportTopContributors(frameDivisor);
            AppendCsvRow(
                GetTickCount64(), fps, frameMeanMs, frameP50Ms, frameP95Ms, frameP99Ms, frameMaxMs,
                animationCalls, renderDrivenCalls, externalCalls,
                animationMs / frameDivisor, TicksToMs(nonBlendTicks) / frameDivisor,
                blendCalls, blendVertices, blendMs / frameDivisor,
                duplicateAnimation, duplicateSkin, orphanBlendCalls,
                matrixAverage, matrixMax,
                mapCalls, mapDuringAnimation, mapDuringBlend, TicksToMs(mapTicks) / frameDivisor,
                updateCalls, updateDuringAnimation,
                drawCalls, drawIndexedCalls, drawInstancedCalls, drawIndexedInstancedCalls);
        }

