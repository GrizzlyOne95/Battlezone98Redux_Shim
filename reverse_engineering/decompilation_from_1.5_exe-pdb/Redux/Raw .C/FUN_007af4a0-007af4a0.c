
void FUN_007af4a0(void)

{
  char cVar1;
  undefined4 uVar2;
  Root *pRVar3;
  int iVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  char *pcVar6;
  undefined4 *puVar7;
  undefined1 *puVar8;
  int *piVar9;
  char *pcVar10;
  int *piVar11;
  undefined1 local_3f0 [4];
  undefined4 local_3ec;
  undefined4 local_3e8;
  undefined4 local_3e4;
  undefined4 local_3e0;
  undefined4 local_3dc;
  undefined4 local_3d8;
  undefined4 local_3d4;
  int *local_3d0;
  undefined4 local_3cc;
  undefined4 local_3c8;
  int *local_3c4;
  int local_3c0;
  undefined4 local_3bc;
  int local_3b8;
  undefined4 local_3b4;
  undefined4 local_3b0;
  undefined4 local_3ac;
  undefined4 local_3a8;
  undefined4 local_3a4;
  int *local_3a0;
  undefined4 local_39c;
  int local_398;
  undefined4 local_394;
  undefined4 local_390;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_38c;
  undefined4 local_388;
  int *local_384;
  int *local_380;
  undefined4 local_37c;
  undefined4 local_378;
  undefined4 local_374;
  int *local_370;
  int *local_36c;
  undefined4 local_368;
  undefined4 local_364;
  int *local_360;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_35c;
  undefined4 local_358;
  undefined4 local_354;
  undefined4 local_350;
  undefined4 local_34c;
  undefined4 local_348;
  undefined4 local_344;
  RenderSystem *local_340;
  undefined4 local_33c;
  undefined4 local_338;
  undefined4 local_334;
  undefined4 local_330;
  undefined4 local_32c;
  int *local_328;
  undefined4 local_324;
  undefined4 local_320;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_31c;
  void *local_318;
  int *local_314;
  int *local_310;
  undefined4 local_30c;
  void *local_308;
  void *local_304;
  undefined4 local_300;
  undefined4 local_2fc;
  void *local_2f8;
  int *local_2f4;
  RenderSystem *local_2f0;
  undefined4 local_2ec;
  RenderSystem *local_2e8;
  undefined4 local_2e4;
  int *local_2e0;
  undefined4 local_2dc;
  void *local_2d8;
  undefined4 local_2d4;
  undefined4 local_2d0;
  RenderSystem *local_2cc;
  void *local_2c8;
  int *local_2c4;
  int *local_2c0;
  undefined4 local_2bc;
  void *local_2b8;
  undefined4 local_2b4;
  int *local_2b0;
  undefined4 local_2ac;
  void *local_2a8;
  RenderSystem *local_2a4;
  undefined4 local_2a0;
  void *local_29c;
  void *local_298;
  void *local_294;
  undefined4 local_290;
  void *local_28c;
  void *local_288;
  void *local_284;
  undefined4 local_280;
  undefined4 local_27c;
  void *local_278;
  RenderSystem *local_274;
  int local_270;
  void *local_26c;
  undefined4 local_268;
  void *local_264;
  void *local_260;
  void *local_25c;
  int *local_258;
  void *local_254;
  void *local_250;
  void *local_24c;
  undefined4 local_248;
  void *local_244;
  undefined4 local_240;
  void *local_23c;
  void *local_238;
  void *local_234;
  int *local_230;
  RenderSystem *local_22c;
  void *local_228;
  undefined4 local_224;
  undefined4 local_220;
  void *local_21c;
  int *local_218;
  int *local_214;
  int *local_210;
  undefined1 local_20c [4];
  int local_208;
  int *local_204;
  int *local_200;
  undefined4 local_1fc;
  int local_1f8;
  int *local_1f4;
  int *local_1f0;
  int local_1ec;
  int local_1e8;
  int local_1e4;
  RenderSystem *local_1e0;
  int local_1dc;
  int *local_1d8;
  int local_1d4;
  int local_1d0;
  int local_1cc;
  int local_1c8;
  int *local_1c4;
  int local_1c0;
  undefined4 local_1bc;
  float local_1b8;
  float local_1b4;
  undefined4 local_1b0;
  RenderSystem *local_1ac;
  float local_1a8;
  undefined4 *local_1a4;
  undefined1 local_1a0 [24];
  undefined1 local_188 [24];
  undefined1 local_170 [24];
  undefined1 local_158 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_140 [24];
  undefined1 local_128 [24];
  undefined1 local_110 [24];
  undefined1 local_f8 [24];
  undefined1 local_e0 [24];
  undefined1 local_c8 [24];
  undefined1 local_b0 [24];
  undefined1 local_98 [24];
  undefined1 local_80 [24];
  undefined1 local_68 [24];
  undefined1 local_50 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_38 [24];
  char local_20 [12];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861013;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0(local_14);
  local_8 = 0;
  *local_1a4 = cUI_OptionsGraphics::vftable;
  local_1a4[0x5e] = 0;
  *(undefined1 *)(local_1a4 + 0x67) = 0;
  *(undefined1 *)((int)local_1a4 + 0x19d) = 0;
  *(undefined1 *)((int)local_1a4 + 0x19e) = 0;
  *(undefined1 *)((int)local_1a4 + 0x19f) = 0;
  *(undefined1 *)(local_1a4 + 0x68) = 0;
  *(undefined1 *)((int)local_1a4 + 0x1a1) = 0;
  DAT_0260baac = (int)*(char *)(DAT_0094672c + 0x25);
  DAT_0260baa8 = (uint)*(byte *)(DAT_0094672c + 0x27);
  uVar2 = FUN_0067c950();
  local_1a4[0x51] = uVar2;
  DAT_009455a4 = local_1a4;
  *(undefined1 *)((int)local_1a4 + 0x1a2) = 0;
  local_238 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (local_238 == (void *)0x0) {
    local_2a0 = 0;
  }
  else {
    local_2a0 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_3c8 = local_2a0;
  local_8._0_1_ = 0;
  local_1a4[99] = local_2a0;
  FUN_007d3f20(1);
  FUN_007d2870("goptions_center.png");
  FUN_007d2110(local_1a4[99],0);
  local_378 = FUN_0081cb40("graphic_options",&DAT_008714b0);
  local_354 = FUN_0081cb40("graphic_options",&DAT_0089f818);
  local_388 = FUN_0081cb40("graphic_options","monitor");
  local_3a8 = FUN_0081cb40("graphic_options","screen_resolution");
  local_3bc = FUN_0081cb40("graphic_options","vehicle_shadows");
  local_33c = FUN_0081cb40("graphic_options",&DAT_0089f800);
  local_364 = FUN_0081cb40("graphic_options","fullscreen");
  local_3d8 = FUN_0081cb40("graphic_options","anisotropic");
  local_350 = FUN_0081cb40("graphic_options","apply");
  local_368 = FUN_0081cb40("graphic_options","detail");
  local_1fc = FUN_0081cb40("option_box",&DAT_0089e9fc);
  local_248 = FUN_0081cb40("option_box",&DAT_008712f4);
  local_3ec = FUN_0081cb40("graphic_options","terrain_dist");
  local_2a8 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (local_2a8 == (void *)0x0) {
    local_2b0 = (int *)0x0;
  }
  else {
    local_2b0 = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_370 = local_2b0;
  local_8._0_1_ = 0;
  local_1c4 = local_2b0;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_1c4 + 0x40))("topcrnhv.png");
  (**(code **)(*local_1c4 + 0x3c))("topcrnck.png");
  FUN_007c2950(local_378);
  FUN_007c23e0(FUN_007ae800);
  FUN_007d2110(local_1c4,0);
  local_1a8 = 190.0;
  local_1b8 = 55.0;
  local_1b0 = 0x43c80000;
  local_1b4 = 10.0;
  local_1bc = 0x436e0000;
  if ((local_1a4[0x51] == 2) || (local_1a4[0x51] == 3)) {
    local_2b8 = operator_new(0x294c);
    local_8._0_1_ = 3;
    if (local_2b8 == (void *)0x0) {
      local_2c0 = (int *)0x0;
    }
    else {
      local_2c0 = (int *)FUN_007ccb70("Monitor",local_1b0,local_1a8 + local_1b4,local_1bc,0x43160000
                                      ,0x20,local_1a4[99]);
    }
    local_380 = local_2c0;
    local_8._0_1_ = 0;
    local_200 = local_2c0;
    (**(code **)(*local_2c0 + 0x3c))(local_388,3);
    FUN_007d2110(local_200,0);
    pRVar3 = Ogre::Root::getSingleton();
    local_1ac = Ogre::Root::getRenderSystem(pRVar3);
    basic_string<>("Rendering Device");
    local_8._0_1_ = 4;
    puVar8 = local_c8;
    (**(code **)(*(int *)local_1ac + 0xc))(puVar8);
    local_1ec = FUN_004b2f10(puVar8);
    local_1ec = local_1ec + 0x30;
    local_8._0_1_ = 0;
    ~basic_string<>();
    basic_string<>("Rendering Device");
    local_8._0_1_ = 5;
    puVar8 = local_188;
    (**(code **)(*(int *)local_1ac + 0xc))(puVar8);
    iVar4 = FUN_004b2f10(puVar8);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_38,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(iVar4 + 0x18));
    local_8._0_1_ = 7;
    ~basic_string<>();
    basic_string<>("Video Mode");
    local_8._0_1_ = 8;
    puVar8 = local_f8;
    (**(code **)(*(int *)local_1ac + 0xc))(puVar8);
    iVar4 = FUN_004b2f10(puVar8);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_140,
               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (iVar4 + 0x18));
    local_8._0_1_ = 10;
    ~basic_string<>();
    local_2c8 = operator_new(500);
    local_8._0_1_ = 0xb;
    if (local_2c8 == (void *)0x0) {
      local_2d0 = 0;
    }
    else {
      local_2d0 = FUN_007c3150("adapterChecklist",0x44244000,local_1a8,0x43010000,0x421c0000,0,
                               local_1a4[99]);
    }
    local_390 = local_2d0;
    local_8._0_1_ = 10;
    local_1a4[0x52] = local_2d0;
    local_1e4 = 0;
    local_1d0 = 0;
    while( true ) {
      iVar4 = FUN_0048a830();
      if (iVar4 <= local_1d0) break;
      FUN_006cf480(local_1d0);
      uVar2 = FUN_0041f870();
      basic_string<>(uVar2);
      local_8._0_1_ = 0xc;
      basic_string<>("Rendering Device");
      local_8._0_1_ = 0xd;
      puVar8 = local_80;
      (**(code **)(*(int *)local_1ac + 0x10))(local_68,puVar8);
      local_8._0_1_ = 0xc;
      ~basic_string<>();
      local_8._0_1_ = 10;
      ~basic_string<>();
      basic_string<>("Video Mode");
      local_8._0_1_ = 0xe;
      (**(code **)(*(int *)local_1ac + 0xc))(local_b0);
      FUN_004b2f10(puVar8);
      local_398 = FUN_0048a830();
      local_8._0_1_ = 10;
      ~basic_string<>();
      if (local_398 != 0) {
        iVar4 = local_1e4;
        FUN_006cf480(local_1d0);
        uVar2 = FUN_0041f870(iVar4);
        FUN_007c3ac0(uVar2,iVar4);
        pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_006cf480(local_1d0);
        iVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                compare(local_38,pbVar5);
        if (iVar4 == 0) {
          FUN_007c3c10(local_1e4);
        }
        local_1e4 = local_1e4 + 1;
      }
      local_1d0 = local_1d0 + 1;
    }
    basic_string<>("Rendering Device");
    local_8._0_1_ = 0xf;
    (**(code **)(*(int *)local_1ac + 0x10))(local_e0,local_38);
    local_8._0_1_ = 10;
    ~basic_string<>();
    basic_string<>("Video Mode");
    local_8._0_1_ = 0x10;
    (**(code **)(*(int *)local_1ac + 0x10))(local_110,local_140);
    local_8._0_1_ = 10;
    ~basic_string<>();
    FUN_007c3cf0(FUN_007ae870);
    FUN_007d2110(local_1a4[0x52],0);
    local_8._0_1_ = 7;
    ~basic_string<>();
    local_8._0_1_ = 0;
    ~basic_string<>();
  }
  else {
    local_1a4[0x52] = 0;
  }
  local_1a8 = local_1a8 + local_1b8;
  local_2d8 = operator_new(0x294c);
  local_8._0_1_ = 0x11;
  if (local_2d8 == (void *)0x0) {
    local_2e0 = (int *)0x0;
  }
  else {
    local_2e0 = (int *)FUN_007ccb70("Resolution",local_1b0,local_1a8 + local_1b4,local_1bc,
                                    0x43160000,0x20,local_1a4[99]);
  }
  local_3a0 = local_2e0;
  local_8._0_1_ = 0;
  local_204 = local_2e0;
  (**(code **)(*local_2e0 + 0x3c))(local_3a8,3);
  FUN_007d2110(local_204,0);
  basic_string<>("Video Mode");
  local_8._0_1_ = 0x12;
  pRVar3 = Ogre::Root::getSingleton();
  local_2e8 = Ogre::Root::getRenderSystem(pRVar3);
  puVar8 = local_170;
  (**(code **)(*(int *)local_2e8 + 0xc))(puVar8);
  local_1dc = FUN_004b2f10(puVar8);
  local_1dc = local_1dc + 0x30;
  local_8._0_1_ = 0;
  ~basic_string<>();
  basic_string<>("Video Mode");
  local_8._0_1_ = 0x13;
  pRVar3 = Ogre::Root::getSingleton();
  local_2f0 = Ogre::Root::getRenderSystem(pRVar3);
  puVar8 = local_1a0;
  (**(code **)(*(int *)local_2f0 + 0xc))(puVar8);
  iVar4 = FUN_004b2f10(puVar8);
  local_31c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
              (iVar4 + 0x18);
  local_8._0_1_ = 0;
  ~basic_string<>();
  local_2f8 = operator_new(500);
  local_8._0_1_ = 0x14;
  if (local_2f8 == (void *)0x0) {
    local_300 = 0;
  }
  else {
    local_300 = FUN_007c3150("resChecklist",0x44244000,local_1a8,0x43010000,0x421c0000,0,
                             local_1a4[99]);
  }
  local_3b0 = local_300;
  local_8._0_1_ = 0;
  local_1a4[0x55] = local_300;
  local_1c0 = 0;
  while( true ) {
    iVar4 = FUN_0048a830();
    if (iVar4 <= local_1c0) break;
    pcVar10 = "16-bit";
    FUN_006cf480(local_1c0);
    pcVar6 = (char *)FUN_0041f870();
    pcVar6 = strstr(pcVar6,pcVar10);
    if (pcVar6 == (char *)0x0) {
      piVar11 = &local_3c0;
      piVar9 = &local_3b8;
      pcVar10 = "%d x %d";
      FUN_006cf480(local_1c0);
      pcVar6 = (char *)FUN_0041f870(pcVar10,piVar9,piVar11);
      sscanf(pcVar6,pcVar10);
      if ((0x3ff < local_3b8) && (0x2cf < local_3c0)) {
        iVar4 = local_1c0;
        FUN_006cf480(local_1c0);
        uVar2 = FUN_0041f870(iVar4);
        FUN_007c3ac0(uVar2,iVar4);
        pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_006cf480(local_1c0);
        iVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                compare(local_31c,pbVar5);
        if (iVar4 == 0) {
          FUN_007c3c10(local_1c0);
        }
      }
    }
    local_1c0 = local_1c0 + 1;
  }
  FUN_007c3cf0(FUN_007ae820);
  FUN_007d2110(local_1a4[0x55],0);
  local_1a8 = local_1a8 + local_1b8;
  local_308 = operator_new(0x294c);
  local_8._0_1_ = 0x15;
  if (local_308 == (void *)0x0) {
    local_310 = (int *)0x0;
  }
  else {
    local_310 = (int *)FUN_007ccb70("aniso",local_1b0,local_1a8 + local_1b4,local_1bc,0x43160000,
                                    0x20,local_1a4[99]);
  }
  local_3d0 = local_310;
  local_8._0_1_ = 0;
  local_1f4 = local_310;
  (**(code **)(*local_310 + 0x3c))(local_3d8,3);
  FUN_007d2110(local_1f4,0);
  local_318 = operator_new(500);
  local_8._0_1_ = 0x16;
  if (local_318 == (void *)0x0) {
    local_224 = 0;
  }
  else {
    local_224 = FUN_007c3150("anisoChecklist",0x44244000,local_1a8,0x43010000,0x421c0000,0,
                             local_1a4[99]);
  }
  local_3e0 = local_224;
  local_8 = (uint)local_8._1_3_ << 8;
  local_1a4[0x56] = local_224;
  FUN_007c3ac0(local_1fc,0);
  for (local_1d4 = 1; local_1d4 < 5; local_1d4 = local_1d4 + 1) {
    _snprintf(local_20,10,"%d",1 << ((char)local_1d4 - 1U & 0x1f));
    FUN_007c3ac0(local_20,local_1d4);
  }
  FUN_007c3c10(*(undefined1 *)(DAT_0094672c + 0x24));
  FUN_007c3cf0(FUN_007ae850);
  FUN_007d2110(local_1a4[0x56],0);
  local_1a8 = local_1a8 + local_1b8;
  local_298 = operator_new(0x294c);
  local_8._0_1_ = 0x17;
  if (local_298 == (void *)0x0) {
    local_2dc = 0;
  }
  else {
    local_2dc = FUN_007ccb70("FullScreen",local_1b0,local_1a8 + local_1b4,local_1bc,0x43160000,0x20,
                             local_1a4[99]);
  }
  local_3e8 = local_2dc;
  local_8._0_1_ = 0;
  local_1a4[0x60] = local_2dc;
  (**(code **)(*(int *)local_1a4[0x60] + 0x3c))(local_364,3);
  FUN_007d2110(local_1a4[0x60],0);
  basic_string<>("Full Screen");
  local_8._0_1_ = 0x18;
  pRVar3 = Ogre::Root::getSingleton();
  local_22c = Ogre::Root::getRenderSystem(pRVar3);
  puVar8 = local_158;
  (**(code **)(*(int *)local_22c + 0xc))(puVar8);
  local_1f8 = FUN_004b2f10(puVar8);
  local_1f8 = local_1f8 + 0x30;
  local_8._0_1_ = 0;
  ~basic_string<>();
  basic_string<>("Full Screen");
  local_8._0_1_ = 0x19;
  pRVar3 = Ogre::Root::getSingleton();
  local_2a4 = Ogre::Root::getRenderSystem(pRVar3);
  puVar8 = local_98;
  (**(code **)(*(int *)local_2a4 + 0xc))(puVar8);
  iVar4 = FUN_004b2f10(puVar8);
  local_38c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
              (iVar4 + 0x18);
  local_8._0_1_ = 0;
  ~basic_string<>();
  local_234 = operator_new(500);
  local_8._0_1_ = 0x1a;
  if (local_234 == (void *)0x0) {
    local_2fc = 0;
  }
  else {
    local_2fc = FUN_007c3150("screenChecklist",0x44244000,local_1a8,0x43010000,0x421c0000,0,
                             local_1a4[99]);
  }
  local_324 = local_2fc;
  local_8._0_1_ = 0;
  local_1a4[0x54] = local_2fc;
  local_1cc = 0;
  while( true ) {
    iVar4 = FUN_0048a830();
    if (iVar4 <= local_1cc) break;
    iVar4 = local_1cc;
    FUN_006cf480(local_1cc);
    uVar2 = FUN_0041f870(iVar4);
    FUN_007c3ac0(uVar2,iVar4);
    pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_006cf480(local_1cc);
    iVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            compare(local_38c,pbVar5);
    if (iVar4 == 0) {
      FUN_007c3c10(local_1cc);
    }
    local_1cc = local_1cc + 1;
  }
  FUN_007c3cf0(FUN_007ae830);
  FUN_007d2110(local_1a4[0x54],0);
  local_1a8 = local_1a8 + local_1b8;
  local_23c = operator_new(0x294c);
  local_8._0_1_ = 0x1b;
  if (local_23c == (void *)0x0) {
    local_2ac = 0;
  }
  else {
    local_2ac = FUN_007ccb70("Vehicles",local_1b0,local_1a8 + local_1b4,local_1bc,0x43160000,0x20,
                             local_1a4[99]);
  }
  local_32c = local_2ac;
  local_8._0_1_ = 0;
  local_1a4[0x5f] = local_2ac;
  (**(code **)(*(int *)local_1a4[0x5f] + 0x3c))(local_3bc,3);
  FUN_007d2110(local_1a4[0x5f],0);
  local_244 = operator_new(500);
  local_8._0_1_ = 0x1c;
  if (local_244 == (void *)0x0) {
    local_2e4 = 0;
  }
  else {
    local_2e4 = FUN_007c3150("vehicleChecklist",0x44244000,local_1a8,0x43010000,0x421c0000,0,
                             local_1a4[99]);
  }
  local_334 = local_2e4;
  local_8._0_1_ = 0;
  local_1a4[0x57] = local_2e4;
  FUN_007c3cf0(FUN_007ae880);
  FUN_007d2110(local_1a4[0x57],0);
  local_1a8 = local_1a8 + local_1b8;
  local_24c = operator_new(0x294c);
  local_8._0_1_ = 0x1d;
  if (local_24c == (void *)0x0) {
    local_2b4 = 0;
  }
  else {
    local_2b4 = FUN_007ccb70(&DAT_0089d35c,local_1b0,local_1a8 + local_1b4,local_1bc,0x43160000,0x20
                             ,local_1a4[99]);
  }
  local_394 = local_2b4;
  local_8._0_1_ = 0;
  local_1a4[0x61] = local_2b4;
  (**(code **)(*(int *)local_1a4[0x61] + 0x3c))(local_33c,3);
  FUN_007d2110(local_1a4[0x61],0);
  local_254 = operator_new(500);
  local_8._0_1_ = 0x1e;
  if (local_254 == (void *)0x0) {
    local_30c = 0;
  }
  else {
    local_30c = FUN_007c3150("hudChecklist",0x44244000,local_1a8,0x43010000,0x421c0000,0,
                             local_1a4[99]);
  }
  local_3d4 = local_30c;
  local_8._0_1_ = 0;
  local_1a4[0x58] = local_30c;
  FUN_007b1f50();
  FUN_007c3c10(*(undefined1 *)(DAT_0094672c + 0x26));
  FUN_007c3cf0(FUN_007ae890);
  FUN_007d2110(local_1a4[0x58],0);
  local_1a8 = local_1a8 + local_1b8;
  local_39c = FUN_0081cb40("option_box","display_hud");
  local_25c = operator_new(0x294c);
  local_8._0_1_ = 0x1f;
  if (local_25c == (void *)0x0) {
    local_2bc = 0;
  }
  else {
    local_2bc = FUN_007ccb70(&DAT_0089d35c,local_1b0,local_1a8 + local_1b4,local_1bc,0x43160000,0x20
                             ,local_1a4[99]);
  }
  local_344 = local_2bc;
  local_8._0_1_ = 0;
  local_1a4[0x62] = local_2bc;
  (**(code **)(*(int *)local_1a4[0x62] + 0x3c))(local_39c,3);
  FUN_007d2110(local_1a4[0x62],0);
  local_264 = operator_new(500);
  local_8._0_1_ = 0x20;
  if (local_264 == (void *)0x0) {
    local_2ec = 0;
  }
  else {
    local_2ec = FUN_007c3150("mHudOnOffChecklist",0x44244000,local_1a8,0x43010000,0x421c0000,0,
                             local_1a4[99]);
  }
  local_34c = local_2ec;
  local_8._0_1_ = 0;
  local_1a4[0x59] = local_2ec;
  FUN_007c3ac0(local_1fc,0);
  FUN_007c3ac0(local_248,1);
  FUN_007c3c10(DAT_008eaab0);
  FUN_007c3cf0(FUN_007ae8a0);
  FUN_007d2110(local_1a4[0x59],0);
  local_1a8 = local_1a8 + local_1b8;
  local_26c = operator_new(0x294c);
  local_8._0_1_ = 0x21;
  if (local_26c == (void *)0x0) {
    local_2c4 = (int *)0x0;
  }
  else {
    local_2c4 = (int *)FUN_007ccb70(&DAT_00873e08,local_1b0,local_1a8 + local_1b4,local_1bc,
                                    0x43160000,0x20,local_1a4[99]);
  }
  local_3c4 = local_2c4;
  local_8._0_1_ = 0;
  local_1f0 = local_2c4;
  (**(code **)(*local_2c4 + 0x3c))(local_354,3);
  FUN_007d2110(local_1f0,0);
  basic_string<>(&DAT_00873e08);
  local_8._0_1_ = 0x22;
  pRVar3 = Ogre::Root::getSingleton();
  local_274 = Ogre::Root::getRenderSystem(pRVar3);
  puVar8 = local_50;
  (**(code **)(*(int *)local_274 + 0xc))(puVar8);
  local_208 = FUN_004b2f10(puVar8);
  local_208 = local_208 + 0x30;
  local_8._0_1_ = 0;
  ~basic_string<>();
  local_304 = operator_new(500);
  local_8._0_1_ = 0x23;
  if (local_304 == (void *)0x0) {
    local_27c = 0;
  }
  else {
    local_27c = FUN_007c3150("fsaaChecklist",0x44244000,local_1a8,0x43010000,0x421c0000,0,
                             local_1a4[99]);
  }
  local_3a4 = local_27c;
  local_8._0_1_ = 0;
  local_1a4[0x53] = local_27c;
  basic_string<>(&DAT_00873e08);
  local_8._0_1_ = 0x24;
  pRVar3 = Ogre::Root::getSingleton();
  local_2cc = Ogre::Root::getRenderSystem(pRVar3);
  puVar8 = local_128;
  (**(code **)(*(int *)local_2cc + 0xc))(puVar8);
  iVar4 = FUN_004b2f10(puVar8);
  local_35c = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
              (iVar4 + 0x18);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_1c8 = 0;
  while( true ) {
    iVar4 = FUN_0048a830();
    if (iVar4 <= local_1c8) break;
    iVar4 = local_1c8;
    FUN_006cf480(local_1c8);
    uVar2 = FUN_0041f870(iVar4);
    FUN_007c3ac0(uVar2,iVar4);
    pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_006cf480(local_1c8);
    iVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            compare(local_35c,pbVar5);
    if (iVar4 == 0) {
      FUN_007c3c10(local_1c8);
    }
    local_1c8 = local_1c8 + 1;
  }
  FUN_007c3cf0(FUN_007ae840);
  FUN_007d2110(local_1a4[0x53],0);
  local_1a8 = local_1a8 + local_1b8;
  local_284 = operator_new(0x294c);
  local_8._0_1_ = 0x25;
  if (local_284 == (void *)0x0) {
    local_2f4 = (int *)0x0;
  }
  else {
    local_2f4 = (int *)FUN_007ccb70("DETAIL",local_1b0,local_1a8 + local_1b4,local_1bc,0x43160000,
                                    0x20,local_1a4[99]);
  }
  local_360 = local_2f4;
  local_8._0_1_ = 0;
  local_210 = local_2f4;
  (**(code **)(*local_2f4 + 0x3c))(local_368,3);
  FUN_007d2110(local_210,0);
  local_28c = operator_new(500);
  local_8._0_1_ = 0x26;
  if (local_28c == (void *)0x0) {
    local_2d4 = 0;
  }
  else {
    local_2d4 = FUN_007c3150("detailChecklist",0x44244000,local_1a8,0x43010000,0x421c0000,0,
                             local_1a4[99]);
  }
  local_3e4 = local_2d4;
  local_8._0_1_ = 0;
  local_1a4[0x5a] = local_2d4;
  FUN_007c3cf0(FUN_007ae8b0);
  FUN_007d2110(local_1a4[0x5a],0);
  FUN_007ae5b0();
  local_1a8 = local_1a8 + local_1b8;
  local_3ac = FUN_0081cb40("graphic_options","cockpit_display");
  local_3cc = FUN_0081cb40("cockpit_display",&DAT_008865a8);
  local_37c = FUN_0081cb40("cockpit_display",&DAT_00892b00);
  local_3b4 = FUN_0081cb40("cockpit_display",&DAT_00892af0);
  local_294 = operator_new(0x294c);
  local_8._0_1_ = 0x27;
  if (local_294 == (void *)0x0) {
    local_314 = (int *)0x0;
  }
  else {
    local_314 = (int *)FUN_007ccb70("COCKPIT",local_1b0,local_1a8 + local_1b4,local_1bc,0x43160000,
                                    0x20,local_1a4[99]);
  }
  local_36c = local_314;
  local_8._0_1_ = 0;
  local_218 = local_314;
  (**(code **)(*local_314 + 0x3c))(local_3ac,3);
  FUN_007d2110(local_218,0);
  local_29c = operator_new(500);
  local_8._0_1_ = 0x28;
  if (local_29c == (void *)0x0) {
    local_220 = 0;
  }
  else {
    local_220 = FUN_007c3150("cockpitChecklist",0x44244000,local_1a8,0x43010000,0x421c0000,0,
                             local_1a4[99]);
  }
  local_374 = local_220;
  local_8._0_1_ = 0;
  local_1a4[0x5b] = local_220;
  FUN_007c3ac0(local_3cc,0);
  FUN_007c3ac0(local_37c,1);
  FUN_007c3ac0(local_3b4,2);
  FUN_007c3c10(*(undefined1 *)(DAT_0094672c + 0x17));
  FUN_007c3cf0(FUN_007ae8c0);
  FUN_007d2110(local_1a4[0x5b],0);
  local_1a8 = local_1a8 + local_1b8;
  local_3dc = FUN_0081cb40("graphic_options","screen_glow");
  local_228 = operator_new(0x294c);
  local_8._0_1_ = 0x29;
  if (local_228 == (void *)0x0) {
    local_230 = (int *)0x0;
  }
  else {
    local_230 = (int *)FUN_007ccb70(&DAT_0089f90c,local_1b0,local_1a8 + local_1b4,local_1bc,
                                    0x422c0000,0x20,local_1a4[99]);
  }
  local_384 = local_230;
  local_8._0_1_ = 0;
  local_214 = local_230;
  (**(code **)(*local_230 + 0x3c))(local_3dc,3);
  FUN_007d2110(local_214,0);
  local_21c = operator_new(500);
  local_8._0_1_ = 0x2a;
  if (local_21c == (void *)0x0) {
    local_240 = 0;
  }
  else {
    local_240 = FUN_007c3150("glowChecklist",0x44244000,local_1a8,0x43010000,0x421c0000,0,
                             local_1a4[99]);
  }
  local_320 = local_240;
  local_8._0_1_ = 0;
  local_1a4[0x5c] = local_240;
  FUN_007c3ac0(local_1fc,0);
  FUN_007c3ac0(local_248,1);
  FUN_007c3c10(*(undefined1 *)(DAT_0094672c + 0x28));
  FUN_007c3cf0(FUN_007ae8d0);
  FUN_007d2110(local_1a4[0x5c],0);
  local_1a8 = local_1a8 + local_1b8;
  local_330 = FUN_0081cb40("graphic_options","shader");
  local_250 = operator_new(0x294c);
  local_8._0_1_ = 0x2b;
  if (local_250 == (void *)0x0) {
    local_258 = (int *)0x0;
  }
  else {
    local_258 = (int *)FUN_007ccb70("shader",local_1b0,local_1a8 + local_1b4,local_1bc,0x422c0000,
                                    0x20,local_1a4[99]);
  }
  local_328 = local_258;
  local_8._0_1_ = 0;
  local_1d8 = local_258;
  (**(code **)(*local_258 + 0x3c))(local_330,3);
  FUN_007d2110(local_1d8,0);
  local_260 = operator_new(500);
  local_8._0_1_ = 0x2c;
  if (local_260 == (void *)0x0) {
    local_268 = 0;
  }
  else {
    local_268 = FUN_007c3150("shaderChecklist",0x44244000,local_1a8,0x43010000,0x421c0000,0,
                             local_1a4[99]);
  }
  local_338 = local_268;
  local_8 = (uint)local_8._1_3_ << 8;
  local_1a4[0x5d] = local_268;
  local_270 = FUN_0044d2a0();
  pRVar3 = Ogre::Root::getSingleton();
  local_340 = Ogre::Root::getRenderSystem(pRVar3);
  puVar8 = local_20c;
  Ogre::Root::getAvailableRenderers(*(Root **)(local_270 + 4));
  FUN_0041fc00(puVar8);
  local_1e8 = 0;
  if (DAT_008e7068 != 0) {
    FUN_0041ff50();
  }
  while( true ) {
    puVar8 = local_3f0;
    Ogre::Root::getAvailableRenderers(*(Root **)(local_270 + 4));
    uVar2 = FUN_0041fc60(puVar8);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') break;
    puVar7 = (undefined4 *)get();
    local_1e0 = (RenderSystem *)*puVar7;
    FUN_0041fe40(&local_1e0);
    iVar4 = local_1e8;
    (**(code **)(*(int *)local_1e0 + 8))(local_1e8);
    uVar2 = FUN_0041f870();
    FUN_007c3ac0(uVar2,iVar4);
    if (local_340 == local_1e0) {
      FUN_007c3c10(local_1e8);
    }
    local_1e8 = local_1e8 + 1;
    FUN_00421f70();
  }
  (**(code **)(*local_1d8 + 0x24))(0);
  (**(code **)(*(int *)local_1a4[0x5d] + 0x24))(0);
  local_1a8 = local_1a8 - local_1b8;
  FUN_007c3cf0(FUN_007ae8e0);
  FUN_007d2110(local_1a4[0x5d],0);
  local_1a8 = local_1a8 + local_1b8;
  local_278 = operator_new(0x294c);
  local_8._0_1_ = 0x2d;
  if (local_278 == (void *)0x0) {
    local_280 = 0;
  }
  else {
    local_280 = FUN_007ccb70("ApplyLabel",local_1b0,local_1a8 + local_1b4,local_1bc,0x43160000,0x20,
                             local_1a4[99]);
  }
  local_348 = local_280;
  local_8._0_1_ = 0;
  local_1a4[0x66] = local_280;
  (**(code **)(*(int *)local_1a4[0x66] + 0x3c))(local_350,3);
  FUN_007d2110(local_1a4[0x66],0);
  local_288 = operator_new(0x1ec);
  local_8._0_1_ = 0x2e;
  if (local_288 == (void *)0x0) {
    local_290 = 0;
  }
  else {
    local_290 = FUN_007c2480("Apply",0x44244000,local_1a8,0x43010000,0x421c0000,0x20,local_1a4[99],0
                             ,0);
  }
  local_358 = local_290;
  local_8 = (uint)local_8._1_3_ << 8;
  local_1a4[100] = local_290;
  FUN_007d2870("optnoff.png");
  (**(code **)(*(int *)local_1a4[100] + 0x3c))("optnclick.png");
  (**(code **)(*(int *)local_1a4[100] + 0x40))("optnon.png");
  FUN_007c23e0(FUN_007ae810);
  FUN_007d2110(local_1a4[100],0);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

