// Included inside terrain_proxy.cpp's private namespace. Reuses its exact-build
// gates, native cluster discovery, Ogre ABI adapters and mission resource owner.
struct TerrainTessPass
{
    uint16_t technique, pass;
    int polygonMode;
    std::string hull, domain;
};
std::vector<TerrainTessPass> g_TessPasses;
std::string g_TessSourceMaterial;

// Optional Ogre parameter exports, guarded by the same released Ogre identity
// as the terrain adapters. Use the logical matrix slot, not a guessed buffer
// offset, so Ogre owns per-camera/per-light updates and stage constant binding.
void ConfigureTerrainMicroReliefDomain(void* pass, const std::string& defines)
{
    if (!g_config.microReliefTest) return;
    HMODULE ogre = GetModuleHandleW(L"OgreMain.dll");
    auto getParameters = Resolve<FnGetGpuProgramParameters>(ogre,
        "?getTessellationDomainProgramParameters@Pass@Ogre@@QBE?AV?$SharedPtr@VGpuProgramParameters@Ogre@@@2@XZ");
    struct ConstantDefinition {
        int type; uint32_t physical, logical, elementSize, arraySize; uint16_t variability;
    };
    using FindConstant = const ConstantDefinition* (__thiscall*)(void*, const std::string&, bool);
    using SetAuto = void (__thiscall*)(void*, uint32_t, int, uint32_t);
    auto find = Resolve<FindConstant>(ogre,
        "?_findNamedConstantDefinition@GpuProgramParameters@Ogre@@QBEPBUGpuConstantDefinition@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
    auto set = Resolve<SetAuto>(ogre,
        "?setAutoConstant@GpuProgramParameters@Ogre@@QAEXIW4AutoConstantType@12@I@Z");
    if (!getParameters || !find || !set) throw std::runtime_error("relief auto-parameter API unavailable");
    OgreSharedPtr parameters;
    getParameters(pass, &parameters);
    if (!parameters.rep) throw std::runtime_error("relief domain parameters unavailable");
    try
    {
        const auto bind = [&](const char* name, int type, uint32_t index = 0) {
            const auto* definition = find(parameters.rep, std::string(name), false);
            if (!definition || definition->type != 21 || definition->elementSize != 16 ||
                definition->arraySize != 1 || definition->physical > 4096 || definition->logical > 4096)
                throw std::runtime_error("relief matrix definition contract unavailable");
            set(parameters.rep, definition->logical, type, index);
        };
        // Ogre 1.10 AutoConstantType, independently checked against public SDK.
        bind("reliefView", 8);          // ACT_VIEW_MATRIX
        bind("reliefInverseView", 9);   // ACT_INVERSE_VIEW_MATRIX
        bind("reliefInverseWorldView", 21); // ACT_INVERSE_WORLDVIEW_MATRIX
        bind("reliefProjection", 12);   // ACT_PROJECTION_MATRIX
        if (defines.find("SHADOWRECEIVER") != std::string::npos)
        {
            bind("reliefShadow1", 80, 0); // ACT_TEXTURE_VIEWPROJ_MATRIX
            if (defines.find("PSSM_ENABLED") != std::string::npos)
            {
                bind("reliefShadow2", 80, 1);
                bind("reliefShadow3", 80, 2);
            }
        }
    }
    catch (...) { ReleaseCloneHandoff(parameters); throw; }
    ReleaseCloneHandoff(parameters);
}

// Released renderer export: vector<uint8_t> uses the three-pointer release ABI.
struct TerrainMicrocode { const uint8_t* first; const uint8_t* last; const uint8_t* end; };
using FnTerrainMicrocode = const TerrainMicrocode* (__thiscall*)(void*);
std::string TerrainProgramSignature(void* program, const char* tag, bool controlPoints = false)
{
    static auto microcode = Resolve<FnTerrainMicrocode>(GetModuleHandleW(L"RenderSystem_Direct3D11.dll"),
        "?getMicroCode@D3D11HLSLProgram@Ogre@@QBEABV?$vector@EV?$STLAllocator@EV?$CategorisedAllocPolicy@$0A@@Ogre@@@Ogre@@@std@@XZ");
    if (!microcode) throw std::runtime_error("runtime shader audit export unavailable");
    const auto* bytes = microcode(program);
    if (!bytes || !bytes->first || bytes->last < bytes->first || bytes->last > bytes->end)
        throw std::runtime_error("runtime shader bytecode unavailable");
    const size_t size = bytes->last - bytes->first;
    const auto read = [&](size_t offset) {
        if (offset + 4 > size) throw std::runtime_error("invalid DXBC signature");
        uint32_t value; memcpy(&value, bytes->first + offset, 4); return value;
    };
    if (size < 32 || size > 1024 * 1024 || memcmp(bytes->first, "DXBC", 4))
        throw std::runtime_error("runtime shader is not DXBC");
    if (read(28) > 64) throw std::runtime_error("invalid DXBC chunk count");
    for (uint32_t i = 0; i < read(28); ++i)
    {
        const size_t offset = read(32 + i * 4);
        if (offset + 8 > size || memcmp(bytes->first + offset, tag, 4)) continue;
        const size_t chunk = offset + 8;
        const size_t chunkEnd = chunk + read(offset + 4);
        if (chunkEnd > size || read(chunk) > 64 || chunk + 8 + read(chunk) * 24 > chunkEnd)
            throw std::runtime_error("invalid DXBC signature chunk");
        std::string signature;
        for (uint32_t n = 0; n < read(chunk); ++n)
        {
            const size_t row = chunk + 8 + n * 24;
            const size_t name = chunk + read(row);
            if (name >= chunkEnd || row + 24 > chunkEnd) throw std::runtime_error("invalid DXBC signature row");
            const char* text = reinterpret_cast<const char*>(bytes->first + name);
            const void* zero = memchr(text, 0, chunkEnd - name);
            if (!zero) throw std::runtime_error("invalid DXBC semantic name");
            signature.append(text, static_cast<const char*>(zero) - text);
            for (size_t field = 4; field <= 16; field += 4)
            {
                // SV_POSITION is an ordinary control-point semantic between
                // tessellation stages. Normalize only that system-value tag;
                // names, indices, types, registers and masks remain exact.
                const uint32_t value = controlPoints && field == 8 && strcmp(text, "SV_POSITION") == 0 ? 1 : read(row + field);
                signature += ":" + std::to_string(value);
            }
            signature += ":" + std::to_string(bytes->first[row + 20]) + ";";
        }
        return signature;
    }
    throw std::runtime_error("runtime shader signature missing");
}

void RestoreNativeTerrainTessellationTest()
{
    if (g_TessSourceMaterial.empty()) { RestoreTerrainMicroReliefBounds(); return; }
    OgreSharedPtr material;
    try
    {
        if (GetModuleHandleW(L"OgreMain.dll"))
        {
            if (void* manager = g_ogre.getMaterialManager())
            {
                g_ogre.getMaterialByName(manager, &material, g_TessSourceMaterial, std::string("Autodetect"));
                if (material.rep)
                {
                    for (const auto& saved : g_TessPasses)
                    {
                        if (saved.technique >= g_ogre.getNumTechniques(material.rep)) continue;
                        void* technique = g_ogre.getTechnique(material.rep, saved.technique);
                        if (saved.pass >= g_ogre.getNumPasses(technique)) continue;
                        void* pass = g_ogre.getPass(technique, saved.pass);
                        g_ogre.setHullProgram(pass, std::string(), true);
                        g_ogre.setDomainProgram(pass, std::string(), true);
                        if (g_ogre.setPolygonMode) g_ogre.setPolygonMode(pass, saved.polygonMode);
                    }
                }
            }
            ReleaseCloneHandoff(material);
        }
        LogShimA(LogLevel::Info, "terrain-tess", "[TERRAIN-TESS] shared material restored source=\"%s\" passes=%zu", g_TessSourceMaterial.c_str(), g_TessPasses.size());
    }
    catch (...)
    {
        ReleaseCloneHandoff(material);
        LogShimA(LogLevel::Warn, "terrain-tess", "[TERRAIN-TESS] shared material restore raised an Ogre exception");
    }
    RestoreTerrainMicroReliefBounds();
    g_TessPasses.clear();
    g_TessSourceMaterial.clear();
}

bool InstallNativeTerrainTessellationTest()
{
    if (!g_config.tessellationTest || g_proxy.semanticMaterialInstalled ||
        g_proxy.semanticMaterialUnsupported)
        return g_proxy.semanticMaterialInstalled;
    OgreSharedPtr sourceMaterial, clone, program;
    try
    {
        HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
        std::string rendererHash;
        if (!renderer || !VerifyModuleHash(renderer,
                "78A1D8E13C8BD71983B09A39A3DCF7783E6C34DDE577DE3B9202460DB500AAE0",
                rendererHash))
            throw std::runtime_error("released DX11 renderer identity not validated");
        if (!g_ogre.getD3D11VertexBuffer)
            g_ogre.getD3D11VertexBuffer = Resolve<FnGetD3D11VertexBuffer>(
                renderer,
                "?getD3DVertexBuffer@D3D11HardwareVertexBuffer@Ogre@@QBEPAUID3D11Buffer@@XZ");
        if (!g_ogre.setHullProgram || !g_ogre.setDomainProgram ||
            !g_ogre.getHullProgram || !g_ogre.getDomainProgram ||
            !g_ogre.hasHullProgram || !g_ogre.hasDomainProgram ||
            !g_ogre.programSupported || !g_ogre.getD3D11VertexBuffer ||
            !g_ogre.getPolygonMode ||
            (g_config.tessellationWireframe && !g_ogre.setPolygonMode) ||
            !ValidateTerrainOperation(g_proxy.sourceMesh, g_proxy.sourceEntity, "tessellation source"))
            throw std::runtime_error("terrain/API contract unavailable");
        RenderOperation operation = {};
        void* subEntity = nullptr;
        void* vertexBuffer = nullptr;
        if (!GetEntityOperation(g_proxy.sourceEntity, operation, subEntity) ||
            !GetVertexBuffer(operation, 0, vertexBuffer))
            throw std::runtime_error("native source buffer unavailable");
        ID3D11Buffer* buffer = g_ogre.getD3D11VertexBuffer(vertexBuffer);
        ID3D11Device* device = nullptr;
        if (!buffer)
            throw std::runtime_error("DX11 buffer unavailable");
        buffer->GetDevice(&device);
        const D3D_FEATURE_LEVEL level = device ? device->GetFeatureLevel() : D3D_FEATURE_LEVEL_9_1;
        if (device) device->Release();
        if (level < D3D_FEATURE_LEVEL_11_0)
            throw std::runtime_error("feature level 11_0 required");

        const auto shaderPath = GetIniPath().parent_path() /
            "openshim/renderer/enhanced/openshim_terrain_tessellation_test.hlsl";
        std::ifstream input(shaderPath, std::ios::binary);
        std::string source((std::istreambuf_iterator<char>(input)), {});
        if (source.empty() || source.size() > 64 * 1024)
            throw std::runtime_error("test shader missing/invalid");
        source = "#define OPENSHIM_TESS_FACTOR " + std::to_string(g_config.tessellationFactor) + "\n" + source;
        if (g_config.microReliefTest)
            source = "#define OPENSHIM_RELIEF_TEST 1\n#define OPENSHIM_RELIEF_AMPLITUDE " +
                std::to_string(g_config.microReliefAmplitude) + "\n" + source;

        const std::string group = "Autodetect";
        const std::string* material = g_ogre.getMaterialName(subEntity);
        if (!material || material->empty())
            throw std::runtime_error("native material unavailable");
        g_proxy.materialName = *material;
        void* materialManager = g_ogre.getMaterialManager();
        void* programManager = g_ogre.getHighLevelProgramManager();
        if (!materialManager || !programManager)
            throw std::runtime_error("resource managers unavailable");
        g_ogre.getMaterialByName(materialManager, &sourceMaterial, *material, group);
        if (!sourceMaterial.rep)
            throw std::runtime_error("source material unavailable");
        g_proxy.generation = ++g_resourceSerial;
        g_proxy.semanticMaterialGeneration = ++g_semanticMaterialSerial;
        const std::string prefix = "OpenShim/TerrainTessTest/" +
            std::to_string(g_proxy.semanticMaterialGeneration) + "/" + SourceHashSuffix(source);
        g_proxy.semanticMaterialName = prefix + "/Material";
        g_ogre.cloneMaterial(sourceMaterial.rep, &clone, g_proxy.semanticMaterialName, false, std::string());
        if (!clone.rep)
            throw std::runtime_error("material clone unavailable");
        ++g_semanticMaterialCreated;
        std::map<std::string, std::pair<std::string, std::string>> programs;
        std::map<std::string, std::string> interfaces;
        unsigned specialized = 0;
        for (uint16_t t = 0; t < g_ogre.getNumTechniques(clone.rep); ++t)
        {
            void* technique = g_ogre.getTechnique(clone.rep, t);
            for (uint16_t p = 0; p < g_ogre.getNumPasses(technique); ++p)
            {
                void* pass = g_ogre.getPass(technique, p);
                const OgreSharedPtr* vertex = g_ogre.getVertexProgram(pass);
                if (!vertex || !vertex->rep) continue;
                const std::string* vertexSource = g_ogre.getProgramSource(vertex->rep);
                if (!vertexSource || vertexSource->empty())
                {
                    vertex = g_ogre.getUnifiedDelegate(vertex->rep);
                    if (!vertex || !vertex->rep) continue;
                    vertexSource = g_ogre.getProgramSource(vertex->rep);
                }
                std::string target, entry, defines;
                g_ogre.getStringParameter(vertex->rep, &target, std::string("target"));
                g_ogre.getStringParameter(vertex->rep, &entry, std::string("entry_point"));
                g_ogre.getStringParameter(vertex->rep, &defines, std::string("preprocessor_defines"));
                // Cover recognized per-pixel terrain, including the main
                // shadow-receiving passes. Preserve their shadow coordinates.
                if (target.rfind("vs_4", 0) != 0 || entry != "terrain_vertex" ||
                    !vertexSource || vertexSource->find("iPosition.y = heightOffset") == std::string::npos ||
                    vertexSource->find("out float vDepth : TEXCOORD5") == std::string::npos ||
                    vertexSource->find("out float3 vViewPosition : TEXCOORD4") == std::string::npos ||
                    defines.find("VERTEX_LIGHTING") != std::string::npos)
                    continue;
                const std::string expected = TerrainProgramSignature(vertex->rep, "OSGN");
                const auto signatureInsertion = interfaces.emplace(defines, expected);
                if (!signatureInsertion.second && signatureInsertion.first->second != expected)
                    throw std::runtime_error("same-defines terrain passes have different runtime interfaces");
                auto found = programs.find(defines);
                if (found == programs.end())
                {
                    std::pair<std::string, std::string> names;
                    for (int stage = 0; stage < 2; ++stage)
                    {
                        // Released Ogre's microcode cache is name-keyed. Include
                        // defines so a reordered pass cannot reuse another
                        // permutation's bytecode from an earlier game session.
                        const std::string name = prefix + "/" + SourceHashSuffix(defines) +
                            (stage == 0 ? "/Hull" : "/Domain");
                        // Ogre 1.10 GpuProgramType: domain=3, hull=4.
                        g_ogre.createHighLevelProgram(programManager, &program, name,
                            std::string("General"), std::string("hlsl"), stage == 0 ? 4 : 3);
                        if (!program.rep)
                            throw std::runtime_error("shader creation failed");
                        g_proxy.semanticProgramNames.push_back(name);
                        ++g_semanticProgramsCreatedTotal;
                        g_ogre.setProgramSource(program.rep, source);
                        if (!g_ogre.setStringParameter(program.rep, std::string("target"),
                                stage == 0 ? std::string("hs_5_0") : std::string("ds_5_0")) ||
                            !g_ogre.setStringParameter(program.rep, std::string("entry_point"),
                                stage == 0 ? std::string("TerrainHull") : std::string("TerrainDomain")) ||
                            !g_ogre.setStringParameter(program.rep, std::string("preprocessor_defines"), defines))
                            throw std::runtime_error("shader parameters rejected");
                        g_ogre.loadResource(program.rep, true);
                        if (!g_ogre.programSupported(program.rep))
                            throw std::runtime_error("shader compilation unsupported");
                        const std::string actualInput = TerrainProgramSignature(program.rep, "ISGN", stage == 1);
                        const std::string actualOutput = TerrainProgramSignature(program.rep, "OSGN", stage == 0);
                        if (expected != actualInput || expected != actualOutput)
                        {
                            LogShimA(LogLevel::Warn, "terrain-tess", "[TERRAIN-TESS] runtime signature mismatch stage=%d expected=%s input=%s output=%s", stage, expected.c_str(), actualInput.c_str(), actualOutput.c_str());
                            throw std::runtime_error("runtime VS/HS/DS signature mismatch");
                        }
                        ReleaseCloneHandoff(program);
                        (stage == 0 ? names.first : names.second) = name;
                    }
                    found = programs.emplace(defines, names).first;
                }
                g_ogre.setHullProgram(pass, found->second.first, true);
                g_ogre.setDomainProgram(pass, found->second.second, true);
                ConfigureTerrainMicroReliefDomain(pass, defines);
                const OgreSharedPtr* hull = g_ogre.getHullProgram(pass);
                const OgreSharedPtr* domain = g_ogre.getDomainProgram(pass);
                if (!hull || !hull->rep || !domain || !domain->rep ||
                    *g_ogre.getResourceName(hull->rep) != found->second.first ||
                    *g_ogre.getResourceName(domain->rep) != found->second.second)
                    throw std::runtime_error("shader bind audit failed");
                if (g_config.tessellationWireframe)
                    g_ogre.setPolygonMode(pass, 2); // Ogre::PM_WIREFRAME
                void* originalPass = g_ogre.getPass(g_ogre.getTechnique(sourceMaterial.rep, t), p);
                // Ogre's program getter dereferences an absent usage object;
                // the has-program API is the safe test for an unbound stage.
                if (g_ogre.hasHullProgram(originalPass) || g_ogre.hasDomainProgram(originalPass))
                    throw std::runtime_error("source pass already uses tessellation");
                g_TessPasses.push_back({ t, p, g_ogre.getPolygonMode(originalPass), found->second.first, found->second.second });
                ++specialized;
            }
        }
        if (!specialized)
            throw std::runtime_error("no compatible per-pixel terrain pass");
        if (g_config.microReliefTest && !PrepareTerrainMicroReliefBounds())
            throw std::runtime_error("relief bounds could not be prepared");
        // Assigning a clone to the discovered Entity did not reach observed
        // submissions. Specialize its shared terrain material so native
        // renderables see the programs. All clusters using this material are
        // affected. Meshes, bounds, COLOR0 and original VS/PS stay untouched.
        g_TessSourceMaterial = g_proxy.materialName;
        for (const auto& saved : g_TessPasses)
        {
            void* pass = g_ogre.getPass(g_ogre.getTechnique(sourceMaterial.rep, saved.technique), saved.pass);
            g_ogre.setHullProgram(pass, saved.hull, true);
            g_ogre.setDomainProgram(pass, saved.domain, true);
            // Stage parameters were audited on the clone. Copy the same
            // auto-constant setup onto the newly attached original usage.
            if (g_config.microReliefTest)
            {
                const OgreSharedPtr* domain = g_ogre.getDomainProgram(pass);
                std::string defines;
                g_ogre.getStringParameter(domain->rep, &defines, std::string("preprocessor_defines"));
                ConfigureTerrainMicroReliefDomain(pass, defines);
            }
            if (g_config.tessellationWireframe) g_ogre.setPolygonMode(pass, 2);
        }
        ReleaseCloneHandoff(sourceMaterial);
        ReleaseCloneHandoff(clone);
        g_proxy.semanticMaterialInstalled = true;
        LogShimA(LogLevel::Info, "terrain-tess",
            "[TERRAIN-TESS] shared native material installed discoveryZone=(%d,%d) discoveryCluster=(%d,%d) factor=%d displacement=%.3f wireframe=%d passes=%u programs=%zu featureLevel=0x%X source=\"%s\" test=\"%s\"",
            g_proxy.zoneX, g_proxy.zoneZ, g_proxy.clusterX, g_proxy.clusterZ,
            g_config.tessellationFactor, g_config.microReliefTest ? g_config.microReliefAmplitude : 0.0f,
            g_config.tessellationWireframe ? 1 : 0,
            specialized, g_proxy.semanticProgramNames.size(), static_cast<unsigned>(level),
            g_proxy.materialName.c_str(), g_proxy.semanticMaterialName.c_str());
        return true;
    }
    catch (const std::exception& error)
    {
        LogShimA(LogLevel::Warn, "terrain-tess", "[TERRAIN-TESS] test declined: %s; native material retained", error.what());
    }
    catch (...)
    {
        LogShimA(LogLevel::Warn, "terrain-tess", "[TERRAIN-TESS] test declined after Ogre exception; native material retained");
    }
    RestoreNativeTerrainTessellationTest();
    g_TessPasses.clear();
    ReleaseCloneHandoff(program);
    ReleaseCloneHandoff(sourceMaterial);
    ReleaseCloneHandoff(clone);
    RemoveSemanticResources("tessellation-test-declined");
    g_proxy.semanticMaterialUnsupported = true; // bounded one attempt per mission
    return false;
}
