// Bounded scene inventory on the existing game-thread terrain render callback.
// Exported accessors only; no container ABI traversal or retained engine owners.
struct GeometryEntityApi
{
    using Ptr=void* (__thiscall*)(void*);
    using Index=void* (__thiscall*)(void*,uint16_t);
    using Count=uint16_t (__thiscall*)(void*);
    using UInt=uint32_t (__thiscall*)(void*);
    using Bool=bool (__thiscall*)(void*);
    using Int=int (__thiscall*)(void*);
    using Text=const std::string* (__thiscall*)(void*);
    using Shared=const OgreSharedPtr* (__thiscall*)(void*);
    using Transform=const float* (__thiscall*)(void*);
    using World=void (__thiscall*)(void*,float*);
    Ptr root=nullptr; Index child=nullptr,attached=nullptr;
    Count children=nullptr,attachments=nullptr,animations=nullptr,worldCount=nullptr;
    UInt subCount=nullptr; Bool skeleton=nullptr,visible=nullptr,casts=nullptr,depthWrite=nullptr;
    Shared mesh=nullptr,material=nullptr; Text name=nullptr,program=nullptr;
    Ptr technique=nullptr; Bool hardwareAnimation=nullptr; World world=nullptr;
    Int sourceBlend=nullptr,destBlend=nullptr,alphaFunction=nullptr;
    Transform transform=nullptr; const void* entityVtable=nullptr;
} g_GeometryEntities;
bool BindGeometryEntities()
{
    static const bool bound=[] {
        auto module=GetModuleHandleW(L"OgreMain.dll"); std::string hash;
        if(!VerifyModuleHash(module,kExpectedOgreSha256,hash)) return false;
        auto& a=g_GeometryEntities;
#define GEOMETRY_API(field,exportName) a.field=Resolve<decltype(a.field)>(module,exportName)
        GEOMETRY_API(root,"?getRootSceneNode@SceneManager@Ogre@@UAEPAVSceneNode@2@XZ");
        GEOMETRY_API(child,"?getChild@Node@Ogre@@UBEPAV12@G@Z");
        GEOMETRY_API(attached,"?getAttachedObject@SceneNode@Ogre@@UAEPAVMovableObject@2@G@Z");
        GEOMETRY_API(children,"?numChildren@Node@Ogre@@UBEGXZ");
        GEOMETRY_API(attachments,"?numAttachedObjects@SceneNode@Ogre@@UBEGXZ");
        GEOMETRY_API(animations,"?getNumAnimations@Mesh@Ogre@@UBEGXZ");
        GEOMETRY_API(worldCount,"?getNumWorldTransforms@SubEntity@Ogre@@UBEGXZ");
        GEOMETRY_API(world,"?getWorldTransforms@SubEntity@Ogre@@UBEXPAVMatrix4@2@@Z");
        GEOMETRY_API(technique,"?getTechnique@SubEntity@Ogre@@UBEPAVTechnique@2@XZ");
        GEOMETRY_API(hardwareAnimation,"?isHardwareAnimationEnabled@Entity@Ogre@@QAE_NXZ");
        GEOMETRY_API(subCount,"?getNumSubEntities@Entity@Ogre@@QBEIXZ");
        GEOMETRY_API(skeleton,"?hasSkeleton@Entity@Ogre@@QBE_NXZ");
        GEOMETRY_API(visible,"?isVisible@MovableObject@Ogre@@UBE_NXZ");
        GEOMETRY_API(casts,"?getCastShadows@MovableObject@Ogre@@UBE_NXZ");
        GEOMETRY_API(mesh,"?getMesh@Entity@Ogre@@QBEABV?$SharedPtr@VMesh@Ogre@@@2@XZ");
        GEOMETRY_API(material,"?getMaterial@SubEntity@Ogre@@UBEABV?$SharedPtr@VMaterial@Ogre@@@2@XZ");
        GEOMETRY_API(name,"?getName@MovableObject@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
        GEOMETRY_API(program,"?getVertexProgramName@Pass@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
        GEOMETRY_API(sourceBlend,"?getSourceBlendFactor@Pass@Ogre@@QBE?AW4SceneBlendFactor@2@XZ");
        GEOMETRY_API(destBlend,"?getDestBlendFactor@Pass@Ogre@@QBE?AW4SceneBlendFactor@2@XZ");
        GEOMETRY_API(alphaFunction,"?getAlphaRejectFunction@Pass@Ogre@@QBE?AW4CompareFunction@2@XZ");
        GEOMETRY_API(depthWrite,"?getDepthWriteEnabled@Pass@Ogre@@QBE_NXZ");
        GEOMETRY_API(transform,"?_getFullTransform@Node@Ogre@@UBEABVMatrix4@2@XZ");
#undef GEOMETRY_API
        a.entityVtable=GetProcAddress(module,"??_7Entity@Ogre@@6BShadowCaster@1@@");
        return a.root&&a.child&&a.attached&&a.children&&a.attachments&&a.animations&&a.subCount&&a.skeleton&&
            a.visible&&a.casts&&a.mesh&&a.material&&a.name&&a.program&&a.sourceBlend&&a.destBlend&&a.alphaFunction&&a.depthWrite&&a.transform&&a.entityVtable&&
            a.worldCount&&a.world&&a.technique&&a.hardwareAnimation;
    }(); return bound;
}
void* GeometrySceneRoot(uintptr_t slot)
{
    __try {
        auto* globals=slot?*reinterpret_cast<uint8_t**>(slot):nullptr;
        void* manager=globals?*reinterpret_cast<void**>(globals+8):nullptr;
        return manager?g_GeometryEntities.root(manager):nullptr;
    } __except(EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
}
bool GeometryNodeLinks(void* node,uint16_t& children,uint16_t& attached)
{
    __try { children=g_GeometryEntities.children(node); attached=g_GeometryEntities.attachments(node); return children<=4096&&attached<=256; }
    __except(EXCEPTION_EXECUTE_HANDLER) { return false; }
}
void* GeometryNodeItem(GeometryEntityApi::Index getter,void* node,uint16_t index)
{
    __try { return getter(node,index); } __except(EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
}
bool GeometryIsEntity(void* object)
{
    __try { return object&&*static_cast<const void**>(object)==g_GeometryEntities.entityVtable; }
    __except(EXCEPTION_EXECUTE_HANDLER) { return false; }
}
// General index readback uses the qualified native DX11 buffer class. All
// foreign/COM reads live in a SEH leaf; no failed COM state is touched on fault.
using GeometryIndexGet=ID3D11Buffer* (__thiscall*)(void*);
__declspec(noinline) bool GuardedGeometryIndexRead(void* buffer,GeometryIndexGet get,const void* table,unsigned char* bytes,uint32_t size)
{
    ID3D11Device* device=nullptr; ID3D11DeviceContext* context=nullptr; ID3D11Buffer* staging=nullptr;
    bool success=false,mapped=false;
    __try {
        do {
            if(!buffer||!get||!table||*static_cast<const void**>(buffer)!=table) break;
            ID3D11Buffer* source=get(buffer); if(!source) break;
            D3D11_BUFFER_DESC desc{}; source->GetDesc(&desc);
            if(desc.ByteWidth<size||desc.ByteWidth>32*1024*1024) break;
            source->GetDevice(&device); if(!device) break; device->GetImmediateContext(&context); if(!context) break;
            desc.Usage=D3D11_USAGE_STAGING; desc.BindFlags=desc.MiscFlags=desc.StructureByteStride=0; desc.CPUAccessFlags=D3D11_CPU_ACCESS_READ;
            if(FAILED(device->CreateBuffer(&desc,nullptr,&staging))||!staging) break;
            context->CopyResource(staging,source); D3D11_MAPPED_SUBRESOURCE data{};
            if(FAILED(context->Map(staging,0,D3D11_MAP_READ,0,&data))||!data.pData) break;
            mapped=true; memcpy(bytes,data.pData,size); success=true;
        } while(false);
        if(mapped)context->Unmap(staging,0); if(staging)staging->Release(); if(context)context->Release(); if(device)device->Release();
    } __except(EXCEPTION_EXECUTE_HANDLER) { return false; }
    return success;
}
bool ReadGeometryIndices(void* buffer,uint32_t size,std::vector<unsigned char>& bytes)
{
    if(!size||size>32*1024*1024) return false;
    HMODULE renderer=GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
    auto get=Resolve<GeometryIndexGet>(renderer,"?getD3DIndexBuffer@D3D11HardwareIndexBuffer@Ogre@@QBEPAUID3D11Buffer@@XZ");
    const auto* table=GetProcAddress(renderer,"??_7D3D11HardwareIndexBuffer@Ogre@@6B@");
    bytes.resize(size); return GuardedGeometryIndexRead(buffer,get,table,bytes.data(),size);
}
bool GeometryBuildingMaterial(void* sub,nlohmann::json& observation)
{
    auto& a=g_GeometryEntities; void* technique=a.technique(sub);
    if(!technique) throw std::runtime_error("building active technique unavailable");
    if(g_ogre.getNumPasses(technique)!=1) throw std::runtime_error("building active technique must have one pass");
    void* pass=g_ogre.getPass(technique,0);
    if(!pass||a.sourceBlend(pass)!=0||a.destBlend(pass)!=1||a.alphaFunction(pass)!=1||!a.depthWrite(pass)) throw std::runtime_error("building active pass is not unblended depth-writing always-pass alpha");
    if((g_ogre.hasHullProgram&&g_ogre.hasHullProgram(pass))||(g_ogre.hasDomainProgram&&g_ogre.hasDomainProgram(pass))) throw std::runtime_error("building tessellation unsupported");
    const auto* program=g_ogre.getVertexProgram(pass);
    if(!program||!program->rep||!g_ogre.getProgramSource||!g_ogre.getUnifiedDelegate) throw std::runtime_error("building vertex program/source APIs unavailable");
    const auto* source=g_ogre.getProgramSource(program->rep);
    if(!source||source->empty()) {
        program=g_ogre.getUnifiedDelegate(program->rep);
        if(!program||!program->rep) throw std::runtime_error("building vertex delegate unavailable");
        source=g_ogre.getProgramSource(program->rep);
    }
    const auto* name=g_ogre.getResourceName(program->rep);
    if(!source||source->size()>2*1024*1024||!name||name->size()>256) throw std::runtime_error("building source/name bounds declined");
    if((name->find("Base")!=0&&name->find("OSE_Base")!=0)||name->find("_vertexHLSL4")==std::string::npos)
        throw std::runtime_error("building requires a base HLSL4 vertex delegate: "+*name);
    std::string compact;
    for(unsigned char character:*source) if(character!=' '&&character!='\t'&&character!='\r'&&character!='\n') compact.push_back(static_cast<char>(character));
    if(compact.find("oPosition=mul(wvpMat,iPosition);")==std::string::npos) throw std::runtime_error("building base position source expression declined: "+*name);
    observation={{"resolvedVertexProgram",*name},{"basePositionSourceObserved",true},{"depthWrite",true},
        {"sourceBlend",0},{"destBlend",1},{"alphaFunction",1},{"foreignMaterialQualified",false}};
    return true;
}
void CaptureGeometryBuilding(void* entity,void* sub,FrameBridge::NativeGeometry& casters,nlohmann::json& observation)
{
    auto& a=g_GeometryEntities;
    if(a.hardwareAnimation(entity)||a.worldCount(sub)!=1) throw std::runtime_error("building requires software pose and one world transform");
    if(!GeometryBuildingMaterial(sub,observation)) throw std::runtime_error("building material position/opacity contract declined");
    RenderOperation op{}; g_ogre.getRenderOperation(sub,op);
    if(!op.vertexData||!op.indexData||!op.useIndexes||op.operationType!=4||op.numberOfInstances>1||op.renderToVertexBuffer||op.globalInstancingAvailable)
        throw std::runtime_error("building draw operation unsupported");
    const void* position=g_ogre.findElementBySemantic(op.vertexData->declaration,1,0);
    if(!position) throw std::runtime_error("building position declaration absent");
    const int type=g_ogre.getElementType(position); if(type!=2&&type!=3) throw std::runtime_error("building requires FLOAT3/FLOAT4 position");
    void* buffer=nullptr; if(!GetVertexBuffer(op,g_ogre.getElementSource(position),buffer)) throw std::runtime_error("building position buffer absent");
    FrameBridge::NativeIndexedMesh draw;
    draw.stride=g_ogre.getVertexSize(buffer); draw.positionOffset=g_ogre.getElementOffset(position); draw.positionFloats=type==2?3:4;
    draw.vertexStart=op.vertexData->vertexStart; draw.vertexCount=op.vertexData->vertexCount;
    draw.indexStart=op.indexData->indexStart; draw.indexCount=op.indexData->indexCount;
    draw.indexBytes=g_ogre.getIndexSize(op.indexData->indexBuffer.rep);
    a.world(sub,draw.world); // Exact transform used by this renderable, not inferred from its scene node.
    const uint64_t vbBytes=(uint64_t(draw.vertexStart)+draw.vertexCount)*draw.stride;
    const uint64_t ibBytes=(uint64_t(draw.indexStart)+draw.indexCount)*draw.indexBytes;
    if(!vbBytes||!ibBytes||vbBytes>32*1024*1024||ibBytes>32*1024*1024||casters.header.clusters>=256||
        casters.vertices.size()+draw.indexCount>1000000) throw std::runtime_error("building geometry budget/range declined");
    std::vector<unsigned char> vertices,indices;
    if(!ReadD3D11VertexBuffer(buffer,static_cast<uint32_t>(vbBytes),vertices)||
        !ReadGeometryIndices(op.indexData->indexBuffer.rep,static_cast<uint32_t>(ibBytes),indices)) throw std::runtime_error("building native buffer readback declined");
    auto points=FrameBridge::DecodeNativeIndexedMesh(draw,vertices,indices);
    casters.vertices.insert(casters.vertices.end(),points.begin(),points.end()); ++casters.header.clusters;
    observation["vertices"]=draw.vertexCount; observation["indices"]=draw.indexCount; observation["triangles"]=draw.indexCount/3;
    observation["worldTransform"]=std::vector<float>(draw.world,draw.world+16); observation["positionStride"]=draw.stride;
    observation["vertexStart"]=draw.vertexStart; observation["indexStart"]=draw.indexStart; observation["indexBytes"]=draw.indexBytes;
    observation["softwarePose"]=true;
    observation["hardwareAnimationEnabled"]=false; observation["worldTransformCount"]=1;
}
void ExportGeometryEntityInventoryBody(const std::filesystem::path& geometryPath)
{
    try {
        if(!BindGeometryEntities()) throw std::runtime_error("entity inventory exported API contract unavailable");
        void* root=GeometrySceneRoot(EngineGlobals::RenderGlobals());
        if(!root) throw std::runtime_error("entity inventory scene root unavailable");
        std::vector<void*> pending{root}; std::set<void*> visited,entities;
        nlohmann::json rows=nlohmann::json::array();
        FrameBridge::NativeGeometry casters; casters.header.producerPid=GetCurrentProcessId(); casters.header.missionGeneration=g_missionGeneration;
        auto casterRows=nlohmann::json::array();
        while(!pending.empty()) {
            void* node=pending.back(); pending.pop_back();
            if(!node||!visited.insert(node).second||visited.size()>8192) throw std::runtime_error("entity inventory graph bound/cycle");
            uint16_t children=0,attached=0;
            if(!GeometryNodeLinks(node,children,attached)) throw std::runtime_error("entity inventory node links declined");
            for(uint16_t i=0;i<children;++i) pending.push_back(GeometryNodeItem(g_GeometryEntities.child,node,i));
            for(uint16_t i=0;i<attached;++i) {
                void* entity=GeometryNodeItem(g_GeometryEntities.attached,node,i);
                if(!GeometryIsEntity(entity)||!entities.insert(entity).second) continue;
                if(entities.size()>2048) throw std::runtime_error("entity inventory count bound");
                auto& a=g_GeometryEntities;
                const auto* mesh=a.mesh(entity); if(!mesh||!mesh->rep) throw std::runtime_error("entity inventory mesh unavailable");
                const auto* name=a.name(entity); const auto* meshName=g_ogre.getResourceName(mesh->rep);
                if(!name||!meshName||name->size()>256||meshName->size()>256) throw std::runtime_error("entity inventory name bounds");
                const unsigned count=a.subCount(entity); if(count>64) throw std::runtime_error("entity inventory subentity bound");
                const float* matrix=a.transform(node); if(!matrix) throw std::runtime_error("entity inventory transform unavailable");
                nlohmann::json row={{"name",*name},{"mesh",*meshName},{"skeleton",a.skeleton(entity)},{"animations",a.animations(mesh->rep)},
                    {"visible",a.visible(entity)},{"castsShadows",a.casts(entity)},{"transform",std::vector<float>(matrix,matrix+16)}};
                auto subRows=nlohmann::json::array();
                const bool building=g_config.geometryBuildings&&a.visible(entity)&&a.casts(entity)&&a.animations(mesh->rep)==0&&
                    (meshName->rfind("ab",0)==0||meshName->rfind("sb",0)==0);
                for(unsigned subIndex=0;subIndex<count;++subIndex) {
                    void* sub=g_ogre.getSubEntity(entity,subIndex); if(!sub) throw std::runtime_error("entity inventory subentity unavailable");
                    RenderOperation op{}; g_ogre.getRenderOperation(sub,op);
                    const auto* material=a.material(sub);
                    nlohmann::json subRow={{"material",*g_ogre.getMaterialName(sub)},{"topology",op.operationType},{"indexed",op.useIndexes!=0},
                        {"instances",op.numberOfInstances},{"vertices",op.vertexData?op.vertexData->vertexCount:0},{"vertexStart",op.vertexData?op.vertexData->vertexStart:0},
                        {"indices",op.indexData?op.indexData->indexCount:0},{"indexStart",op.indexData?op.indexData->indexStart:0}};
                    if(op.vertexData) {
                        const void* position=g_ogre.findElementBySemantic(op.vertexData->declaration,1,0);
                        if(position) {
                            const auto source=g_ogre.getElementSource(position); void* buffer=nullptr;
                            subRow["positionType"]=g_ogre.getElementType(position); subRow["positionSource"]=source; subRow["positionOffset"]=g_ogre.getElementOffset(position);
                            if(GetVertexBuffer(op,source,buffer)) subRow["positionStride"]=g_ogre.getVertexSize(buffer);
                        }
                    }
                    auto techniques=nlohmann::json::array();
                    if(material&&material->rep) for(unsigned t=0;t<g_ogre.getNumTechniques(material->rep)&&t<32;++t) {
                        void* technique=g_ogre.getTechnique(material->rep,static_cast<uint16_t>(t)); auto passes=nlohmann::json::array();
                        for(unsigned p=0;p<g_ogre.getNumPasses(technique)&&p<8;++p) {
                            void* pass=g_ogre.getPass(technique,static_cast<uint16_t>(p));
                            passes.push_back({{"vertexProgram",*a.program(pass)},{"sourceBlend",a.sourceBlend(pass)},{"destBlend",a.destBlend(pass)},
                                {"alphaFunction",a.alphaFunction(pass)},{"depthWrite",a.depthWrite(pass)}});
                        } techniques.push_back(passes);
                    }
                    subRow["techniques"]=techniques; subRows.push_back(subRow);
                    if(building) {
                        nlohmann::json captured;
                        try {
                            CaptureGeometryBuilding(entity,sub,casters,captured);
                            captured["name"]=*name; captured["mesh"]=*meshName; captured["subentity"]=subIndex; captured["material"]=*g_ogre.getMaterialName(sub);
                            casterRows.push_back(captured);
                        } catch(const std::exception& error) { row["buildingDeclined"]=error.what(); }
                    }
                }
                row["subentities"]=subRows; rows.push_back(row);
            }
        }
        const auto path=geometryPath.string()+".entities.json";
        if(std::filesystem::exists(path)) throw std::runtime_error("entity inventory needs new path");
        nlohmann::json report={{"schema","bzr-native-entity-inventory-v1"},{"pid",GetCurrentProcessId()},{"missionGeneration",g_missionGeneration},
            {"nodes",visited.size()},{"entities",rows},{"geometryQualified",false},{"staticLifetimeQualified",false}};
        std::ofstream out(path); out<<report.dump(2)<<'\n'; if(!out) throw std::runtime_error("entity inventory write failed");
        LogShimA(LogLevel::Info,"terrain-geometry","[NATIVE-ENTITIES] inventory nodes=%zu entities=%zu path=\"%s\"",visited.size(),rows.size(),path.c_str());
        if(g_config.geometryBuildings) {
            if(casters.vertices.empty()) throw std::runtime_error("no building submeshes met snapshot contract");
            const auto buildingPath=geometryPath.string()+".buildings.bin";
            if(std::filesystem::exists(buildingPath)||std::filesystem::exists(buildingPath+".json")) throw std::runtime_error("building snapshot needs new path");
            std::ofstream binary(buildingPath,std::ios::binary); FrameBridge::WriteNativeGeometry(binary,casters); binary.close();
            LARGE_INTEGER now{}; QueryPerformanceCounter(&now);
            nlohmann::json buildingReport={{"schema","bzr-building-pose-snapshot-v1"},{"pid",GetCurrentProcessId()},{"missionGeneration",g_missionGeneration},
                {"observationQpc",now.QuadPart},{"vertices",casters.vertices.size()},{"triangles",casters.vertices.size()/3},
                {"submeshes",casterRows},{"payloadHash",FrameBridge::GeometryHash(casters.vertices)},
                {"worldSpace",true},{"snapshotPoseOnly",true},{"liveLifetimeQualified",false},{"foreignMaterialQualified",false}};
            std::ofstream metadata(buildingPath+".json"); metadata<<buildingReport.dump(2)<<'\n'; if(!metadata) throw std::runtime_error("building snapshot metadata write failed");
            LogShimA(LogLevel::Info,"terrain-geometry","[NATIVE-ENTITIES] building snapshot submeshes=%zu triangles=%zu path=\"%s\"",casterRows.size(),casters.vertices.size()/3,buildingPath.c_str());
        }
    } catch(const std::exception& error) { LogShimA(LogLevel::Warn,"terrain-geometry","[NATIVE-ENTITIES] inventory declined: %s",error.what()); }
      catch(...) { LogShimA(LogLevel::Warn,"terrain-geometry","[NATIVE-ENTITIES] inventory declined after native exception"); }
}
// Foreign reads run on the game thread under exact module/vtable guards. An
// unexpected access violation must never escape into the game's render loop.
// This leaf has no C++ owners. /EHsc cannot unwind the body on SEH: decline and
// disable inventory for the session rather than touching unknown foreign state
// or retrying/leaking repeatedly. Ordinary C++ errors are handled in the body.
bool g_GeometryEntityInventoryFaulted=false;
__declspec(noinline) bool GuardedGeometryEntityInventory(const std::filesystem::path& path)
{
    __try { ExportGeometryEntityInventoryBody(path); return true; }
    __except(EXCEPTION_EXECUTE_HANDLER) { return false; }
}
void ExportGeometryEntityInventory(const std::filesystem::path& path)
{
    if(g_GeometryEntityInventoryFaulted) return;
    if(!GuardedGeometryEntityInventory(path)) {
        g_GeometryEntityInventoryFaulted=true;
        LogShimA(LogLevel::Warn,"terrain-geometry","[NATIVE-ENTITIES] inventory disabled after guarded native fault");
    }
}
