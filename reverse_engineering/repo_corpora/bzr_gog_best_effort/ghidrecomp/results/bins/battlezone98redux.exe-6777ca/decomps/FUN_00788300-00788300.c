
undefined4 * __fastcall FUN_00788300(undefined4 *param_1)

{
  uint uVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int *local_78;
  int *local_70;
  undefined4 local_68;
  undefined4 local_5c;
  undefined4 local_58;
  int *local_54;
  int *local_4c;
  undefined4 local_48;
  int *local_3c;
  undefined4 local_30;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e7b0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0(uVar1);
  local_8 = 0;
  *param_1 = cUI_Campaign::vftable;
  DAT_009454e8 = param_1;
  pvVar2 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar2 == (void *)0x0) {
    local_68 = 0;
  }
  else {
    local_68 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  param_1[0x52] = local_68;
  FUN_007d3f20(1);
  FUN_007d2870("iaoptions_center.png");
  FUN_007d2110(param_1[0x52],0);
  uVar3 = FUN_0081cb40("missions",&DAT_008714b0);
  uVar4 = FUN_0081cb40("campaign","select_campaign");
  uVar5 = FUN_0081cb40("missions","launch");
  uVar6 = FUN_0081cb40("missions","archives");
  uVar6 = FUN_0081cb40("single","options",uVar1,uVar6);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar2 == (void *)0x0) {
    local_70 = (int *)0x0;
  }
  else {
    local_70 = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_70 + 0x40))("topcrnhv.png");
  (**(code **)(*local_70 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar3);
  FUN_007c23e0(FUN_00788030);
  FUN_007d2110(local_70,0);
  iVar7 = FUN_00764bb0();
  if (iVar7 != 3) {
    iVar7 = FUN_00764bb0();
    if (iVar7 != 1) goto LAB_007887c8;
  }
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 3;
  if (pvVar2 == (void *)0x0) {
    local_78 = (int *)0x0;
  }
  else {
    local_78 = (int *)FUN_007c2480("GetMapsButton",0,0x44610000,0x43960000,0x42700000,0x60,0,0,
                                   0x41000000);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("multi_createGame_button_off.png");
  (**(code **)(*local_78 + 0x40))("multi_createGame_button_over.png");
  (**(code **)(*local_78 + 0x3c))("multi_createGame_button_on.png");
  uVar3 = FUN_0081cb40("campaign","get_campaigns");
  FUN_007c2950(uVar3);
  FUN_007c23e0(FUN_00787fe0);
  FUN_007d2110(local_78,0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 4;
  if (pvVar2 == (void *)0x0) {
    local_4c = (int *)0x0;
  }
  else {
    local_4c = (int *)FUN_007c2480("RefreshButton",0,0x44700000,0x43960000,0x42700000,0x60,0,0,
                                   0x41000000);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007d2870("multi_createGame_button_off.png");
  (**(code **)(*local_4c + 0x40))("multi_createGame_button_over.png");
  (**(code **)(*local_4c + 0x3c))("multi_createGame_button_on.png");
  uVar3 = FUN_0081cb40("missions","refresh");
  FUN_007c2950(uVar3);
  FUN_007c23e0(FUN_00787ff0);
  FUN_007d2110(local_4c,0);
LAB_007887c8:
  pvVar2 = operator_new(0x930);
  local_8._0_1_ = 5;
  if (pvVar2 == (void *)0x0) {
    local_54 = (int *)0x0;
  }
  else {
    local_54 = (int *)FUN_007cc390("Select",0x43d98000,0x42f80000,0x440e8000,0x422c0000,0x9020,
                                   param_1[0x52],0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_54 + 0x3c))(uVar4);
  FUN_007d2110(local_54,0);
  pvVar2 = operator_new(0x180);
  local_8._0_1_ = 6;
  if (pvVar2 == (void *)0x0) {
    local_5c = 0;
  }
  else {
    local_5c = FUN_007c9de0("Mission_List",0x43910000,0x43820000,0x44048000,0x43e10000,FUN_00788000,
                            FUN_00788010,0,param_1[0x52],0xff00ff00,0x3f800000);
  }
  local_8._0_1_ = 0;
  param_1[0x51] = local_5c;
  DAT_009454e4 = param_1[0x51];
  pvVar2 = operator_new(0x294c);
  local_8._0_1_ = 7;
  if (pvVar2 == (void *)0x0) {
    local_48 = 0;
  }
  else {
    local_48 = FUN_007ccb70("descriptionBox",0x43d98000,0x443d0000,0x440e8000,0x42f00000,0x20,
                            param_1[0x52]);
  }
  local_8._0_1_ = 0;
  param_1[0x55] = local_48;
  FUN_007d2110(param_1[0x55],0);
  pvVar2 = operator_new(0x144);
  local_8._0_1_ = 8;
  if (pvVar2 == (void *)0x0) {
    local_58 = 0;
  }
  else {
    local_58 = FUN_007d1cc0("MapPreview",0x447a0000,0x43850000,0x43480000,0x43480000,0x20,
                            param_1[0x52],0);
  }
  local_8._0_1_ = 0;
  param_1[0x54] = local_58;
  FUN_007d2110(param_1[0x54],0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 9;
  if (pvVar2 == (void *)0x0) {
    local_30 = 0;
  }
  else {
    local_30 = FUN_007c2480("Launch",0,0,0x43ab0000,0x429a0000,0xa2,0,0xc2200000,0);
  }
  local_8._0_1_ = 0;
  param_1[0x53] = local_30;
  FUN_007d2870("topcorner.png");
  (**(code **)(*(int *)param_1[0x53] + 0x40))("topcrnhv.png");
  (**(code **)(*(int *)param_1[0x53] + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar5);
  FUN_007c23e0(FUN_00788050);
  FUN_007d2110(param_1[0x53],0);
  FUN_00788d90();
  FUN_007cb3e0(FUN_00788040);
  FUN_007d2110(param_1[0x51],0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 10;
  if (pvVar2 == (void *)0x0) {
    local_3c = (int *)0x0;
  }
  else {
    local_3c = (int *)FUN_007c2480("Options",0,0x447ac000,0x43ab0000,0x429a0000,0x24,0,0x41e00000,
                                   0x40a00000);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_3c + 0x40))("topcrnhv.png");
  (**(code **)(*local_3c + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar6);
  FUN_007c23e0(FUN_00788020);
  FUN_007d2110(local_3c,0);
  ExceptionList = local_10;
  return param_1;
}

