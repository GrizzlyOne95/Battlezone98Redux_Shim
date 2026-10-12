// One owned, base-mesh snapshot of the selected zone. Static diagnostic only;
// no claim of live deformation, complete map coverage or tessellated relief.
unsigned g_GeometryExportTicks=0;
bool g_GeometryExportFinished=false;
FrameBridge::NativeGeometryLease g_NativeLease;
FrameBridge::NativeGeometryLeaseState g_PendingNativeLease;
bool g_NativeLeasePending=false;
uint64_t g_NativeRevision=0;
void InvalidateNativeGeometry(const char* reason)
{
    if(!g_config.geometryLive) return;
    g_NativeLease.Invalidate(); g_NativeLeasePending=false;
    if(g_GeometryExportFinished) LogShimA(LogLevel::Info,"terrain-geometry","[TERRAIN-GEOMETRY] lease invalidated revision=%llu reason=%s",g_NativeRevision,reason);
    g_GeometryExportTicks=0; g_GeometryExportFinished=false;
}
void ResetNativeGeometryExport() {
    InvalidateNativeGeometry("mission-owner-reset");
    g_GeometryExportTicks=0; g_GeometryExportFinished=false;
}

bool ReadNativeIndexBytes(void* buffer,std::vector<uint8_t>& bytes)
{
    HMODULE renderer=GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
    using GetIndex=ID3D11Buffer* (__thiscall*)(void*);
    auto get=Resolve<GetIndex>(renderer,"?getD3DIndexBuffer@D3D11HardwareIndexBuffer@Ogre@@QBEPAUID3D11Buffer@@XZ");
    const auto* vtable=GetProcAddress(renderer,"??_7D3D11HardwareIndexBuffer@Ogre@@6B@");
    if(!get||!vtable||!buffer||*static_cast<void**>(buffer)!=vtable) return false;
    bytes.resize(kExpectedIndices*2);
    ID3D11Buffer* native=get(buffer); if(!native) return false;
    ID3D11Device* device=nullptr; ID3D11DeviceContext* context=nullptr; ID3D11Buffer* staging=nullptr;
    D3D11_BUFFER_DESC desc{}; native->GetDesc(&desc);
    if(desc.ByteWidth!=kExpectedIndices*2) return false;
    native->GetDevice(&device); if(!device) return false; device->GetImmediateContext(&context);
    desc.Usage=D3D11_USAGE_STAGING; desc.BindFlags=desc.MiscFlags=desc.StructureByteStride=0; desc.CPUAccessFlags=D3D11_CPU_ACCESS_READ;
    bool result=false;
    if(context&&SUCCEEDED(device->CreateBuffer(&desc,nullptr,&staging)))
    {
        context->CopyResource(staging,native); D3D11_MAPPED_SUBRESOURCE mapped{};
        if(SUCCEEDED(context->Map(staging,0,D3D11_MAP_READ,0,&mapped)))
        {
            memcpy(bytes.data(),mapped.pData,bytes.size());
            context->Unmap(staging,0); result=true;
        }
    }
    if(staging)staging->Release(); if(context)context->Release(); device->Release(); return result;
}

void ExportNativeTerrainGeometry()
{
    if(g_config.geometryLive) {
        if(!g_NativeLease.Open(GetCurrentProcessId(),true)) return;
        if(g_NativeLease.TakeRefreshRequest()) InvalidateNativeGeometry("consumer-refresh-probe");
        if(g_NativeLeasePending&&g_NativeLease.Publish(g_PendingNativeLease)) {
            g_NativeLeasePending=false;
            LogShimA(LogLevel::Info,"terrain-geometry","[TERRAIN-GEOMETRY] lease ready revision=%llu hash=%llu validFromQpc=%llu",g_NativeRevision,g_PendingNativeLease.payloadHash,g_PendingNativeLease.validFromQpc);
        }
    }
    if(g_GeometryExportFinished||++g_GeometryExportTicks<120) return;
    g_GeometryExportFinished=true;
    try
    {
        if(g_config.tessellationTest||g_config.microReliefTest)
            throw std::runtime_error("native snapshot requires undisplaced terrain");
        if(!ResolveD3D11VertexBufferApi()) throw std::runtime_error("native DX11 buffer contract unavailable");
        std::string hash;
        if(!VerifyModuleHash(GetModuleHandleW(L"RenderSystem_Direct3D11.dll"),
            "78A1D8E13C8BD71983B09A39A3DCF7783E6C34DDE577DE3B9202460DB500AAE0",hash))
            throw std::runtime_error("native geometry renderer identity declined");
        using GetTransform=const float* (__thiscall*)(void*);
        auto transform=Resolve<GetTransform>(GetModuleHandleW(L"OgreMain.dll"),"?_getFullTransform@Node@Ogre@@UBEABVMatrix4@2@XZ");
        if(!transform) throw std::runtime_error("native full-transform API unavailable");
        FrameBridge::NativeGeometry snapshot;
        snapshot.header.producerPid=GetCurrentProcessId(); snapshot.header.missionGeneration=g_missionGeneration;
        snapshot.vertices.reserve(16*kExpectedIndices);
        nlohmann::json clusters=nlohmann::json::array();
        int zoneX=0,zoneZ=0;
        if(!SafeReadZoneInt(g_proxy.zone,kZoneXOffset,zoneX)||!SafeReadZoneInt(g_proxy.zone,kZoneZOffset,zoneZ))
            throw std::runtime_error("native selected-zone identity unavailable");
        for(int x=0;x<4;++x) for(int z=0;z<4;++z)
        {
            ClusterCandidate candidate; bool abort=false;
            if(!ResolveClusterCandidate(g_proxy.zone,zoneX,zoneZ,x,z,candidate,abort)||
                !ValidateTerrainOperation(candidate.mesh,candidate.entity,"geometry snapshot"))
                throw std::runtime_error("native snapshot requires all sixteen selected-zone clusters");
            RenderOperation operation{}; void* sub=nullptr; void* positions=nullptr; void* heights=nullptr;
            if(!GetEntityOperation(candidate.entity,operation,sub)||operation.vertexData->vertexStart||operation.indexData->indexStart||
                !GetVertexBuffer(operation,0,positions)||!GetVertexBuffer(operation,2,heights))
                throw std::runtime_error("native snapshot stream ranges unsupported");
            if(!g_ogre.findElementBySemantic||!g_ogre.getElementSource||!g_ogre.getElementType||!g_ogre.getElementOffset)
                throw std::runtime_error("native declaration API unavailable");
            const void* positionElement=g_ogre.findElementBySemantic(operation.vertexData->declaration,1,0);
            const void* heightElement=g_ogre.findElementBySemantic(operation.vertexData->declaration,7,1);
            const int positionType=positionElement?g_ogre.getElementType(positionElement):-1;
            if(!positionElement||!heightElement||g_ogre.getElementSource(positionElement)!=0||g_ogre.getElementOffset(positionElement)!=0||
                (positionType!=2&&positionType!=3)||g_ogre.getElementSource(heightElement)!=2||g_ogre.getElementOffset(heightElement)!=0||g_ogre.getElementType(heightElement)!=0)
                throw std::runtime_error("native position/height declaration unsupported");
            std::vector<uint8_t> positionBytes,heightBytes,indexBytes;
            if(!ReadD3D11VertexBuffer(positions,kExpectedVertices*16,positionBytes)||
                !ReadD3D11VertexBuffer(heights,kExpectedVertices*4,heightBytes)||
                !ReadNativeIndexBytes(operation.indexData->indexBuffer.rep,indexBytes))
                throw std::runtime_error("native snapshot readback failed");
            const float* matrix=transform(candidate.node);
            if(!matrix||matrix[12]!=0||matrix[13]!=0||matrix[14]!=0||matrix[15]!=1)
                throw std::runtime_error("native snapshot affine node transform unavailable");
            for(unsigned i=0;i<16;++i) if(!std::isfinite(matrix[i])) throw std::runtime_error("nonfinite native transform");
            float minY=100000,maxY=-100000;
            for(unsigned i=0;i<kExpectedIndices;++i)
            {
                uint16_t index; memcpy(&index,indexBytes.data()+i*2,2);
                if(index>=kExpectedVertices) throw std::runtime_error("native index outside source vertex range");
                float p[4],height; memcpy(p,positionBytes.data()+index*16,16); memcpy(&height,heightBytes.data()+index*4,4);
                if(positionType==2) p[3]=1; // D3D IA float3 -> shader float4 supplies W=1.
                // The released terrain VS replaces object Y with TEXCOORD1.
                p[1]=height;
                if(p[3]!=1) throw std::runtime_error("native position W contract unsupported");
                FrameBridge::NativePoint world{matrix[0]*p[0]+matrix[1]*p[1]+matrix[2]*p[2]+matrix[3],
                    matrix[4]*p[0]+matrix[5]*p[1]+matrix[6]*p[2]+matrix[7],
                    matrix[8]*p[0]+matrix[9]*p[1]+matrix[10]*p[2]+matrix[11]};
                if(!std::isfinite(world.x)||!std::isfinite(world.y)||!std::isfinite(world.z)||
                    std::abs(world.x)>100000||std::abs(world.y)>100000||std::abs(world.z)>100000)
                    throw std::runtime_error("native transformed vertex outside finite world bounds");
                minY=(std::min)(minY,world.y); maxY=(std::max)(maxY,world.y); snapshot.vertices.push_back(world);
            }
            ++snapshot.header.clusters;
            clusters.push_back({{"mesh",candidate.meshName},{"zone",{zoneX,zoneZ}},{"cluster",{x,z}},
                {"worldTransform",std::vector<float>(matrix,matrix+16)},{"minimumY",minY},{"maximumY",maxY}});
        }
        const uint64_t revision=g_config.geometryLive?++g_NativeRevision:0;
        const auto path=std::filesystem::path(g_config.geometryExport+(g_config.geometryLive?".g"+std::to_string(revision)+".bin":""));
        if(!path.is_absolute()||std::filesystem::exists(path)||std::filesystem::exists(path.string()+".json")) throw std::runtime_error("native snapshot needs a new absolute output path");
        std::ofstream out(path,std::ios::binary); FrameBridge::WriteNativeGeometry(out,snapshot); out.close();
        nlohmann::json report={{"schema","bzr-native-terrain-snapshot-v1"},{"pid",GetCurrentProcessId()},
            {"missionGeneration",g_missionGeneration},{"clusters",clusters},{"vertices",snapshot.vertices.size()},
            {"triangles",snapshot.vertices.size()/3},{"worldSpace",true},{"heightStreamSlot",2},
            {"baseNativeGeometryOnly",true},{"liveUpdatesQualified",false},{"fullMapCoverage",false},
            {"offscreenNativeClustersIncluded",true},{"payloadHash",FrameBridge::GeometryHash(snapshot.vertices)}};
        std::ofstream metadata(path.string()+".json"); metadata<<report.dump(2)<<'\n';
        if(!metadata) throw std::runtime_error("native snapshot metadata write failed");
        metadata.close();
        if(g_config.geometryLive) {
            LARGE_INTEGER now{},frequency{}; QueryPerformanceCounter(&now); QueryPerformanceFrequency(&frequency);
            g_PendingNativeLease={}; g_PendingNativeLease.producerPid=GetCurrentProcessId();
            g_PendingNativeLease.missionGeneration=g_missionGeneration; g_PendingNativeLease.revision=revision;
            g_PendingNativeLease.payloadHash=FrameBridge::GeometryHash(snapshot.vertices);
            g_PendingNativeLease.validFromQpc=static_cast<uint64_t>(now.QuadPart); g_PendingNativeLease.qpcFrequency=static_cast<uint64_t>(frequency.QuadPart);
            g_PendingNativeLease.triangles=static_cast<uint32_t>(snapshot.vertices.size()/3); g_NativeLeasePending=true;
        }
        LogShimA(LogLevel::Info,"terrain-geometry","[TERRAIN-GEOMETRY] snapshot exported clusters=%u vertices=%zu triangles=%zu generation=%u baseNative=1 worldSpace=1 path=\"%s\"",snapshot.header.clusters,snapshot.vertices.size(),snapshot.vertices.size()/3,g_missionGeneration,path.string().c_str());
    }
    catch(const std::exception& error) { LogShimA(LogLevel::Warn,"terrain-geometry","[TERRAIN-GEOMETRY] snapshot declined: %s",error.what()); }
    catch(...) { LogShimA(LogLevel::Warn,"terrain-geometry","[TERRAIN-GEOMETRY] snapshot declined after native exception"); }
}
