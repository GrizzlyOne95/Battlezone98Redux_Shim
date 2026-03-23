
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00664110(void)

{
  char cVar1;
  bool bVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  void *pvVar5;
  RenderSystem *pRVar6;
  undefined4 *puVar7;
  ExternalTextureSourceManager *this;
  ArchiveManager *this_00;
  _AFX_AYGSHELL_STATE *p_Var8;
  Manager *this_01;
  ResourceGroupManager *this_02;
  Root *this_03;
  uint uVar9;
  int iVar10;
  RenderWindow *pRVar11;
  SceneManager *pSVar12;
  Vector3 *pVVar13;
  TextureManager *this_04;
  HardwarePixelBuffer *pHVar14;
  int unaff_EBP;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar15;
  code *pcVar16;
  uint uVar17;
  PixelFormat PVar18;
  int iVar19;
  ManualResourceLoader *pMVar20;
  uint uVar21;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar22;
  bool bVar23;
  OgreTheoraVideoManager *pOVar24;
  ArchiveFactory *pAVar25;
  char *pcVar26;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar27;
  
  *(undefined4 *)(unaff_EBP + -4) = 9;
  basic_string<>();
  *(undefined1 *)(unaff_EBP + -4) = 0xe;
  uVar4 = Ogre::ConfigFile::getSetting
                    ((ConfigFile *)(unaff_EBP + -0x530),
                     (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )(unaff_EBP + -0x434),
                     (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )(unaff_EBP + -0x2cc),
                     (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )&DAT_025f8dc8);
  *(undefined4 *)(unaff_EBP + -0x4fc) = uVar4;
  FUN_0045e0f0();
  ~basic_string<>();
  *(undefined1 *)(unaff_EBP + -4) = 9;
  ~basic_string<>();
  basic_string<>();
  *(undefined1 *)(unaff_EBP + -4) = 0xf;
  Ogre::ConfigFile::getSetting
            ((ConfigFile *)(unaff_EBP + -0x530),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (unaff_EBP + -0x104),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (unaff_EBP + -0x1dc),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (unaff_EBP + -0x44));
  *(undefined1 *)(unaff_EBP + -4) = 0x11;
  ~basic_string<>();
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    cVar1 = FUN_00427270();
    if (cVar1 == '\0') {
      *(undefined4 *)(unaff_EBP + -0x464) = 0;
    }
    else {
      *(undefined4 *)(unaff_EBP + -0x464) = 1;
    }
  }
  else {
    *(undefined4 *)(unaff_EBP + -0x464) = 1;
  }
  *(undefined1 *)(unaff_EBP + -4) = 9;
  ~basic_string<>();
  *(undefined1 *)(unaff_EBP + -4) = 8;
  Ogre::ConfigFile::~ConfigFile((ConfigFile *)(unaff_EBP + -0x530));
  pvVar5 = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<0>_>::operator_new(0x1bc);
  *(void **)(unaff_EBP + -0x498) = pvVar5;
  *(undefined1 *)(unaff_EBP + -4) = 0x12;
  if (*(int *)(unaff_EBP + -0x498) == 0) {
    *(undefined4 *)(unaff_EBP + -0x4a0) = 0;
  }
  else {
    basic_string<>();
    *(undefined1 *)(unaff_EBP + -4) = 0x13;
    *(uint *)(unaff_EBP + -0x444) = *(uint *)(unaff_EBP + -0x444) | 1;
    FUN_0041f870();
    basic_string<>();
    *(undefined4 *)(unaff_EBP + -4) = 0x14;
    *(uint *)(unaff_EBP + -0x444) = *(uint *)(unaff_EBP + -0x444) | 2;
    basic_string<>();
    *(undefined4 *)(unaff_EBP + -4) = 0x15;
    *(uint *)(unaff_EBP + -0x444) = *(uint *)(unaff_EBP + -0x444) | 4;
    uVar4 = Ogre::Root::Root(*(Root **)(unaff_EBP + -0x498),
                             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              *)(unaff_EBP + -0x35c),
                             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              *)(unaff_EBP + -0x20c),
                             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              *)(unaff_EBP + -0x2fc));
    *(undefined4 *)(unaff_EBP + -0x4a0) = uVar4;
  }
  *(undefined4 *)(unaff_EBP + -0x4e0) = *(undefined4 *)(unaff_EBP + -0x4a0);
  *(undefined4 *)(unaff_EBP + -4) = 0x18;
  *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 4) = *(undefined4 *)(unaff_EBP + -0x4e0);
  *(undefined4 *)(unaff_EBP + -4) = 0x17;
  if ((*(uint *)(unaff_EBP + -0x444) & 4) != 0) {
    *(uint *)(unaff_EBP + -0x444) = *(uint *)(unaff_EBP + -0x444) & 0xfffffffb;
    ~basic_string<>();
  }
  *(undefined4 *)(unaff_EBP + -4) = 0x16;
  if ((*(uint *)(unaff_EBP + -0x444) & 2) != 0) {
    *(uint *)(unaff_EBP + -0x444) = *(uint *)(unaff_EBP + -0x444) & 0xfffffffd;
    ~basic_string<>();
  }
  *(undefined4 *)(unaff_EBP + -4) = 8;
  if ((*(uint *)(unaff_EBP + -0x444) & 1) != 0) {
    *(uint *)(unaff_EBP + -0x444) = *(uint *)(unaff_EBP + -0x444) & 0xfffffffe;
    ~basic_string<>();
  }
  uVar4 = FUN_00435ca0();
  *(undefined4 *)(unaff_EBP + -0x4e8) = uVar4;
  if (*(int *)(unaff_EBP + -0x4e8) == 0) {
    *(undefined1 *)(unaff_EBP + -0x453) = 0;
    *(undefined1 *)(unaff_EBP + -4) = 6;
    ~basic_string<>();
    *(undefined1 *)(unaff_EBP + -4) = 4;
    FUN_004180b0();
    *(undefined1 *)(unaff_EBP + -4) = 3;
    ~basic_string<>();
    *(undefined1 *)(unaff_EBP + -4) = 2;
    FUN_004180b0();
    *(undefined1 *)(unaff_EBP + -4) = 1;
    ~basic_string<>();
    *(undefined1 *)(unaff_EBP + -4) = 0;
    FUN_004180b0();
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    ~basic_string<>();
  }
  else {
    cVar1 = FUN_0041f890();
    if (cVar1 != '\0') {
      FID_conflict_operator_();
    }
    pRVar6 = Ogre::Root::getRenderSystemByName
                       (*(Root **)(*(int *)(unaff_EBP + -0x438) + 4),
                        (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)&DAT_025f8d94);
    if (pRVar6 == (RenderSystem *)0x0) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_025f8d94,"Direct3D9 Rendering Subsystem");
    }
    pRVar6 = Ogre::Root::getRenderSystemByName
                       (*(Root **)(*(int *)(unaff_EBP + -0x438) + 4),
                        (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)&DAT_025f8d94);
    if (pRVar6 == (RenderSystem *)0x0) {
      Ogre::Root::getAvailableRenderers(*(Root **)(*(int *)(unaff_EBP + -0x438) + 4));
      puVar7 = (undefined4 *)FUN_00666680();
      *(undefined4 *)(unaff_EBP + -0x4a8) = *puVar7;
      (**(code **)(**(int **)(unaff_EBP + -0x4a8) + 4))();
      FID_conflict_operator_();
    }
    pRVar6 = Ogre::Root::getRenderSystemByName
                       (*(Root **)(*(int *)(unaff_EBP + -0x438) + 4),
                        (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)&DAT_025f8d94);
    if (pRVar6 == (RenderSystem *)0x0) {
      *(undefined1 *)(unaff_EBP + -0x455) = 0;
      *(undefined1 *)(unaff_EBP + -4) = 6;
      ~basic_string<>();
      *(undefined1 *)(unaff_EBP + -4) = 4;
      FUN_004180b0();
      *(undefined1 *)(unaff_EBP + -4) = 3;
      ~basic_string<>();
      *(undefined1 *)(unaff_EBP + -4) = 2;
      FUN_004180b0();
      *(undefined1 *)(unaff_EBP + -4) = 1;
      ~basic_string<>();
      *(undefined1 *)(unaff_EBP + -4) = 0;
      FUN_004180b0();
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      ~basic_string<>();
    }
    else {
      if (DAT_008ed0c4 == 2) {
        DAT_008ed0c4 = *(int *)(unaff_EBP + -0x464);
      }
      pvVar5 = operator_new(0x9c);
      *(void **)(unaff_EBP + -0x460) = pvVar5;
      *(undefined1 *)(unaff_EBP + -4) = 0x19;
      if (*(int *)(unaff_EBP + -0x460) == 0) {
        *(undefined4 *)(unaff_EBP + -0x470) = 0;
      }
      else {
        Ogre::OgreTheoraVideoManager::OgreTheoraVideoManager
                  (*(OgreTheoraVideoManager **)(unaff_EBP + -0x460),1);
        **(undefined4 **)(unaff_EBP + -0x460) = Ogre::OgreTheoraVideoManager::vftable;
        *(undefined ***)(*(int *)(unaff_EBP + -0x460) + 0x80) =
             Ogre::OgreTheoraVideoManager::vftable;
        *(undefined4 *)(unaff_EBP + -0x470) = *(undefined4 *)(unaff_EBP + -0x460);
      }
      *(undefined4 *)(unaff_EBP + -0x4c8) = *(undefined4 *)(unaff_EBP + -0x470);
      *(undefined1 *)(unaff_EBP + -4) = 8;
      DAT_02b3ee4c = *(OgreTheoraVideoManager **)(unaff_EBP + -0x4c8);
      basic_string<>();
      *(undefined1 *)(unaff_EBP + -4) = 0x1a;
      pbVar15 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                (unaff_EBP + -0x23c);
      pOVar24 = DAT_02b3ee4c;
      this = Ogre::ExternalTextureSourceManager::getSingleton();
      Ogre::ExternalTextureSourceManager::setExternalTextureSource
                (this,pbVar15,(ExternalTextureSource *)pOVar24);
      *(undefined1 *)(unaff_EBP + -4) = 8;
      ~basic_string<>();
      pvVar5 = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<0>_>::operator_new(8);
      *(void **)(unaff_EBP + -0x4b8) = pvVar5;
      *(undefined1 *)(unaff_EBP + -4) = 0x1b;
      if (*(int *)(unaff_EBP + -0x4b8) == 0) {
        *(undefined4 *)(unaff_EBP + -0x4b4) = 0;
      }
      else {
        uVar4 = FUN_00669ae0();
        *(undefined4 *)(unaff_EBP + -0x4b4) = uVar4;
      }
      *(undefined4 *)(unaff_EBP + -0x4f8) = *(undefined4 *)(unaff_EBP + -0x4b4);
      *(undefined1 *)(unaff_EBP + -4) = 8;
      *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 0x30) = *(undefined4 *)(unaff_EBP + -0x4f8);
      pAVar25 = *(ArchiveFactory **)(*(int *)(unaff_EBP + -0x438) + 0x30);
      this_00 = Ogre::ArchiveManager::getSingleton();
      Ogre::ArchiveManager::addArchiveFactory(this_00,pAVar25);
      p_Var8 = _AfxGetAygshellState();
      this_01 = Ogre::OgreTheoraVideoManager::getTheoraVideoManager(DAT_02b3ee4c);
      theoraplayer::Manager::setAudioInterfaceFactory(this_01,(AudioInterfaceFactory *)p_Var8);
      basic_string<>();
      *(undefined1 *)(unaff_EBP + -4) = 0x1c;
      basic_string<>();
      *(undefined1 *)(unaff_EBP + -4) = 0x1d;
      basic_string<>();
      *(undefined1 *)(unaff_EBP + -4) = 0x1e;
      Ogre::ConfigFile::ConfigFile((ConfigFile *)(unaff_EBP + -0x514));
      *(undefined1 *)(unaff_EBP + -4) = 0x1f;
      basic_string<>();
      *(undefined1 *)(unaff_EBP + -4) = 0x20;
      FUN_0041f870();
      basic_string<>();
      *(undefined1 *)(unaff_EBP + -4) = 0x21;
      Ogre::ConfigFile::load
                ((ConfigFile *)(unaff_EBP + -0x514),
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (unaff_EBP + -0x11c),
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (unaff_EBP + -0x3bc),true);
      *(undefined1 *)(unaff_EBP + -4) = 0x20;
      ~basic_string<>();
      *(undefined1 *)(unaff_EBP + -4) = 0x1f;
      ~basic_string<>();
      Ogre::ConfigFile::getSectionIterator((ConfigFile *)(unaff_EBP + -0x514));
      while (cVar1 = FUN_00666820(), cVar1 != '\0') {
        uVar4 = FUN_006667b0();
        *(undefined4 *)(unaff_EBP + -0x4d0) = uVar4;
        FUN_0045e0f0();
        ~basic_string<>();
        uVar4 = FUN_006667f0();
        *(undefined4 *)(unaff_EBP + -0x47c) = uVar4;
        FUN_00430590();
        puVar7 = (undefined4 *)FUN_00420260();
        *(undefined4 *)(unaff_EBP + -0x45c) = *puVar7;
        while( true ) {
          FID_conflict_begin();
          cVar1 = FUN_00420f10();
          if (cVar1 == '\0') break;
          FUN_00422150();
          FID_conflict_operator_();
          FUN_00422150();
          FID_conflict_operator_();
          bVar23 = true;
          bVar2 = true;
          pbVar15 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    (unaff_EBP + -0xec);
          pbVar27 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    (unaff_EBP + -0xd4);
          pbVar22 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    (unaff_EBP + -0xbc);
          this_02 = Ogre::ResourceGroupManager::getSingleton();
          Ogre::ResourceGroupManager::addResourceLocation
                    (this_02,pbVar22,pbVar27,pbVar15,bVar2,bVar23);
          FUN_00428570();
        }
      }
      *(undefined1 *)(unaff_EBP + -0x439) = 0;
      *(undefined1 *)(unaff_EBP + -0x445) = 0;
      *(undefined4 *)(unaff_EBP + -0x468) = 3;
      if ((*(int *)(unaff_EBP + -0x468) != 0) &&
         ((*(char *)(unaff_EBP + -0x445) != '\0' || (*(char *)(unaff_EBP + -0x439) == '\0')))) {
        *(undefined1 *)(unaff_EBP + -0x445) = 0;
        *(undefined1 *)(unaff_EBP + -4) = 0x22;
        bVar2 = Ogre::Root::restoreConfig(*(Root **)(*(int *)(unaff_EBP + -0x438) + 4));
        *(bool *)(unaff_EBP + -0x451) = bVar2;
        *(undefined1 *)(unaff_EBP + -0x439) = *(undefined1 *)(unaff_EBP + -0x451);
        FUN_00664905();
        return;
      }
      if ((*(char *)(unaff_EBP + -0x445) == '\0') && (*(char *)(unaff_EBP + -0x439) != '\0')) {
        basic_string<>();
        *(undefined1 *)(unaff_EBP + -4) = 0x27;
        this_03 = Ogre::Root::getSingleton();
        pRVar6 = Ogre::Root::getRenderSystem(this_03);
        *(RenderSystem **)(unaff_EBP + -0x48c) = pRVar6;
        (**(code **)(**(int **)(unaff_EBP + -0x48c) + 0xc))();
        FUN_004b2f10();
        uVar9 = FUN_00427270();
        DAT_009183b8 = uVar9 & 0xff;
        *(undefined1 *)(unaff_EBP + -4) = 0x1f;
        ~basic_string<>();
        pRVar6 = Ogre::Root::getRenderSystem(*(Root **)(*(int *)(unaff_EBP + -0x438) + 4));
        *(RenderSystem **)(unaff_EBP + -0x440) = pRVar6;
        (**(code **)(**(int **)(unaff_EBP + -0x440) + 4))();
        cVar1 = FUN_00427270();
        if (cVar1 != '\0') {
          basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 0x28;
          (**(code **)(**(int **)(unaff_EBP + -0x440) + 0xc))();
          iVar10 = FUN_004b2f10();
          *(int *)(unaff_EBP + -0x4d8) = iVar10 + 0x30;
          *(undefined1 *)(unaff_EBP + -4) = 0x1f;
          ~basic_string<>();
          if ((_DAT_00920ed4 < 1) && ((_DAT_00920ed4 != 0 || (uVar9 = FUN_0048a830(), uVar9 < 2))))
          {
            basic_string<>();
            *(undefined1 *)(unaff_EBP + -4) = 0x2b;
            basic_string<>();
            *(undefined1 *)(unaff_EBP + -4) = 0x2c;
            (**(code **)(**(int **)(unaff_EBP + -0x440) + 0x10))();
            *(undefined1 *)(unaff_EBP + -4) = 0x2b;
            ~basic_string<>();
            *(undefined1 *)(unaff_EBP + -4) = 0x1f;
            ~basic_string<>();
          }
          else {
            basic_string<>();
            *(undefined1 *)(unaff_EBP + -4) = 0x29;
            basic_string<>();
            *(undefined1 *)(unaff_EBP + -4) = 0x2a;
            (**(code **)(**(int **)(unaff_EBP + -0x440) + 0x10))();
            *(undefined1 *)(unaff_EBP + -4) = 0x29;
            ~basic_string<>();
            *(undefined1 *)(unaff_EBP + -4) = 0x1f;
            ~basic_string<>();
          }
        }
        (**(code **)(**(int **)(unaff_EBP + -0x440) + 4))();
        cVar1 = FUN_00427270();
        if (cVar1 == '\0') {
          (**(code **)(**(int **)(unaff_EBP + -0x440) + 4))();
          cVar1 = FUN_00427270();
          if (cVar1 != '\0') {
            uVar4 = (**(code **)(**(int **)(unaff_EBP + -0x440) + 0xc))();
            *(undefined4 *)(unaff_EBP + -0x494) = uVar4;
            basic_string<>();
            *(undefined1 *)(unaff_EBP + -4) = 0x30;
            FUN_00420350();
            *(undefined1 *)(unaff_EBP + -4) = 0x1f;
            ~basic_string<>();
            FID_conflict_begin();
            cVar1 = FUN_00420f10();
            if (cVar1 != '\0') {
              basic_string<>();
              *(undefined1 *)(unaff_EBP + -4) = 0x31;
              basic_string<>();
              *(undefined1 *)(unaff_EBP + -4) = 0x32;
              (**(code **)(**(int **)(unaff_EBP + -0x440) + 0x10))();
              *(undefined1 *)(unaff_EBP + -4) = 0x31;
              ~basic_string<>();
              *(undefined1 *)(unaff_EBP + -4) = 0x1f;
              ~basic_string<>();
            }
            basic_string<>();
            *(undefined1 *)(unaff_EBP + -4) = 0x33;
            pcVar26 = "Yes";
            (**(code **)(**(int **)(unaff_EBP + -0x440) + 0xc))();
            iVar10 = FUN_004b2f10();
            std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            operator=((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)(iVar10 + 0x18),pcVar26);
            *(undefined1 *)(unaff_EBP + -4) = 0x1f;
            ~basic_string<>();
          }
        }
        else {
          uVar4 = (**(code **)(**(int **)(unaff_EBP + -0x440) + 0xc))();
          *(undefined4 *)(unaff_EBP + -0x4a4) = uVar4;
          basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 0x2d;
          FUN_00420350();
          *(undefined1 *)(unaff_EBP + -4) = 0x1f;
          ~basic_string<>();
          FID_conflict_begin();
          cVar1 = FUN_00420f10();
          if (cVar1 != '\0') {
            basic_string<>();
            *(undefined1 *)(unaff_EBP + -4) = 0x2e;
            basic_string<>();
            *(undefined1 *)(unaff_EBP + -4) = 0x2f;
            (**(code **)(**(int **)(unaff_EBP + -0x440) + 0x10))();
            *(undefined1 *)(unaff_EBP + -4) = 0x2e;
            ~basic_string<>();
            *(undefined1 *)(unaff_EBP + -4) = 0x1f;
            ~basic_string<>();
          }
        }
        uVar4 = FUN_00663de0();
        *(undefined4 *)(unaff_EBP + -0x4f0) = uVar4;
        *(undefined4 *)(unaff_EBP + -0x4c0) = *(undefined4 *)(unaff_EBP + -0x4f0);
        *(undefined1 *)(unaff_EBP + -4) = 0x34;
        FUN_00449810();
        *(undefined1 *)(unaff_EBP + -4) = 0x1f;
        ~basic_string<>();
        pbVar27 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  &DAT_025f8dc8;
        pbVar15 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  (unaff_EBP + 8);
        bVar2 = (bool)FUN_00435a30();
        pRVar11 = Ogre::Root::initialise
                            (*(Root **)(*(int *)(unaff_EBP + -0x438) + 4),bVar2,pbVar15,pbVar27);
        *(RenderWindow **)(*(int *)(unaff_EBP + -0x438) + 0xc) = pRVar11;
        if (*(int *)(*(int *)(unaff_EBP + -0x438) + 0xc) == 0) {
          uVar4 = FUN_00435a40();
          *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 0xc) = uVar4;
        }
        if (*(int *)(*(int *)(unaff_EBP + -0x438) + 0xc) == 0) {
          *(undefined1 *)(unaff_EBP + -0x450) = 0;
          *(undefined1 *)(unaff_EBP + -4) = 0x1e;
          Ogre::ConfigFile::~ConfigFile((ConfigFile *)(unaff_EBP + -0x514));
          *(undefined1 *)(unaff_EBP + -4) = 0x1d;
          ~basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 0x1c;
          ~basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 8;
          ~basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 6;
          ~basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 4;
          FUN_004180b0();
          *(undefined1 *)(unaff_EBP + -4) = 3;
          ~basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 2;
          FUN_004180b0();
          *(undefined1 *)(unaff_EBP + -4) = 1;
          ~basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 0;
          FUN_004180b0();
          *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
          ~basic_string<>();
        }
        else {
          Ogre::WindowEventUtilities::addWindowEventListener
                    (*(RenderWindow **)(*(int *)(unaff_EBP + -0x438) + 0xc),
                     *(WindowEventListener **)(unaff_EBP + -0x438));
          cVar1 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0xc) + 0x144))();
          if (cVar1 == '\0') {
            *(undefined4 *)(unaff_EBP + -0x474) = 1;
          }
          else {
            *(undefined4 *)(unaff_EBP + -0x474) = 0;
          }
          *(undefined1 *)(*(int *)(unaff_EBP + -0x438) + 0x54) = *(undefined1 *)(unaff_EBP + -0x474)
          ;
          uVar4 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0xc) + 0x10))();
          *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 0x50) = uVar4;
          uVar4 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0xc) + 0xc))();
          *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 0x4c) = uVar4;
          FUN_00683620();
          pSVar12 = Ogre::Root::createSceneManager
                              (*(Root **)(*(int *)(unaff_EBP + -0x438) + 4),1,
                               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)&DAT_025f8dc8);
          *(SceneManager **)(*(int *)(unaff_EBP + -0x438) + 8) = pSVar12;
          *(undefined4 *)(unaff_EBP + -0x478) = 0x3da3d70a;
          DAT_008ed780 = *(float *)(unaff_EBP + -0x478) * 1.0000001;
          basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 0x35;
          uVar4 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 8) + 0x104))();
          *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 0x10) = uVar4;
          *(undefined1 *)(unaff_EBP + -4) = 0x1f;
          ~basic_string<>();
          pVVar13 = (Vector3 *)Ogre::Vector3::Vector3((Vector3 *)(unaff_EBP + -0x574),0.0,0.0,0.0);
          Ogre::Camera::setPosition(*(Camera **)(*(int *)(unaff_EBP + -0x438) + 0x10),pVVar13);
          pVVar13 = (Vector3 *)Ogre::Vector3::Vector3((Vector3 *)(unaff_EBP + -0x580),0.0,0.0,0.0);
          Ogre::Camera::lookAt(*(Camera **)(*(int *)(unaff_EBP + -0x438) + 0x10),pVVar13);
          (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0x10) + 0x140))();
          (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0x10) + 0x148))();
          Ogre::MovableObject::setCastShadows
                    (*(MovableObject **)(*(int *)(unaff_EBP + -0x438) + 0x10),false);
          uVar4 = FUN_0044c7a0();
          *(undefined1 **)(unaff_EBP + -0x550) = &stack0xffffffec;
          FUN_00662df0(uVar4);
          FUN_00663910(unaff_EBP + -0x55c);
          (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0x10) + 0x138))();
          Ogre::Camera::setAutoAspectRatio(*(Camera **)(*(int *)(unaff_EBP + -0x438) + 0x10),true);
          basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 0x36;
          uVar4 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 8) + 0x104))();
          *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 0x14) = uVar4;
          *(undefined1 *)(unaff_EBP + -4) = 0x1f;
          ~basic_string<>();
          (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0x14) + 0x140))(0x3dcccccd);
          Ogre::MovableObject::setCastShadows
                    (*(MovableObject **)(*(int *)(unaff_EBP + -0x438) + 0x14),false);
          Ogre::Camera::setAutoAspectRatio(*(Camera **)(*(int *)(unaff_EBP + -0x438) + 0x14),true);
          basic_string<>("SniperCam");
          *(undefined1 *)(unaff_EBP + -4) = 0x37;
          uVar4 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 8) + 0x104))
                            (unaff_EBP + -0x3d4);
          *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 0x18) = uVar4;
          *(undefined1 *)(unaff_EBP + -4) = 0x1f;
          ~basic_string<>();
          (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0x18) + 0x140))(0x3dcccccd);
          Ogre::MovableObject::setCastShadows
                    (*(MovableObject **)(*(int *)(unaff_EBP + -0x438) + 0x18),false);
          Ogre::Camera::setAutoAspectRatio(*(Camera **)(*(int *)(unaff_EBP + -0x438) + 0x18),true);
          Ogre::Camera::setPosition
                    (*(Camera **)(*(int *)(unaff_EBP + -0x438) + 0x18),100.0,100.0,100.0);
          basic_string<>("SniperTex");
          *(undefined1 *)(unaff_EBP + -4) = 0x38;
          pbVar22 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x0;
          uVar21 = 0;
          bVar2 = false;
          pMVar20 = (ManualResourceLoader *)0x20;
          iVar19 = 0x1a;
          PVar18 = 0;
          iVar10 = 0x200;
          uVar17 = 0x200;
          uVar9 = 2;
          pbVar15 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    (unaff_EBP + -0x17c);
          pbVar27 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    (unaff_EBP + -0x504);
          pcVar16 = DEFAULT_RESOURCE_GROUP_NAME_exref;
          this_04 = Ogre::TextureManager::getSingleton();
          Ogre::TextureManager::createManual
                    (this_04,pbVar27,pbVar15,(TextureType)pcVar16,uVar9,uVar17,iVar10,PVar18,iVar19,
                     pMVar20,bVar2,uVar21,pbVar22);
          *(undefined1 *)(unaff_EBP + -4) = 0x3a;
          ~basic_string<>();
          uVar4 = get();
          *(undefined4 *)(unaff_EBP + -0x480) = uVar4;
          uVar4 = (**(code **)(**(int **)(unaff_EBP + -0x480) + 0x15c))(unaff_EBP + -0x53c,0,0);
          *(undefined4 *)(unaff_EBP + -0x4c4) = uVar4;
          *(undefined4 *)(unaff_EBP + -0x4cc) = *(undefined4 *)(unaff_EBP + -0x4c4);
          *(undefined1 *)(unaff_EBP + -4) = 0x3b;
          pHVar14 = Ogre::SharedPtr<class_Ogre::HardwarePixelBuffer>::operator->
                              (*(SharedPtr<class_Ogre::HardwarePixelBuffer> **)(unaff_EBP + -0x4cc))
          ;
          *(HardwarePixelBuffer **)(unaff_EBP + -0x488) = pHVar14;
          DAT_00920e80 = (**(code **)(**(int **)(unaff_EBP + -0x488) + 0x40))(0);
          *(undefined1 *)(unaff_EBP + -4) = 0x3a;
          Ogre::HardwarePixelBufferSharedPtr::~HardwarePixelBufferSharedPtr
                    ((HardwarePixelBufferSharedPtr *)(unaff_EBP + -0x53c));
          uVar3 = FUN_00435a50();
          *(undefined1 *)(unaff_EBP + -0x44f) = uVar3;
          *(undefined1 *)(unaff_EBP + -4) = 0x1f;
          FUN_004499a0();
          *(undefined1 *)(unaff_EBP + -4) = 0x1e;
          Ogre::ConfigFile::~ConfigFile((ConfigFile *)(unaff_EBP + -0x514));
          *(undefined1 *)(unaff_EBP + -4) = 0x1d;
          ~basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 0x1c;
          ~basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 8;
          ~basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 6;
          ~basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 4;
          FUN_004180b0();
          *(undefined1 *)(unaff_EBP + -4) = 3;
          ~basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 2;
          FUN_004180b0();
          *(undefined1 *)(unaff_EBP + -4) = 1;
          ~basic_string<>();
          *(undefined1 *)(unaff_EBP + -4) = 0;
          FUN_004180b0();
          *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
          ~basic_string<>();
        }
      }
      else {
        *(undefined1 *)(unaff_EBP + -0x452) = 0;
        *(undefined1 *)(unaff_EBP + -4) = 0x1e;
        Ogre::ConfigFile::~ConfigFile((ConfigFile *)(unaff_EBP + -0x514));
        *(undefined1 *)(unaff_EBP + -4) = 0x1d;
        ~basic_string<>();
        *(undefined1 *)(unaff_EBP + -4) = 0x1c;
        ~basic_string<>();
        *(undefined1 *)(unaff_EBP + -4) = 8;
        ~basic_string<>();
        *(undefined1 *)(unaff_EBP + -4) = 6;
        ~basic_string<>();
        *(undefined1 *)(unaff_EBP + -4) = 4;
        FUN_004180b0();
        *(undefined1 *)(unaff_EBP + -4) = 3;
        ~basic_string<>();
        *(undefined1 *)(unaff_EBP + -4) = 2;
        FUN_004180b0();
        *(undefined1 *)(unaff_EBP + -4) = 1;
        ~basic_string<>();
        *(undefined1 *)(unaff_EBP + -4) = 0;
        FUN_004180b0();
        *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
        ~basic_string<>();
      }
    }
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

