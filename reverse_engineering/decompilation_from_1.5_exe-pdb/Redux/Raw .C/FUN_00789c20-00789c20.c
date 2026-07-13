
undefined4 * __fastcall FUN_00789c20(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 local_58;
  int *local_50;
  undefined4 local_4c;
  int *local_48;
  int *local_40;
  undefined4 local_3c;
  int *local_38;
  undefined4 local_30;
  undefined4 local_2c;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e8c4;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d0fa0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cUI_InstantAction::vftable;
  DAT_009454f4 = param_1;
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_30 = 0;
  }
  else {
    local_30 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  param_1[0x52] = local_30;
  FUN_007d3f20(1);
  FUN_007d2870("iaoptions_center.png");
  FUN_007d2110(param_1[0x52],0);
  uVar2 = FUN_0081cb40("missions",&DAT_008714b0);
  uVar3 = FUN_0081cb40("missions","select_mission");
  uVar4 = FUN_0081cb40("missions","launch");
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar1 == (void *)0x0) {
    local_38 = (int *)0x0;
  }
  else {
    local_38 = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_38 + 0x40))("topcrnhv.png");
  (**(code **)(*local_38 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_007898e0);
  FUN_007d2110(local_38,0);
  iVar5 = FUN_00764980();
  if (iVar5 != 0) {
    pvVar1 = operator_new(0x1ec);
    local_8._0_1_ = 3;
    if (pvVar1 == (void *)0x0) {
      local_40 = (int *)0x0;
    }
    else {
      local_40 = (int *)FUN_007c2480("GetMapsButton",0,0x44610000,0x43960000,0x42700000,0x60,0,0,
                                     0x41000000);
    }
    local_8._0_1_ = 0;
    FUN_007d2870("multi_createGame_button_off.png");
    (**(code **)(*local_40 + 0x40))("multi_createGame_button_over.png");
    (**(code **)(*local_40 + 0x3c))("multi_createGame_button_on.png");
    uVar2 = FUN_0081cb40("missions","get_maps");
    FUN_007c2950(uVar2);
    FUN_007c23e0(FUN_00787fe0);
    FUN_007d2110(local_40,0);
    pvVar1 = operator_new(0x1ec);
    local_8._0_1_ = 4;
    if (pvVar1 == (void *)0x0) {
      local_48 = (int *)0x0;
    }
    else {
      local_48 = (int *)FUN_007c2480("RefreshButton",0,0x44700000,0x43960000,0x42700000,0x60,0,0,
                                     0x41000000);
    }
    local_8._0_1_ = 0;
    FUN_007d2870("multi_createGame_button_off.png");
    (**(code **)(*local_48 + 0x40))("multi_createGame_button_over.png");
    (**(code **)(*local_48 + 0x3c))("multi_createGame_button_on.png");
    uVar2 = FUN_0081cb40("missions","refresh");
    FUN_007c2950(uVar2);
    FUN_007c23e0(FUN_007898b0);
    FUN_007d2110(local_48,0);
  }
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 5;
  if (pvVar1 == (void *)0x0) {
    local_50 = (int *)0x0;
  }
  else {
    local_50 = (int *)FUN_007cc390("Select",0x43d98000,0x42f80000,0x440e8000,0x422c0000,0x9020,
                                   param_1[0x52],0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_50 + 0x3c))(uVar3);
  FUN_007d2110(local_50,0);
  pvVar1 = operator_new(0x180);
  local_8._0_1_ = 6;
  if (pvVar1 == (void *)0x0) {
    local_58 = 0;
  }
  else {
    local_58 = FUN_007c9de0("Mission_List",0x43910000,0x43820000,0x44048000,0x43e10000,FUN_007898c0,
                            FUN_007898d0,0,param_1[0x52],0xff00ff00,0x3f800000);
  }
  local_8._0_1_ = 0;
  param_1[0x51] = local_58;
  DAT_009454f0 = param_1[0x51];
  pvVar1 = operator_new(0x294c);
  local_8._0_1_ = 7;
  if (pvVar1 == (void *)0x0) {
    local_4c = 0;
  }
  else {
    local_4c = FUN_007ccb70("descriptionBox",0x43d98000,0x443d0000,0x440e8000,0x42f00000,0x20,
                            param_1[0x52]);
  }
  local_8._0_1_ = 0;
  param_1[0x55] = local_4c;
  FUN_007d2110(param_1[0x55],0);
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 8;
  if (pvVar1 == (void *)0x0) {
    local_2c = 0;
  }
  else {
    local_2c = FUN_007d1cc0("MapPreview",0x447a0000,0x43850000,0x43480000,0x43480000,0x20,
                            param_1[0x52],0);
  }
  local_8._0_1_ = 0;
  param_1[0x54] = local_2c;
  FUN_007d2110(param_1[0x54],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 9;
  if (pvVar1 == (void *)0x0) {
    local_3c = 0;
  }
  else {
    local_3c = FUN_007c2480("Launch",0,0,0x43ab0000,0x429a0000,0xa2,0,0xc2200000,0);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x53] = local_3c;
  FUN_007d2870("topcorner.png");
  (**(code **)(*(int *)param_1[0x53] + 0x40))("topcrnhv.png");
  (**(code **)(*(int *)param_1[0x53] + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar4);
  FUN_007c23e0(FUN_00789900);
  FUN_007d2110(param_1[0x53],0);
  FUN_0078a560();
  FUN_007cb3e0(FUN_007898f0);
  FUN_007d2110(param_1[0x51],0);
  ExceptionList = local_10;
  return param_1;
}

