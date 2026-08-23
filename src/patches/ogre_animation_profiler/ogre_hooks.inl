        void __fastcall HookEntityUpdateAnimation(void* self, void*)
        {
            FnEntityUpdateAnimation real = g_RealEntityUpdateAnimation
                ? g_RealEntityUpdateAnimation
                : reinterpret_cast<FnEntityUpdateAnimation>(g_EntityUpdateAnimationDetour.trampoline);
            if (!real)
                return;
            real(self);
        }

        void __fastcall HookSceneManagerRenderScene(
            void* self,
            void*,
            void* camera,
            void* viewport,
            bool includeOverlays)
        {
            FnSceneManagerRenderScene real = g_RealSceneManagerRenderScene
                ? g_RealSceneManagerRenderScene
                : reinterpret_cast<FnSceneManagerRenderScene>(
                    g_SceneManagerRenderSceneDetour.trampoline);
            if (!real)
                return;

            if (!g_Enabled.load(std::memory_order_relaxed))
            {
                real(self, camera, viewport, includeOverlays);
                return;
            }

            // Ogre documents shadow-texture rendering as re-entrant calls to
            // this method, so the pre-entry depth classifies the camera pass.
            g_SceneRenderCalls.fetch_add(1, std::memory_order_relaxed);
            if (t_SceneRenderDepth != 0)
                g_ShadowSceneRenderCalls.fetch_add(1, std::memory_order_relaxed);
            CameraProfileSlot* cameraSlot = FindOrClaimCameraSlot(camera);
            CaptureCameraMetadata(cameraSlot, camera);
            if (cameraSlot)
            {
                cameraSlot->renderCalls.fetch_add(1, std::memory_order_relaxed);
                if (t_SceneRenderDepth != 0)
                {
                    cameraSlot->nestedRenderCalls.fetch_add(
                        1, std::memory_order_relaxed);
                }
            }
            SceneRenderScope scope;
            SceneCameraScope cameraScope(camera);
            real(self, camera, viewport, includeOverlays);
        }

        void __fastcall HookSceneManagerRenderSingleObject(
            void* self,
            void*,
            void* renderable,
            const void* pass,
            bool lightScissoringClipping,
            bool doLightIteration,
            const void* manualLightList)
        {
            FnSceneManagerRenderSingleObject real =
                g_RealSceneManagerRenderSingleObject
                    ? g_RealSceneManagerRenderSingleObject
                    : reinterpret_cast<FnSceneManagerRenderSingleObject>(
                        g_SceneManagerRenderSingleObjectDetour.trampoline);
            if (!real)
                return;
            // Isolation is checked before the profiler-enabled gate so an
            // isolation arm can be captured with collection off and PresentMon
            // attached. With no isolation requested this is one relaxed load.
            const unsigned isolationMask =
                g_IsolationMask.load(std::memory_order_relaxed);
            if (!g_Enabled.load(std::memory_order_relaxed))
            {
                if (isolationMask != 0 &&
                    ShouldIsolateRenderable(nullptr, isolationMask, pass))
                {
                    g_IsolatedRenderables.fetch_add(1, std::memory_order_relaxed);
                    return;
                }
                real(
                    self, renderable, pass, lightScissoringClipping,
                    doLightIteration, manualLightList);
                return;
            }

            const void* owner = nullptr;
            const void* mesh = nullptr;
            ResolveSubEntityOwnerAndMesh(renderable, owner, mesh);
            RenderContributorSlot* slot = FindOrClaimRenderContributorSlot(
                renderable, pass, t_CurrentSceneCamera, mesh);
            CaptureRenderContributorMetadata(
                slot, renderable, pass, t_CurrentSceneCamera, owner, mesh);
            if (slot)
            {
                slot->calls.fetch_add(1, std::memory_order_relaxed);
                if (t_SceneRenderDepth > 1)
                    slot->shadowCalls.fetch_add(1, std::memory_order_relaxed);
                else
                    slot->mainCalls.fetch_add(1, std::memory_order_relaxed);
            }

            // Measurement-only isolation arm. Suppressing the renderable here
            // rather than at the render-system boundary removes the material,
            // technique and scheme setup as well as the submission, so the
            // frame-time delta reflects the whole category and not just its
            // backend cost. Default mask is zero, so stock behavior is
            // bit-for-bit unchanged unless OPENSHIM_PROFILE_ISOLATE is set.
            if (isolationMask != 0 &&
                ShouldIsolateRenderable(slot, isolationMask, pass))
            {
                g_IsolatedRenderables.fetch_add(1, std::memory_order_relaxed);
                return;
            }

            const uint64_t start = ReadQpc();
            {
                RenderContributorScope scope(slot);
                real(
                    self, renderable, pass, lightScissoringClipping,
                    doLightIteration, manualLightList);
            }
            if (slot)
            {
                slot->ticks.fetch_add(
                    ReadQpc() - start, std::memory_order_relaxed);
            }
        }

        void __fastcall HookEntityUpdateRenderQueue(void* self, void*, void* renderQueue)
        {
            if (!g_RealEntityUpdateRenderQueue)
                return;
            if (!g_Enabled.load(std::memory_order_relaxed))
            {
                g_RealEntityUpdateRenderQueue(self, renderQueue);
                return;
            }

            g_RenderQueueCalls.fetch_add(1, std::memory_order_relaxed);
            if (t_SceneRenderDepth > 1)
                g_ShadowRenderQueueCalls.fetch_add(1, std::memory_order_relaxed);
            else
                g_MainRenderQueueCalls.fetch_add(1, std::memory_order_relaxed);
            BloomAdd(g_RenderEntityBloom, self);
            EntityProfileSlot* entitySlot = FindOrClaimEntitySlot(self);
            CaptureEntityMetadata(entitySlot, self);
            if (entitySlot)
            {
                entitySlot->renderQueueCalls.fetch_add(1, std::memory_order_relaxed);
                if (g_PresentObserved.load(std::memory_order_acquire))
                {
                    const uint64_t frame = g_FrameEpoch.load(std::memory_order_relaxed);
                    const uint64_t previous = entitySlot->lastRenderQueueFrame.exchange(
                        frame, std::memory_order_relaxed);
                    if (previous == frame)
                    {
                        g_DuplicateRenderQueueSameFrame.fetch_add(
                            1, std::memory_order_relaxed);
                    }
                }
            }
            RenderQueueScope scope(self);
            g_RealEntityUpdateRenderQueue(self, renderQueue);
        }

        bool __fastcall HookEntityGetCastShadows(const void* self, void*)
        {
            if (!g_OgreGetCastShadows)
                return false;

            const bool stockResult = g_OgreGetCastShadows(self);
            if (!stockResult ||
                !g_ChunkShadowPolicyEnabled.load(std::memory_order_relaxed) ||
                !self || !g_OgreEntityGetMesh || !g_OgreGetResourceName ||
                !g_OgreSetCastShadows)
            {
                return stockResult;
            }

            g_ChunkShadowQueries.fetch_add(1, std::memory_order_relaxed);
            __try
            {
                const void* meshSharedPtr = g_OgreEntityGetMesh(self);
                const void* mesh = meshSharedPtr
                    ? *reinterpret_cast<void* const*>(meshSharedPtr)
                    : nullptr;
                if (mesh && OgreProfilerAlgorithms::IsNativeTransientChunkMeshName(
                                g_OgreGetResourceName(mesh).c_str()))
                {
                    g_OgreSetCastShadows(const_cast<void*>(self), false);
                    g_ChunkShadowSuppressions.fetch_add(1, std::memory_order_relaxed);
                    return false;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                // Preserve the engine result if retail Ogre metadata is unavailable.
            }
            return stockResult;
        }

        void __fastcall HookEntityUpdateAnimationCore(void* self, void*)
        {
            FnEntityUpdateAnimation real = g_RealEntityUpdateAnimationCore
                ? g_RealEntityUpdateAnimationCore
                : reinterpret_cast<FnEntityUpdateAnimation>(g_EntityUpdateAnimationCoreDetour.trampoline);
            if (!real)
                return;
            if (!g_Enabled.load(std::memory_order_relaxed))
            {
                real(self);
                return;
            }

            const bool renderDriven = (t_RenderQueueEntity == self);
            const bool frameTracking = g_PresentObserved.load(std::memory_order_acquire);
            const uint64_t frame = frameTracking
                ? g_FrameEpoch.load(std::memory_order_relaxed)
                : 0;
            EntityProfileSlot* entitySlot = FindOrClaimEntitySlot(self);
            CaptureEntityMetadata(entitySlot, self);
            if (entitySlot && frameTracking)
            {
                const uint64_t previous =
                    entitySlot->lastAnimationFrame.exchange(frame, std::memory_order_relaxed);
                if (previous == frame)
                    g_DuplicateAnimationSameFrame.fetch_add(1, std::memory_order_relaxed);
            }

            g_AnimationCalls.fetch_add(1, std::memory_order_relaxed);
            if (renderDriven && t_SceneRenderDepth > 1)
                g_ShadowAnimationCalls.fetch_add(1, std::memory_order_relaxed);
            else if (renderDriven)
                g_MainAnimationCalls.fetch_add(1, std::memory_order_relaxed);
            BloomAdd(g_AnimationEntityBloom, self);
            const uint64_t start = ReadQpc();
            uint32_t blendCallsForAnimation = 0;
            uint64_t blendVerticesForAnimation = 0;
            {
                CurrentEntityScope scope(self);
                real(self);
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
            FnSoftwareVertexBlend real = g_RealSoftwareVertexBlend
                ? g_RealSoftwareVertexBlend
                : reinterpret_cast<FnSoftwareVertexBlend>(g_SoftwareVertexBlendDetour.trampoline);
            if (!real)
                return;
            EnsureDx11SoftwareSkinSourceShadows(sourceVertexData);
            if (!g_Enabled.load(std::memory_order_relaxed))
            {
                real(
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
            if (t_SceneRenderDepth > 1)
                g_ShadowSoftwareBlendCalls.fetch_add(1, std::memory_order_relaxed);
            else
                g_MainSoftwareBlendCalls.fetch_add(1, std::memory_order_relaxed);
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
            CaptureSourceLayout(sourceSlot, sourceVertexData);
            const uint64_t start = ReadQpc();
            {
                SoftwareBlendScope scope;
                real(
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

