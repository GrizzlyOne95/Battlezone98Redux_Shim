
void __thiscall FUN_007a9590(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  void *pvVar2;
  undefined1 *puVar3;
  undefined4 local_98;
  int *local_88;
  int *local_7c;
  undefined4 local_78;
  undefined4 local_74;
  int *local_6c;
  undefined4 local_60;
  int *local_5c;
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860884;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_Multiplayer_VehicleSelect::vftable;
  basic_string<>(local_14);
  local_8 = 0;
  param_1[10] = param_3;
  DAT_00945598 = param_1;
  uVar1 = FUN_00764760();
  param_1[7] = uVar1;
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 1;
  if (pvVar2 == (void *)0x0) {
    local_98 = 0;
  }
  else {
    local_98 = FUN_007cc390("VehicleSelectName",0x444a8000,0x43d20000,0x43a90000,0x420c0000,0x8020,
                            param_2,0);
  }
  local_8._0_1_ = 0;
  param_1[8] = local_98;
  FUN_007d2110(param_1[8],0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar2 == (void *)0x0) {
    local_88 = (int *)0x0;
  }
  else {
    local_88 = (int *)FUN_007c2480("VehicleSelectPageLeft",0x43570000,0,0x420c0000,0x420c0000,0x20,
                                   param_1[8],0,0);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("learroff.png");
  (**(code **)(*local_88 + 0x40))("learrclk.png");
  (**(code **)(*local_88 + 0x3c))("learron.png");
  FUN_007c2950(&DAT_008a1ad8);
  FUN_007c23e0(FUN_007a9410);
  FUN_007d2110(local_88,0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 3;
  if (pvVar2 == (void *)0x0) {
    local_6c = (int *)0x0;
  }
  else {
    local_6c = (int *)FUN_007c2480("VehicleSelectPageRight",0x437a0000,0,0x420c0000,0x420c0000,0x20,
                                   param_1[8],0,0);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("rtarroff.png");
  (**(code **)(*local_6c + 0x40))("rtarrclk.png");
  (**(code **)(*local_6c + 0x3c))("rtarron.png");
  FUN_007c2950(&DAT_008a1ad8);
  FUN_007c23e0(FUN_007a9420);
  FUN_007d2110(local_6c,0);
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 4;
  if (pvVar2 == (void *)0x0) {
    local_74 = 0;
  }
  else {
    local_74 = FUN_007cc390("Faction",0x448be000,0x43d20000,0x43a90000,0x420c0000,0x8020,param_2,0);
  }
  local_8._0_1_ = 0;
  param_1[9] = local_74;
  FUN_007cc6b0(0x3f666666);
  FUN_007a9ea0();
  FUN_007d2110(param_1[9],0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 5;
  if (pvVar2 == (void *)0x0) {
    local_7c = (int *)0x0;
  }
  else {
    local_7c = (int *)FUN_007c2480("FactionSelectPageLeft",0x43f08000,0,0x420c0000,0x420c0000,0x20,
                                   param_1[8],0,0);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("learroff.png");
  (**(code **)(*local_7c + 0x40))("learrclk.png");
  (**(code **)(*local_7c + 0x3c))("learron.png");
  FUN_007c2950(&DAT_008a1ad8);
  FUN_007c23e0(FUN_007a9430);
  FUN_007d2110(local_7c,0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 6;
  if (pvVar2 == (void *)0x0) {
    local_5c = (int *)0x0;
  }
  else {
    local_5c = (int *)FUN_007c2480("FactionSelectPageRight",0x44010000,0,0x420c0000,0x420c0000,0x20,
                                   param_1[8],0,0);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("rtarroff.png");
  (**(code **)(*local_5c + 0x40))("rtarrclk.png");
  (**(code **)(*local_5c + 0x3c))("rtarron.png");
  FUN_007c2950(&DAT_008a1ad8);
  FUN_007c23e0(FUN_007a9440);
  FUN_007d2110(local_5c,0);
  pvVar2 = operator_new(0x294c);
  local_8._0_1_ = 7;
  if (pvVar2 == (void *)0x0) {
    local_78 = 0;
  }
  else {
    local_78 = FUN_007ccb70("chatText",0x448c0000,0x43200000,0x43fd0000,0x44514000,0,param_2);
  }
  local_8._0_1_ = 0;
  param_1[0xb] = local_78;
  basic_string<>(&DAT_008a1ad8);
  local_8._0_1_ = 8;
  FUN_007cce50(0x3f333333);
  uVar1 = FUN_0041f870(3);
  (**(code **)(*(int *)param_1[0xb] + 0x3c))(uVar1);
  FUN_007d2110(param_1[0xb],0);
  pvVar2 = operator_new(0x144);
  local_8._0_1_ = 9;
  if (pvVar2 == (void *)0x0) {
    local_60 = 0;
  }
  else {
    local_60 = FUN_007a9450("VehiclePreview",0xc2600000,0xc38e8000,0x43aa0000,0x438b0000,0x20,
                            param_1[8]);
  }
  local_8._0_1_ = 8;
  param_1[0xc] = local_60;
  FUN_007d3f20(4);
  FUN_007d2a00("scope","SniperTex");
  uVar1 = (**(code **)(*DAT_00920e80 + 0x2c))
                    (*(undefined4 *)(DAT_00920ea0 + 0x18),0,0,0,0x3f800000,0x3f800000);
  *(undefined4 *)(DAT_00920ea0 + 0x24) = uVar1;
  Ogre::Viewport::setClearEveryFrame(*(Viewport **)(DAT_00920ea0 + 0x24),true,3);
  Ogre::Viewport::setBackgroundColour
            (*(Viewport **)(DAT_00920ea0 + 0x24),(ColourValue *)Black_exref);
  Ogre::Viewport::setOverlaysEnabled(*(Viewport **)(DAT_00920ea0 + 0x24),false);
  Ogre::Viewport::setShadowsEnabled(*(Viewport **)(DAT_00920ea0 + 0x24),false);
  Ogre::Viewport::setVisibilityMask(*(Viewport **)(DAT_00920ea0 + 0x24),8);
  FUN_00680fe0();
  FUN_007d2110(param_1[0xc],0);
  puVar3 = local_44;
  FUN_00764780(puVar3);
  FUN_007663a0(puVar3);
  local_8._0_1_ = 10;
  uVar1 = FUN_0041f870();
  (**(code **)(*(int *)param_1[8] + 0x3c))(uVar1);
  local_8._0_1_ = 8;
  ~basic_string<>();
  DAT_00920e98 = 0;
  DAT_00920ec0 = 0;
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

