
undefined4 * __fastcall FUN_00794810(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_90;
  undefined4 local_88;
  undefined4 local_80;
  int *local_78;
  undefined4 local_74;
  int *local_70;
  undefined4 local_6c;
  int *local_68;
  undefined4 local_64;
  int *local_5c;
  int *local_4c;
  undefined4 local_3c;
  undefined4 local_30;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f197;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d0fa0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cUI_Mods::vftable;
  DAT_00945554 = param_1;
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_64 = 0;
  }
  else {
    local_64 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(1);
  FUN_007d2870("keyOptions_center.png");
  FUN_007d2110(local_64,0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar1 == (void *)0x0) {
    local_68 = (int *)0x0;
  }
  else {
    local_68 = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_68 + 0x40))("topcrnhv.png");
  (**(code **)(*local_68 + 0x3c))("topcrnck.png");
  uVar2 = FUN_0081cb40("options",&DAT_008714b0);
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_00794720);
  FUN_007d2110(local_68,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 3;
  if (pvVar1 == (void *)0x0) {
    local_70 = (int *)0x0;
  }
  else {
    local_70 = (int *)FUN_007cc390("Lobby",0x43910000,0x430c0000,0x43dc0000,0x422c0000,0x20,local_64
                                   ,0);
  }
  local_8._0_1_ = 0;
  uVar2 = FUN_0081cb40(&DAT_0089e0e4,"inactive");
  (**(code **)(*local_70 + 0x3c))(uVar2);
  FUN_007d2110(local_70,0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 4;
  if (pvVar1 == (void *)0x0) {
    local_78 = (int *)0x0;
  }
  else {
    local_78 = (int *)FUN_007cc390("Lobby",0x443e0000,0x430c0000,0x43dc0000,0x422c0000,0x20,local_64
                                   ,0);
  }
  local_8._0_1_ = 0;
  uVar2 = FUN_0081cb40(&DAT_0089e0e4,"active");
  (**(code **)(*local_78 + 0x3c))(uVar2);
  FUN_007d2110(local_78,0);
  pvVar1 = operator_new(0x180);
  local_8._0_1_ = 5;
  if (pvVar1 == (void *)0x0) {
    local_80 = 0;
  }
  else {
    local_80 = FUN_007c9de0("InactiveList",0x43910000,0x43480000,0x43d98000,0x43dc0000,FUN_00794730,
                            FUN_00794750,0x20,local_64,0xff00ff00,0x3f800000);
  }
  local_8._0_1_ = 0;
  param_1[0x51] = local_80;
  DAT_00945550 = param_1[0x51];
  FUN_007cb3e0(FUN_007947b0);
  FUN_007d2110(param_1[0x51],0);
  pvVar1 = operator_new(0x180);
  local_8._0_1_ = 6;
  if (pvVar1 == (void *)0x0) {
    local_88 = 0;
  }
  else {
    local_88 = FUN_007c9de0("ActiveList",0x443e0000,0x43480000,0x43d98000,0x43dc0000,FUN_00794770,
                            FUN_00794790,0x20,local_64,0xff00ff00,0x3f800000);
  }
  local_8._0_1_ = 0;
  param_1[0x52] = local_88;
  DAT_0094554c = param_1[0x52];
  FUN_007cb3e0(FUN_007947c0);
  FUN_007d2110(param_1[0x52],0);
  pvVar1 = operator_new(0x294c);
  local_8._0_1_ = 7;
  if (pvVar1 == (void *)0x0) {
    local_90 = 0;
  }
  else {
    local_90 = FUN_007ccb70(&DAT_00895778,0x43870000,0x443e0000,0x44520000,0x432a0000,0x20,local_64)
    ;
  }
  local_8._0_1_ = 0;
  param_1[0x53] = local_90;
  FUN_007d2110(param_1[0x53],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 8;
  if (pvVar1 == (void *)0x0) {
    local_6c = 0;
  }
  else {
    local_6c = FUN_007c2480("activateMod",0x43960000,0x44250000,0x43960000,0x42700000,0x20,local_64,
                            0,0);
  }
  local_8._0_1_ = 0;
  param_1[0x54] = local_6c;
  FUN_007d2870("time_limit_off.png");
  (**(code **)(*(int *)param_1[0x54] + 0x40))("time_limit_over.png");
  (**(code **)(*(int *)param_1[0x54] + 0x3c))("time_limit_on.png");
  uVar2 = FUN_0081cb40(&DAT_0089e0e4,"activate_mod");
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_007947d0);
  FUN_007d2110(param_1[0x54],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 9;
  if (pvVar1 == (void *)0x0) {
    local_74 = 0;
  }
  else {
    local_74 = FUN_007c2480("inactivateMod",0x44390000,0x44250000,0x43960000,0x42700000,0x20,
                            local_64,0,0);
  }
  local_8._0_1_ = 0;
  param_1[0x55] = local_74;
  FUN_007d2870("time_limit_off.png");
  (**(code **)(*(int *)param_1[0x55] + 0x40))("time_limit_over.png");
  (**(code **)(*(int *)param_1[0x55] + 0x3c))("time_limit_on.png");
  uVar2 = FUN_0081cb40(&DAT_0089e0e4,"deactivate_mod");
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_007947e0);
  FUN_007d2110(param_1[0x55],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 10;
  if (pvVar1 == (void *)0x0) {
    local_30 = 0;
  }
  else {
    local_30 = FUN_007c2480("upPriority",0x448ac000,0x44228000,0x43520000,0x42480000,0x20,local_64,0
                            ,0);
  }
  local_8._0_1_ = 0;
  param_1[0x56] = local_30;
  FUN_007d2870("time_limit_off.png");
  (**(code **)(*(int *)param_1[0x56] + 0x40))("time_limit_over.png");
  (**(code **)(*(int *)param_1[0x56] + 0x3c))("time_limit_on.png");
  uVar2 = FUN_0081cb40(&DAT_0089e0e4,"increase_priority");
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_007947f0);
  FUN_007d2110(param_1[0x56],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0xb;
  if (pvVar1 == (void *)0x0) {
    local_3c = 0;
  }
  else {
    local_3c = FUN_007c2480("dnPriority",0x448ac000,0x44318000,0x43520000,0x42480000,0x20,local_64,0
                            ,0);
  }
  local_8._0_1_ = 0;
  param_1[0x57] = local_3c;
  FUN_007d2870("time_limit_off.png");
  (**(code **)(*(int *)param_1[0x57] + 0x40))("time_limit_over.png");
  (**(code **)(*(int *)param_1[0x57] + 0x3c))("time_limit_on.png");
  uVar2 = FUN_0081cb40(&DAT_0089e0e4,"decrease_priority");
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_00794800);
  FUN_007d2110(param_1[0x57],0);
  iVar3 = FUN_00764980();
  if (iVar3 != 0) {
    pvVar1 = operator_new(0x1ec);
    local_8._0_1_ = 0xc;
    if (pvVar1 == (void *)0x0) {
      local_4c = (int *)0x0;
    }
    else {
      local_4c = (int *)FUN_007c2480("GetMapsButton",0,0x44700000,0x43960000,0x42700000,0x60,0,0,
                                     0x41000000);
    }
    local_8._0_1_ = 0;
    FUN_007d2870("multi_createGame_button_off.png");
    (**(code **)(*local_4c + 0x40))("multi_createGame_button_over.png");
    (**(code **)(*local_4c + 0x3c))("multi_createGame_button_on.png");
    uVar2 = FUN_0081cb40("missions","get_mods");
    FUN_007c2950(uVar2);
    FUN_007c23e0(FUN_00787fe0);
    FUN_007d2110(local_4c,0);
    pvVar1 = operator_new(0x1ec);
    local_8._0_1_ = 0xd;
    if (pvVar1 == (void *)0x0) {
      local_5c = (int *)0x0;
    }
    else {
      local_5c = (int *)FUN_007c2480("RefreshButton",0,0x447f0000,0x43960000,0x42700000,0x60,0,0,
                                     0x41000000);
    }
    local_8._0_1_ = 0;
    FUN_007d2870("multi_createGame_button_off.png");
    (**(code **)(*local_5c + 0x40))("multi_createGame_button_over.png");
    (**(code **)(*local_5c + 0x3c))("multi_createGame_button_on.png");
    uVar2 = FUN_0081cb40("missions","refresh");
    FUN_007c2950(uVar2);
    FUN_007c23e0(FUN_00794710);
    FUN_007d2110(local_5c,0);
  }
  FUN_007955c0();
  ExceptionList = local_10;
  return param_1;
}

