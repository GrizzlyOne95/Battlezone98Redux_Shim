
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00664905(void)

{
  bool bVar1;
  undefined1 uVar2;
  char cVar3;
  Root *pRVar4;
  RenderSystem *pRVar5;
  undefined4 *puVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar7;
  int iVar8;
  uint uVar9;
  undefined4 uVar10;
  RenderWindow *pRVar11;
  SceneManager *pSVar12;
  Vector3 *pVVar13;
  TextureManager *this;
  HardwarePixelBuffer *pHVar14;
  int unaff_EBP;
  code *pcVar15;
  uint uVar16;
  PixelFormat PVar17;
  int iVar18;
  ManualResourceLoader *pMVar19;
  uint uVar20;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar21;
  char *pcVar22;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar23;
  
  *(undefined4 *)(unaff_EBP + -4) = 0x1f;
  pRVar4 = Ogre::Root::getSingleton();
  pRVar5 = Ogre::Root::getRenderSystem(pRVar4);
  *(RenderSystem **)(unaff_EBP + -0x44c) = pRVar5;
  if (DAT_008ed0c4 == 1) {
    *(undefined4 *)(unaff_EBP + -0x49c) = 1;
  }
  else {
    *(undefined4 *)(unaff_EBP + -0x49c) = 0;
  }
  *(undefined1 *)(unaff_EBP + -0x446) = *(undefined1 *)(unaff_EBP + -0x49c);
  if (*(int *)(unaff_EBP + -0x44c) == 0) {
    *(undefined1 *)(unaff_EBP + -0x44d) = 0;
  }
  else {
    basic_string<>();
    *(undefined1 *)(unaff_EBP + -4) = 0x24;
    *(uint *)(unaff_EBP + -0x444) = *(uint *)(unaff_EBP + -0x444) | 8;
    (**(code **)(**(int **)(unaff_EBP + -0x44c) + 0xc))();
    FUN_004b2f10();
    uVar2 = FUN_00427270();
    *(undefined1 *)(unaff_EBP + -0x44d) = uVar2;
  }
  *(undefined1 *)(unaff_EBP + -0x454) = *(undefined1 *)(unaff_EBP + -0x44d);
  *(undefined4 *)(unaff_EBP + -4) = 0x1f;
  if ((*(uint *)(unaff_EBP + -0x444) & 8) != 0) {
    *(uint *)(unaff_EBP + -0x444) = *(uint *)(unaff_EBP + -0x444) & 0xfffffff7;
    ~basic_string<>();
  }
  if (*(int *)(unaff_EBP + -0x44c) != 0) {
    (**(code **)(**(int **)(unaff_EBP + -0x44c) + 4))();
    cVar3 = operator!=<>();
    if (cVar3 == '\0') {
      *(undefined4 *)(unaff_EBP + -0x484) = 0;
      goto LAB_00664a38;
    }
  }
  *(undefined4 *)(unaff_EBP + -0x484) = 1;
LAB_00664a38:
  *(undefined1 *)(unaff_EBP + -0x44e) = *(undefined1 *)(unaff_EBP + -0x484);
  if (((*(char *)(unaff_EBP + -0x439) == '\0') ||
      (*(char *)(unaff_EBP + -0x454) != *(char *)(unaff_EBP + -0x446))) ||
     (*(char *)(unaff_EBP + -0x44e) != '\0')) {
    *(undefined1 *)(unaff_EBP + -0x445) = 1;
    Ogre::Root::getAvailableRenderers(*(Root **)(*(int *)(unaff_EBP + -0x438) + 4));
    FUN_0041fc00();
    while( true ) {
      Ogre::Root::getAvailableRenderers(*(Root **)(*(int *)(unaff_EBP + -0x438) + 4));
      FUN_0041fc60();
      cVar3 = FID_conflict_operator__();
      if (cVar3 == '\0') break;
      puVar6 = (undefined4 *)get();
      *(undefined4 *)(unaff_EBP + -0x44c) = *puVar6;
      pbVar7 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (**(code **)(**(int **)(unaff_EBP + -0x44c) + 4))();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (unaff_EBP + -0x29c),pbVar7);
      *(undefined1 *)(unaff_EBP + -4) = 0x25;
      if (*(char *)(unaff_EBP + -0x439) == '\0') {
        FUN_004365c0();
      }
      else {
        if (*(char *)(unaff_EBP + -0x446) == '\0') {
          *(undefined **)(unaff_EBP + -0x4ac) = &DAT_00873de0;
        }
        else {
          *(undefined **)(unaff_EBP + -0x4ac) = &DAT_00873e10;
        }
        basic_string<>();
        *(undefined1 *)(unaff_EBP + -4) = 0x26;
        pcVar22 = *(char **)(unaff_EBP + -0x4ac);
        (**(code **)(**(int **)(unaff_EBP + -0x44c) + 0xc))();
        iVar8 = FUN_004b2f10();
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   (iVar8 + 0x18),pcVar22);
        *(undefined1 *)(unaff_EBP + -4) = 0x25;
        ~basic_string<>();
      }
      cVar3 = FUN_00427310();
      if (cVar3 != '\0') {
        Ogre::Root::setRenderSystem
                  (*(Root **)(*(int *)(unaff_EBP + -0x438) + 4),
                   *(RenderSystem **)(unaff_EBP + -0x44c));
      }
      FUN_00666840();
      *(undefined1 *)(unaff_EBP + -4) = 0x1f;
      ~basic_string<>();
    }
    Ogre::Root::saveConfig(*(Root **)(*(int *)(unaff_EBP + -0x438) + 4));
  }
  *(int *)(unaff_EBP + -0x468) = *(int *)(unaff_EBP + -0x468) + -1;
  if ((*(int *)(unaff_EBP + -0x468) != 0) &&
     ((*(char *)(unaff_EBP + -0x445) != '\0' || (*(char *)(unaff_EBP + -0x439) == '\0')))) {
    *(undefined1 *)(unaff_EBP + -0x445) = 0;
    *(undefined1 *)(unaff_EBP + -4) = 0x22;
    bVar1 = Ogre::Root::restoreConfig(*(Root **)(*(int *)(unaff_EBP + -0x438) + 4));
    *(bool *)(unaff_EBP + -0x451) = bVar1;
    *(undefined1 *)(unaff_EBP + -0x439) = *(undefined1 *)(unaff_EBP + -0x451);
    FUN_00664905();
    return;
  }
  if ((*(char *)(unaff_EBP + -0x445) == '\0') && (*(char *)(unaff_EBP + -0x439) != '\0')) {
    basic_string<>();
    *(undefined1 *)(unaff_EBP + -4) = 0x27;
    pRVar4 = Ogre::Root::getSingleton();
    pRVar5 = Ogre::Root::getRenderSystem(pRVar4);
    *(RenderSystem **)(unaff_EBP + -0x48c) = pRVar5;
    (**(code **)(**(int **)(unaff_EBP + -0x48c) + 0xc))();
    FUN_004b2f10();
    uVar9 = FUN_00427270();
    DAT_009183b8 = uVar9 & 0xff;
    *(undefined1 *)(unaff_EBP + -4) = 0x1f;
    ~basic_string<>();
    pRVar5 = Ogre::Root::getRenderSystem(*(Root **)(*(int *)(unaff_EBP + -0x438) + 4));
    *(RenderSystem **)(unaff_EBP + -0x440) = pRVar5;
    (**(code **)(**(int **)(unaff_EBP + -0x440) + 4))();
    cVar3 = FUN_00427270();
    if (cVar3 != '\0') {
      basic_string<>();
      *(undefined1 *)(unaff_EBP + -4) = 0x28;
      (**(code **)(**(int **)(unaff_EBP + -0x440) + 0xc))();
      iVar8 = FUN_004b2f10();
      *(int *)(unaff_EBP + -0x4d8) = iVar8 + 0x30;
      *(undefined1 *)(unaff_EBP + -4) = 0x1f;
      ~basic_string<>();
      if ((_DAT_00920ed4 < 1) && ((_DAT_00920ed4 != 0 || (uVar9 = FUN_0048a830(), uVar9 < 2)))) {
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
    cVar3 = FUN_00427270();
    if (cVar3 == '\0') {
      (**(code **)(**(int **)(unaff_EBP + -0x440) + 4))();
      cVar3 = FUN_00427270();
      if (cVar3 != '\0') {
        uVar10 = (**(code **)(**(int **)(unaff_EBP + -0x440) + 0xc))();
        *(undefined4 *)(unaff_EBP + -0x494) = uVar10;
        basic_string<>();
        *(undefined1 *)(unaff_EBP + -4) = 0x30;
        FUN_00420350();
        *(undefined1 *)(unaff_EBP + -4) = 0x1f;
        ~basic_string<>();
        FID_conflict_begin();
        cVar3 = FUN_00420f10();
        if (cVar3 != '\0') {
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
        pcVar22 = "Yes";
        (**(code **)(**(int **)(unaff_EBP + -0x440) + 0xc))();
        iVar8 = FUN_004b2f10();
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   (iVar8 + 0x18),pcVar22);
        *(undefined1 *)(unaff_EBP + -4) = 0x1f;
        ~basic_string<>();
      }
    }
    else {
      uVar10 = (**(code **)(**(int **)(unaff_EBP + -0x440) + 0xc))();
      *(undefined4 *)(unaff_EBP + -0x4a4) = uVar10;
      basic_string<>();
      *(undefined1 *)(unaff_EBP + -4) = 0x2d;
      FUN_00420350();
      *(undefined1 *)(unaff_EBP + -4) = 0x1f;
      ~basic_string<>();
      FID_conflict_begin();
      cVar3 = FUN_00420f10();
      if (cVar3 != '\0') {
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
    uVar10 = FUN_00663de0();
    *(undefined4 *)(unaff_EBP + -0x4f0) = uVar10;
    *(undefined4 *)(unaff_EBP + -0x4c0) = *(undefined4 *)(unaff_EBP + -0x4f0);
    *(undefined1 *)(unaff_EBP + -4) = 0x34;
    FUN_00449810();
    *(undefined1 *)(unaff_EBP + -4) = 0x1f;
    ~basic_string<>();
    pbVar23 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
              &DAT_025f8dc8;
    pbVar7 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (unaff_EBP + 8);
    bVar1 = (bool)FUN_00435a30();
    pRVar11 = Ogre::Root::initialise
                        (*(Root **)(*(int *)(unaff_EBP + -0x438) + 4),bVar1,pbVar7,pbVar23);
    *(RenderWindow **)(*(int *)(unaff_EBP + -0x438) + 0xc) = pRVar11;
    if (*(int *)(*(int *)(unaff_EBP + -0x438) + 0xc) == 0) {
      uVar10 = FUN_00435a40();
      *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 0xc) = uVar10;
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
      cVar3 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0xc) + 0x144))();
      if (cVar3 == '\0') {
        *(undefined4 *)(unaff_EBP + -0x474) = 1;
      }
      else {
        *(undefined4 *)(unaff_EBP + -0x474) = 0;
      }
      *(undefined1 *)(*(int *)(unaff_EBP + -0x438) + 0x54) = *(undefined1 *)(unaff_EBP + -0x474);
      uVar10 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0xc) + 0x10))();
      *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 0x50) = uVar10;
      uVar10 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0xc) + 0xc))();
      *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 0x4c) = uVar10;
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
      uVar10 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 8) + 0x104))();
      *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 0x10) = uVar10;
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
      uVar10 = FUN_0044c7a0();
      *(undefined1 **)(unaff_EBP + -0x550) = &stack0xffffffec;
      FUN_00662df0(uVar10);
      FUN_00663910(unaff_EBP + -0x55c);
      (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0x10) + 0x138))();
      Ogre::Camera::setAutoAspectRatio(*(Camera **)(*(int *)(unaff_EBP + -0x438) + 0x10),true);
      basic_string<>();
      *(undefined1 *)(unaff_EBP + -4) = 0x36;
      uVar10 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 8) + 0x104))();
      *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 0x14) = uVar10;
      *(undefined1 *)(unaff_EBP + -4) = 0x1f;
      ~basic_string<>();
      (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0x14) + 0x140))(0x3dcccccd);
      Ogre::MovableObject::setCastShadows
                (*(MovableObject **)(*(int *)(unaff_EBP + -0x438) + 0x14),false);
      Ogre::Camera::setAutoAspectRatio(*(Camera **)(*(int *)(unaff_EBP + -0x438) + 0x14),true);
      basic_string<>("SniperCam");
      *(undefined1 *)(unaff_EBP + -4) = 0x37;
      uVar10 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 8) + 0x104))
                         (unaff_EBP + -0x3d4);
      *(undefined4 *)(*(int *)(unaff_EBP + -0x438) + 0x18) = uVar10;
      *(undefined1 *)(unaff_EBP + -4) = 0x1f;
      ~basic_string<>();
      (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x438) + 0x18) + 0x140))(0x3dcccccd);
      Ogre::MovableObject::setCastShadows
                (*(MovableObject **)(*(int *)(unaff_EBP + -0x438) + 0x18),false);
      Ogre::Camera::setAutoAspectRatio(*(Camera **)(*(int *)(unaff_EBP + -0x438) + 0x18),true);
      Ogre::Camera::setPosition(*(Camera **)(*(int *)(unaff_EBP + -0x438) + 0x18),100.0,100.0,100.0)
      ;
      basic_string<>("SniperTex");
      *(undefined1 *)(unaff_EBP + -4) = 0x38;
      pbVar21 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)0x0;
      uVar20 = 0;
      bVar1 = false;
      pMVar19 = (ManualResourceLoader *)0x20;
      iVar18 = 0x1a;
      PVar17 = 0;
      iVar8 = 0x200;
      uVar16 = 0x200;
      uVar9 = 2;
      pbVar7 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (unaff_EBP + -0x17c);
      pbVar23 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                (unaff_EBP + -0x504);
      pcVar15 = DEFAULT_RESOURCE_GROUP_NAME_exref;
      this = Ogre::TextureManager::getSingleton();
      Ogre::TextureManager::createManual
                (this,pbVar23,pbVar7,(TextureType)pcVar15,uVar9,uVar16,iVar8,PVar17,iVar18,pMVar19,
                 bVar1,uVar20,pbVar21);
      *(undefined1 *)(unaff_EBP + -4) = 0x3a;
      ~basic_string<>();
      uVar10 = get();
      *(undefined4 *)(unaff_EBP + -0x480) = uVar10;
      uVar10 = (**(code **)(**(int **)(unaff_EBP + -0x480) + 0x15c))(unaff_EBP + -0x53c,0,0);
      *(undefined4 *)(unaff_EBP + -0x4c4) = uVar10;
      *(undefined4 *)(unaff_EBP + -0x4cc) = *(undefined4 *)(unaff_EBP + -0x4c4);
      *(undefined1 *)(unaff_EBP + -4) = 0x3b;
      pHVar14 = Ogre::SharedPtr<class_Ogre::HardwarePixelBuffer>::operator->
                          (*(SharedPtr<class_Ogre::HardwarePixelBuffer> **)(unaff_EBP + -0x4cc));
      *(HardwarePixelBuffer **)(unaff_EBP + -0x488) = pHVar14;
      DAT_00920e80 = (**(code **)(**(int **)(unaff_EBP + -0x488) + 0x40))(0);
      *(undefined1 *)(unaff_EBP + -4) = 0x3a;
      Ogre::HardwarePixelBufferSharedPtr::~HardwarePixelBufferSharedPtr
                ((HardwarePixelBufferSharedPtr *)(unaff_EBP + -0x53c));
      uVar2 = FUN_00435a50();
      *(undefined1 *)(unaff_EBP + -0x44f) = uVar2;
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
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

