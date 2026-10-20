#include "menu_theme.h"
#include "menu_theme_policy.h"
#include "BZROpenShim.h"
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "ogre_runtime.h"
#include "render_profile_runtime.h"
#include "shell_screens.h"
#include "shim_log.h"
#include "patcher.h"
#include <Windows.h>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

namespace BZROpenShim::MenuTheme
{
    namespace
    {
        namespace Shell = ShellScreens;
        struct Shared { void* rep=nullptr; void* info=nullptr; };
        static_assert(sizeof(Shared)==8,"released Ogre SharedPtr ABI");
        using GetIndexed = void*(__thiscall*)(void*,unsigned short);
        using GetName = const std::string&(__thiscall*)(const void*);
        using SetProgram = void(__thiscall*)(void*,const std::string&,bool);
        using GetParams = Shared*(__thiscall*)(const void*,Shared*);
        using SetParams = void(__thiscall*)(void*,Shared);
        using FindConstant = const uint32_t*(__thiscall*)(const void*,const std::string&,bool);
        using WriteConstants = void(__thiscall*)(void*,size_t,const float*,size_t);
        using Free = void(__cdecl*)(void*);
        using GetManager=void*(__cdecl*)();
        using GetMaterial=Shared*(__thiscall*)(void*,Shared*,const std::string&,const std::string&);
        using InfoDtor = void(__thiscall*)(void*,unsigned);
        struct Api
        {
            GetIndexed technique=nullptr,pass=nullptr;
            GetName vertex=nullptr,fragment=nullptr;
            SetProgram setProgram=nullptr;
            GetParams getParams=nullptr;
            SetParams setParams=nullptr;
            FindConstant find=nullptr;
            WriteConstants write=nullptr;
            Free free=nullptr;
            GetManager manager=nullptr;
            GetMaterial material=nullptr;
            bool ready=false;
        };
        Api g_api;
        Settings g_saved,g_preview;
        bool g_read=false,g_apiRead=false,g_collect=false;
        DWORD g_thread=0;
        constexpr char kProgram[]="OpenShim_MenuTheme_fragmentHLSL4";
        struct Entry
        {
            Shared material,original,active;
            void* pass=nullptr;
            std::string program;
            uint32_t index=0,levelsIndex=0;
            bool applied=false;
        };
        // UI-thread owned, bounded. Retains native shared references, never a
        // naked widget. Removed materials are reclaimed when only our ref remains.
        // Remaining native references live until process teardown, as Ogre does.
        std::vector<Entry> g_entries;
        struct Page
        {
            void* screen=nullptr;
            std::array<void*,5> sliders{},values{};
            bool previewRequested=false,saveRequested=false;
            Settings requested;
            void* status=nullptr;
            Settings last;
            std::string message;
        } g_page;

        template<class T> T Export(const char* name) { return reinterpret_cast<T>(OgreRuntime::ResolveExport(name)); }
        bool BindApi()
        {
            if(g_apiRead)return g_api.ready;
            if(!OgreRuntime::IsLoaded())return false;
            g_apiRead=true;
            g_api.technique=Export<GetIndexed>("?getTechnique@Material@Ogre@@QAEPAVTechnique@2@G@Z");
            g_api.pass=Export<GetIndexed>("?getPass@Technique@Ogre@@QAEPAVPass@2@G@Z");
            g_api.vertex=Export<GetName>("?getVertexProgramName@Pass@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            g_api.fragment=Export<GetName>("?getFragmentProgramName@Pass@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
            g_api.setProgram=Export<SetProgram>("?setFragmentProgram@Pass@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
            g_api.getParams=Export<GetParams>("?getFragmentProgramParameters@Pass@Ogre@@QBE?AV?$SharedPtr@VGpuProgramParameters@Ogre@@@2@XZ");
            g_api.setParams=Export<SetParams>("?setFragmentProgramParameters@Pass@Ogre@@QAEXV?$SharedPtr@VGpuProgramParameters@Ogre@@@2@@Z");
            g_api.find=Export<FindConstant>("?_findNamedConstantDefinition@GpuProgramParameters@Ogre@@QBEPBUGpuConstantDefinition@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
            g_api.write=Export<WriteConstants>("?_writeRawConstants@GpuProgramParameters@Ogre@@QAEXIPBMI@Z");
            g_api.free=Export<Free>("?deallocateBytes@StdAllocPolicy@Ogre@@SAXPAX@Z");
            g_api.manager=Export<GetManager>("?getSingletonPtr@MaterialManager@Ogre@@SAPAV12@XZ");
            g_api.material=Export<GetMaterial>("?getByName@MaterialManager@Ogre@@QAE?AV?$SharedPtr@VMaterial@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
            g_api.ready=g_api.manager&&g_api.material&&g_api.technique&&g_api.pass&&g_api.vertex&&g_api.fragment&&g_api.setProgram&&
                g_api.getParams&&g_api.setParams&&g_api.find&&g_api.write&&g_api.free;
            Log(L"[MENUTHEME] Ogre image API %hs\n",g_api.ready?"ready":"unavailable; native images retained");
            return g_api.ready;
        }
        volatile LONG* Count(const Shared& p){return reinterpret_cast<volatile LONG*>(static_cast<uint8_t*>(p.info)+0x14);}
        void Retain(const Shared& p){if(p.rep&&p.info)InterlockedIncrement(Count(p));}
        void Release(Shared& p)
        {
            if(p.rep&&p.info&&InterlockedDecrement(Count(p))==0)
            {
                reinterpret_cast<InfoDtor>((*static_cast<void***>(p.info))[0])(p.info,0);
                g_api.free(p.info);
            }
            p={};
        }
        int Channel(const char* key,int fallback,int maximum=255)
        {
            std::string value;
            if(!TryGetUserConfigString("Display",key,value))return fallback;
            char* end=nullptr;const long v=std::strtol(value.c_str(),&end,10);
            return end!=value.c_str()&&*end==0&&v>=0&&v<=maximum?static_cast<int>(v):fallback;
        }
        void ReadConfig()
        {
            g_saved={};TryGetUserConfigBool("Display","MenuTheme",g_saved.enabled);
            g_saved.rgb={Channel("MenuThemeRed",255),Channel("MenuThemeGreen",0),Channel("MenuThemeBlue",0)};
            g_saved.saturation=Channel("MenuThemeSaturation",100,100);
            g_saved.whiteLevel=Channel("MenuThemeWhiteLevel",100,200);
            g_preview=g_saved;g_read=true;
        }
        void Restore(Entry& e)
        {
            if(!e.applied)return;
            g_api.setProgram(e.pass,e.program,true);
            // Native setter consumes a by-value SharedPtr. Supply its own ref.
            Retain(e.original);g_api.setParams(e.pass,e.original);
            e.applied=false;Release(e.active);
        }
        bool Apply(Entry& e)
        {
            try
            {
                if(!g_preview.enabled){Restore(e);return true;}
                if(!e.applied)
                {
                    // Mark first so every failure restores both native program
                    // and its original parameter block, including mod defaults.
                    e.applied=true;g_api.setProgram(e.pass,kProgram,true);
                    g_api.getParams(e.pass,&e.active);
                    const uint32_t* def=e.active.rep?g_api.find(e.active.rep,"menuTheme",false):nullptr;
                    // Released GpuConstantDefinition: type, physical index,
                    // logical index, element size, array size. Own float4 only.
                    if(!def||def[3]!=4||def[4]!=1||def[1]>1024){Restore(e);return false;}
                    e.index=def[1];
                    const uint32_t* levels=g_api.find(e.active.rep,"menuLevels",false);
                    if(!levels||levels[3]!=4||levels[4]!=1||levels[1]>1024){Restore(e);return false;}
                    e.levelsIndex=levels[1];
                }
                const float rgba[]={g_preview.rgb[0]/255.0f,g_preview.rgb[1]/255.0f,g_preview.rgb[2]/255.0f,1};
                g_api.write(e.active.rep,e.index,rgba,4);
                const float levels[]={g_preview.saturation*.01f,g_preview.whiteLevel*.01f,0,0};
                g_api.write(e.active.rep,e.levelsIndex,levels,4);
                return true;
            }
            catch(...)
            {
                try{Restore(e);}catch(...){}
                return false;
            }
        }
        bool ApplyAll()
        {
            if(g_preview.enabled)Hooks::InstallThumbnailBmpGuardIfPossible();
            bool ok=true;
            for(auto& e:g_entries)ok=Apply(e)&&ok;
            return ok;
        }
        void Prune()
        {
            for(auto i=g_entries.begin();i!=g_entries.end();)
            {
                if(*Count(i->material)!=1){++i;continue;}
                Release(i->active);Release(i->original);Release(i->material);
                i=g_entries.erase(i);
            }
        }
        void CollectLoadedImages()
        {
            void* manager=g_api.manager();if(!manager)return;
            g_collect=true;
            for(const auto name:MenuImages)
            {
                Shared material;
                try
                {
                    g_api.material(manager,&material,std::string(name),"Autodetect");
                    if(material.rep)ImageMaterialReady(std::string(name).c_str(),&material);
                }
                catch(...){}
                Release(material);
            }
            g_collect=false;
        }
        void Back(){if(g_page.screen)Shell::Back(g_page.screen);}
        std::array<int,5> Values(const Settings& s){return {s.rgb[0],s.rgb[1],s.rgb[2],s.saturation,s.whiteLevel};}
        void UpdateSliders()
        {
            const auto values=Values(g_preview);
            for(size_t i=0;i<5;++i)Shell::SetSliderValue(g_page.sliders[i],static_cast<float>(values[i]));
        }
        // Mouse callbacks only enqueue commands; UI update owns Ogre/INI writes.
        void Stock(){g_page.requested=g_preview;g_page.requested.enabled=false;g_page.previewRequested=true;}
        template<int R,int G,int B> void Preset()
        {
            g_page.requested=g_preview;g_page.requested.enabled=true;g_page.requested.rgb={R,G,B};g_page.previewRequested=true;
        }
        void Save(){g_page.saveRequested=true;}
        void Persist()
        {
            const auto values=Values(g_preview);
            std::array<std::string,6> text;
            for(size_t i=0;i<5;++i)text[i]=std::to_string(values[i]);
            text[5]=g_preview.enabled?"1":"0";
            const char* keys[]={"MenuThemeRed","MenuThemeGreen","MenuThemeBlue","MenuThemeSaturation","MenuThemeWhiteLevel","MenuTheme"};
            std::array<ShimConfigValue,6> updates;
            for(size_t i=0;i<6;++i)updates[i]={"Display",keys[i],text[i].c_str()};
            bool ok=false;
            try{ok=WriteShimUserConfigValues(updates.data(),updates.size());}catch(...){}
            if(ok)g_saved=g_preview;
            g_page.message=ok?"Menu theme saved.":"Could not save the menu theme. Previous saved settings retained.";
        }
        void Closed(void* screen)
        {
            if(g_page.screen!=screen)return;
            g_preview=g_saved;ApplyAll();g_page={};
        }
        void Tick(void* screen)
        {
            if(g_page.screen!=screen)return;
            if(g_page.previewRequested)
            {
                g_preview=g_page.requested;g_page.previewRequested=false;UpdateSliders();
                g_page.message=ApplyAll()?"Previewing theme. Apply saves; Back discards changes.":"Theme shader unavailable; affected images stay native.";
            }
            auto values=Values(g_preview);bool changed=false;
            for(size_t i=0;i<5;++i)
            {
                const float raw=Shell::SliderValue(g_page.sliders[i]);
                if(!std::isfinite(raw)||raw<0||raw>(i<3?255:i==3?100:200))continue;
                const int value=static_cast<int>(std::lround(raw));
                changed=changed||value!=values[i];values[i]=value;
                const std::string text=std::to_string(value)+(i>=3?"%":"");
                Shell::SetLabelText(g_page.values[i],text.c_str());
            }
            if(changed)
            {
                g_preview.rgb={values[0],values[1],values[2]};g_preview.saturation=values[3];g_preview.whiteLevel=values[4];g_preview.enabled=true;
                g_page.message=ApplyAll()?"Previewing custom color. Apply saves; Back discards changes.":"Theme shader unavailable; affected images stay native.";
            }
            if(g_page.saveRequested){g_page.saveRequested=false;Persist();}
            Shell::SetLabelText(g_page.status,g_page.message.c_str());
        }
        bool Build(void* screen)
        {
            if(!g_read)ReadConfig();
            g_preview=g_saved;g_page={};g_page.screen=screen;
            void* panel=Shell::AddPanel(screen,nullptr,"MenuTheme_Overlay",{0,0,1440,1080},"osh_menu_theme_center.png");
            if(!panel)return false;
            // Keep navigation inside the full-screen input owner. A sibling
            // button can draw correctly while the panel consumes its clicks.
            Shell::AddButton(panel,nullptr,"MenuTheme_Back",{0,0,342,77},"Back",Shell::kSkinTopCorner,1,28,Back);
            Shell::AddLabel(panel,panel,"MenuTheme_Title",{470,132,500,56},"MENU COLORS",Shell::kTitleLabelFlags);
            Shell::AddLabel(panel,panel,"MenuTheme_Help",{280,240,880,46},"Adjust RGB, saturation and white level to preview.");
            const bool supported=GetBzrDistribution()==BzrDistribution::GOG&&IsCompatibleGameVersion()&&
                RenderProfiles::IdentifyActiveRenderSystem()==1&&BindApi()&&Shell::SlidersAvailable();
            if(!supported)
            {
                g_page.message="Menu recoloring is unavailable on this build or renderer.";
                g_page.status=Shell::AddLabel(panel,panel,"MenuTheme_Status",{280,800,880,56},g_page.message.c_str());
                return true;
            }
            const char* labels[]={"Red","Green","Blue","Saturation","White Level"};
            const char* sliderNames[]={"MenuTheme_Red","MenuTheme_Green","MenuTheme_Blue","MenuTheme_Saturation","MenuTheme_WhiteLevel"};
            const auto values=Values(g_preview);
            for(size_t i=0;i<5;++i)
            {
                const float y=322+static_cast<float>(i)*72;
                Shell::AddLabel(panel,panel,labels[i],{280,y,160,42},labels[i]);
                g_page.sliders[i]=Shell::AddSlider(panel,panel,sliderNames[i],{445,y,590,42},static_cast<float>(i<3?255:i==3?100:200),static_cast<float>(values[i]));
                g_page.values[i]=Shell::AddLabel(panel,panel,(std::string(sliderNames[i])+"_Value").c_str(),{1060,y,100,42},std::to_string(values[i]).c_str());
            }
            const Shell::ButtonSkin skin{"uibtn.png","uibtnhv.png","uibtnhv.png"};
            Shell::AddButton(panel,panel,"MenuTheme_RedPreset",{280,730,200,44},"Red",skin,1,7,&Preset<255,0,0>);
            Shell::AddButton(panel,panel,"MenuTheme_BluePreset",{500,730,200,44},"Blue",skin,1,7,&Preset<0,100,255>);
            Shell::AddButton(panel,panel,"MenuTheme_AmberPreset",{720,730,200,44},"Amber",skin,1,7,&Preset<255,150,0>);
            Shell::AddButton(panel,panel,"MenuTheme_Stock",{940,730,200,44},"Stock",skin,1,7,Stock);
            Shell::AddButton(panel,panel,"MenuTheme_Apply",{550,790,340,44},"Apply",skin,1,9,Save);
            CollectLoadedImages();
            g_page.message="Preview menu images; Apply saves, Back discards changes.";
            g_page.status=Shell::AddLabel(panel,panel,"MenuTheme_Status",{280,875,880,42},g_page.message.c_str());
            return true;
        }
    }

    void ImageMaterialReady(const char* name,void* materialSlot) noexcept
    {
        try
        {
            if(GetBzrDistribution()!=BzrDistribution::GOG||!IsCompatibleGameVersion())return;
            if(!g_read)ReadConfig();
            if((!g_preview.enabled&&!g_collect)||!name||!materialSlot||!IsMenuImage(name))return;
            if(!g_thread)g_thread=GetCurrentThreadId();
            if(g_thread!=GetCurrentThreadId()||RenderProfiles::IdentifyActiveRenderSystem()!=1||!BindApi())return;
            const Shared material=*static_cast<const Shared*>(materialSlot);
            if(!material.rep||!material.info)return;
            for(auto& e:g_entries)if(e.material.rep==material.rep){Apply(e);return;}
            Prune();if(g_entries.size()>=512)return;
            void* technique=g_api.technique(material.rep,0);
            void* pass=technique?g_api.pass(technique,0):nullptr;
            if(!pass||g_api.vertex(pass)!="UI_vertex"||g_api.fragment(pass)!="UI_fragment")return;
            Entry e;e.material=material;e.pass=pass;e.program=g_api.fragment(pass);
            g_api.getParams(pass,&e.original);if(!e.original.rep||!e.original.info)return;
            Retain(e.material);g_entries.push_back(std::move(e));
            const bool ok=Apply(g_entries.back());
            Log(L"[MENUTHEME] image=%hs result=%hs materials=%zu\n",name,ok?"themed":"native",g_entries.size());
        }
        catch(...) { Log(L"[MENUTHEME] Image adapter unavailable; native material retained\n"); }
    }

    bool ImageAdapterNeeded(){if(!g_read)ReadConfig();return g_preview.enabled;}
    bool RegisterScreen(){return Shell::RegisterScreen({ScreenId,"Menu Colors",Build,Closed,Tick});}
}
