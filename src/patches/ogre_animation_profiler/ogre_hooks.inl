        void __fastcall HookEntityUpdateAnimation(void* self, void*)
        {
            if (!g_RealEntityUpdateAnimation)
                return;
            if (!g_Enabled.load(std::memory_order_relaxed))
            {
                g_RealEntityUpdateAnimation(self);
                return;
            }

            const bool renderDriven = (t_RenderQueueEntity == self);
            const bool frameTracking = g_PresentObserved.load(std::memory_order_acquire);
            const uint64_t frame = frameTracking
                ? g_FrameEpoch.load(std::memory_order_relaxed)
                : 0;
            EntityProfileSlot* entitySlot = FindOrClaimEntitySlot(self);
            if (entitySlot && frameTracking)
            {
                const uint64_t previous =
                    entitySlot->lastAnimationFrame.exchange(frame, std::memory_order_relaxed);
                if (previous == frame)
                    g_DuplicateAnimationSameFrame.fetch_add(1, std::memory_order_relaxed);
            }

            g_AnimationCalls.fetch_add(1, std::memory_order_relaxed);
            BloomAdd(g_AnimationEntityBloom, self);
            const uint64_t start = ReadQpc();
            uint32_t blendCallsForAnimation = 0;
            uint64_t blendVerticesForAnimation = 0;
            {
                CurrentEntityScope scope(self);
                g_RealEntityUpdateAnimation(self);
                blendCallsForAnimation = t_CurrentAnimationBlendCalls;
                blendVerticesForAnimation = t_CurrentAnimationBlendVertices;
            }
            const uint64_t elapsed = ReadQpc() - start;

            g_AnimationTicks.fetch_add(elapsed, std::memory_order_relaxed);
            g_AnimationLatencyBuckets[LatencyBucket(elapsed)].fetch_add(1, std::memory_order_relaxed);
            AtomicMax(g_AnimationMaxTicks, elapsed);
            if (renderDriven)
            {
                g_RenderDrivenAnimationCalls.fetch_add(1, std::memory_order_relaxed);
                g_RenderDrivenAnimationTicks.fetch_add(elapsed, std::memory_order_relaxed);
            }
            else
            {
                g_ExternalAnimationCalls.fetch_add(1, std::memory_order_relaxed);
                g_ExternalAnimationTicks.fetch_add(elapsed, std::memory_order_relaxed);
            }

            if (blendCallsForAnimation)
            {
                g_AnimationWithBlendCalls.fetch_add(1, std::memory_order_relaxed);
                g_BlendCallsInAnimations.fetch_add(blendCallsForAnimation, std::memory_order_relaxed);
                g_BlendVerticesInAnimations.fetch_add(blendVerticesForAnimation, std::memory_order_relaxed);
            }
            else
            {
                g_AnimationWithoutBlendCalls.fetch_add(1, std::memory_order_relaxed);
            }

            if (entitySlot)
            {
                entitySlot->animationCalls.fetch_add(1, std::memory_order_relaxed);
                entitySlot->animationTicks.fetch_add(elapsed, std::memory_order_relaxed);
            }
        }

        void __cdecl HookSoftwareVertexBlend(
            const Ogre::VertexData* sourceVertexData,
            const Ogre::VertexData* targetVertexData,
            const void* const* blendMatrices,
            size_t numMatrices,
            bool blendNormals)
        {
            if (!g_RealSoftwareVertexBlend)
                return;
            if (!g_Enabled.load(std::memory_order_relaxed))
            {
                g_RealSoftwareVertexBlend(
                    sourceVertexData,
                    targetVertexData,
                    blendMatrices,
                    numMatrices,
                    blendNormals);
                return;
            }

            const size_t vertices = ReadVertexCount(sourceVertexData);
            const size_t vertexBucket = VertexBucket(vertices);
            const size_t matrixBucket = MatrixBucket(numMatrices);
            const bool firstBlendInAnimation =
                t_CurrentAnimationEntity && t_CurrentAnimationBlendCalls == 0;

            g_SoftwareBlendCalls.fetch_add(1, std::memory_order_relaxed);
            g_SoftwareBlendVertices.fetch_add(vertices, std::memory_order_relaxed);
            g_VertexBucketCalls[vertexBucket].fetch_add(1, std::memory_order_relaxed);
            g_VertexBucketVertices[vertexBucket].fetch_add(vertices, std::memory_order_relaxed);
            g_MatrixBucketCalls[matrixBucket].fetch_add(1, std::memory_order_relaxed);
            g_BlendMatrixTotal.fetch_add(numMatrices, std::memory_order_relaxed);
            AtomicMax(g_BlendMatrixMax, numMatrices);
            if (blendNormals)
                g_BlendNormalsCalls.fetch_add(1, std::memory_order_relaxed);

            EntityProfileSlot* entitySlot = FindOrClaimEntitySlot(t_CurrentAnimationEntity);
            if (t_CurrentAnimationEntity)
            {
                ++t_CurrentAnimationBlendCalls;
                t_CurrentAnimationBlendVertices += vertices;
                BloomAdd(g_SkinnedEntityBloom, t_CurrentAnimationEntity);
                if (firstBlendInAnimation && entitySlot &&
                    g_PresentObserved.load(std::memory_order_acquire))
                {
                    const uint64_t frame = g_FrameEpoch.load(std::memory_order_relaxed);
                    const uint64_t previous =
                        entitySlot->lastSkinFrame.exchange(frame, std::memory_order_relaxed);
                    if (previous == frame)
                        g_DuplicateSkinSameFrame.fetch_add(1, std::memory_order_relaxed);
                }
            }
            else
            {
                g_OrphanBlendCalls.fetch_add(1, std::memory_order_relaxed);
            }

            SourceProfileSlot* sourceSlot = FindOrClaimSourceSlot(sourceVertexData, vertices);
            const uint64_t start = ReadQpc();
            {
                SoftwareBlendScope scope;
                g_RealSoftwareVertexBlend(
                    sourceVertexData,
                    targetVertexData,
                    blendMatrices,
                    numMatrices,
                    blendNormals);
            }
            const uint64_t elapsed = ReadQpc() - start;

            g_SoftwareBlendTicks.fetch_add(elapsed, std::memory_order_relaxed);
            if (t_CurrentAnimationEntity)
                g_SoftwareBlendTicksInAnimation.fetch_add(elapsed, std::memory_order_relaxed);
            g_SoftwareBlendLatencyBuckets[LatencyBucket(elapsed)].fetch_add(1, std::memory_order_relaxed);
            g_VertexBucketTicks[vertexBucket].fetch_add(elapsed, std::memory_order_relaxed);
            AtomicMax(g_SoftwareBlendMaxTicks, elapsed);
            if (entitySlot)
            {
                entitySlot->skinCalls.fetch_add(1, std::memory_order_relaxed);
                entitySlot->skinVertices.fetch_add(vertices, std::memory_order_relaxed);
                entitySlot->skinTicks.fetch_add(elapsed, std::memory_order_relaxed);
            }
            if (sourceSlot)
            {
                sourceSlot->calls.fetch_add(1, std::memory_order_relaxed);
                sourceSlot->vertices.fetch_add(vertices, std::memory_order_relaxed);
                sourceSlot->ticks.fetch_add(elapsed, std::memory_order_relaxed);
            }
        }

