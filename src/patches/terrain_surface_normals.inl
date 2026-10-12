// Guarded authored RGB normal atlas. Height art affects lighting only here;
// domain-stage height texture binding is intentionally not implemented.
struct TerrainSurfacePass { uint16_t technique,pass; OgreSharedPtr original; };
std::vector<TerrainSurfacePass> g_SurfacePasses;
OgreSharedPtr g_SurfaceTexture;
std::string g_SurfaceMaterial;
void* g_SurfaceMaterialIdentity=nullptr;

void RestoreNativeTerrainSurface()
{
    unsigned restored=0;
    OgreSharedPtr material;
    try
    {
        if(!g_SurfaceMaterial.empty()&&GetModuleHandleW(L"OgreMain.dll"))
        {
            g_ogre.getMaterialByName(g_ogre.getMaterialManager(),&material,g_SurfaceMaterial,std::string("Autodetect"));
            if(material.rep==g_SurfaceMaterialIdentity)
            for(auto& entry:g_SurfacePasses)
            {
                if(entry.technique>=g_ogre.getNumTechniques(material.rep)) continue;
                void* technique=g_ogre.getTechnique(material.rep,entry.technique);
                if(!technique||entry.pass>=g_ogre.getNumPasses(technique)) continue;
                void* pass=g_ogre.getPass(technique,entry.pass);
                if(g_ogre.getNumTextureUnitStates(pass)<=2) continue;
                void* unit=g_ogre.getTextureUnitState(pass,2);
                const auto* current=g_hdGetTexture(unit);
                if(current&&current->rep==g_SurfaceTexture.rep)
                { g_ogre.setTexture(unit,entry.original); ++restored; }
            }
        }
    }
    catch(...) { LogShimA(LogLevel::Warn,"terrain-surface","[TERRAIN-SURFACE] normal restoration declined"); }
    if(!g_SurfacePasses.empty())
        LogShimA(LogLevel::Info,"terrain-surface","[TERRAIN-SURFACE] normals restored passes=%u tracked=%zu",restored,g_SurfacePasses.size());
    ReleaseCloneHandoff(material);
    for(auto& entry:g_SurfacePasses) ReleaseCloneHandoff(entry.original);
    g_SurfacePasses.clear(); ReleaseCloneHandoff(g_SurfaceTexture);
    g_SurfaceMaterial.clear(); g_SurfaceMaterialIdentity=nullptr;
}

bool InstallNativeTerrainSurface()
{
    if(g_config.surfaceManifest.empty()||!g_SurfacePasses.empty()) return false;
    OgreSharedPtr material,texture;
    try
    {
        ResolveNativeHdApi();
        std::string hash;
        if(!VerifyModuleHash(GetModuleHandleW(L"RenderSystem_Direct3D11.dll"),
            "78A1D8E13C8BD71983B09A39A3DCF7783E6C34DDE577DE3B9202460DB500AAE0",hash))
            throw std::runtime_error("surface renderer identity declined");
        std::ifstream stream(ResolveHdManifestPath(g_config.surfaceManifest),std::ios::binary);
        std::string text((std::istreambuf_iterator<char>(stream)),{});
        if(text.empty()||text.size()>65536) throw std::runtime_error("surface manifest missing/oversized");
        const auto spec=nlohmann::json::parse(text);
        if(spec.value("schema",std::string())!="bzr-openshim-terrain-surface-v1"||
            spec.value("normalEncoding",std::string())!="rgb-xyz-linear"||
            spec.value("heightUsage",std::string())!="normal-lighting-only")
            throw std::runtime_error("surface schema/encoding/height contract declined");
        if(spec.contains("heightAtlas")||!spec.at("width").is_number_unsigned()||!spec.at("height").is_number_unsigned())
            throw std::runtime_error("surface geometry heights/invalid dimension types unsupported");
        const auto sourceDiffuse=spec.at("sourceDiffuseResource").get<std::string>();
        const auto sourceNormal=spec.at("sourceNormalResource").get<std::string>();
        const auto resource=spec.at("normalAtlas").get<std::string>();
        const auto width=spec.at("width").get<unsigned>(),height=spec.at("height").get<unsigned>();
        if(resource.empty()||resource.size()>255||resource.find_first_of("/\\:")!=std::string::npos||
            sourceDiffuse.empty()||sourceNormal.empty()||width<64||height<64||width>8192||height>8192)
            throw std::runtime_error("surface resource/dimensions invalid");
        RenderOperation operation{}; void* sub=nullptr;
        if(!GetEntityOperation(g_proxy.sourceEntity,operation,sub)) throw std::runtime_error("surface terrain source missing");
        const auto* name=g_ogre.getMaterialName(sub);
        if(!name||*name!=spec.at("material").get<std::string>()) throw std::runtime_error("surface material identity mismatch");
        g_ogre.getMaterialByName(g_ogre.getMaterialManager(),&material,*name,std::string("Autodetect"));
        if(!material.rep) throw std::runtime_error("surface material unavailable");
        for(uint16_t t=0;t<g_ogre.getNumTechniques(material.rep);++t)
        for(uint16_t p=0;p<g_ogre.getNumPasses(g_ogre.getTechnique(material.rep,t));++p)
        {
            void* pass=g_ogre.getPass(g_ogre.getTechnique(material.rep,t),p);
            if(g_ogre.getNumTextureUnitStates(pass)<=2) continue;
            const auto* program=g_ogre.getFragmentProgram(pass);
            if(!program||!program->rep) continue;
            const auto* code=g_ogre.getProgramSource(program->rep);
            if(!code||code->empty()) { program=g_ogre.getUnifiedDelegate(program->rep); if(!program||!program->rep) continue; code=g_ogre.getProgramSource(program->rep); }
            std::string defines,target,entry;
            g_ogre.getStringParameter(program->rep,&defines,std::string("preprocessor_defines"));
            g_ogre.getStringParameter(program->rep,&target,std::string("target"));
            g_ogre.getStringParameter(program->rep,&entry,std::string("entry_point"));
            if(!code||target.rfind("ps_4",0)!=0||entry!="terrain_fragment"||defines.find("NORMALMAP_ENABLED")==std::string::npos||
                defines.find("VERTEX_LIGHTING")!=std::string::npos||defines.find("OSE_TERRAIN_NORMAL_UNPACK_MODE")!=std::string::npos||
                defines.find("RETRO_UNLIT_MODE")!=std::string::npos||defines.find("OSE_TERRAIN_NORMAL_BASIS_MODE")!=std::string::npos||
                defines.find("OSE_TERRAIN_NORMAL_FLIP_GREEN")!=std::string::npos||
                code->find("uniform Texture2D normalMap : register(t2),")==std::string::npos||
                code->find("normalMap.Sample(normalSam, vTexCoord)")==std::string::npos) continue;
            const auto* diffuse=g_hdGetTextureName(g_ogre.getTextureUnitState(pass,0));
            const auto* normal=g_hdGetTextureName(g_ogre.getTextureUnitState(pass,2));
            if(!diffuse||!normal||*diffuse!=sourceDiffuse||*normal!=sourceNormal) continue;
            const auto* original=g_hdGetTexture(g_ogre.getTextureUnitState(pass,2));
            if(!original||!original->rep||!AddSharedReference(*original)) throw std::runtime_error("surface original ownership unavailable");
            try { g_SurfacePasses.push_back({t,p,*original}); }
            catch(...) { auto owned=*original; ReleaseCloneHandoff(owned); throw; }
        }
        if(g_SurfacePasses.empty()) throw std::runtime_error("no guarded normal-mapped terrain pass");
        if(!LoadTerrainHdSourceTexture(g_ogre.getTextureManager(),resource,texture)||!g_ogre.getD3D11Texture2D)
            throw std::runtime_error("surface texture unavailable");
        ID3D11Texture2D* native=g_ogre.getD3D11Texture2D(texture.rep);
        D3D11_TEXTURE2D_DESC desc{}; if(native) native->GetDesc(&desc);
        if(!native||desc.Width!=width||desc.Height!=height||desc.ArraySize!=1||desc.SampleDesc.Count!=1||
            (desc.Format!=DXGI_FORMAT_R8G8B8A8_UNORM&&desc.Format!=DXGI_FORMAT_B8G8R8A8_UNORM))
            throw std::runtime_error("surface needs matching linear RGBA8 2D texture");
        g_SurfaceMaterial=*name; g_SurfaceMaterialIdentity=material.rep;
        g_SurfaceTexture=texture; texture={};
        for(const auto& saved:g_SurfacePasses)
            g_ogre.setTexture(g_ogre.getTextureUnitState(g_ogre.getPass(g_ogre.getTechnique(material.rep,saved.technique),saved.pass),2),g_SurfaceTexture);
        LogShimA(LogLevel::Info,"terrain-surface","[TERRAIN-SURFACE] normals installed material=\"%s\" passes=%zu source=\"%s\" replacement=\"%s\" size=%ux%u mips=%u linear=1 heightGeometry=0",g_SurfaceMaterial.c_str(),g_SurfacePasses.size(),sourceNormal.c_str(),resource.c_str(),width,height,desc.MipLevels);
        ReleaseCloneHandoff(material); return true;
    }
    catch(const std::exception& error) { LogShimA(LogLevel::Warn,"terrain-surface","[TERRAIN-SURFACE] declined: %s; original normals retained",error.what()); }
    catch(...) { LogShimA(LogLevel::Warn,"terrain-surface","[TERRAIN-SURFACE] declined after Ogre exception; original normals retained"); }
    ReleaseCloneHandoff(material); ReleaseCloneHandoff(texture); RestoreNativeTerrainSurface(); return false;
}
