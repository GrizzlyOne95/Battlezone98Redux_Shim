
void __fastcall FUN_007aab70(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_a0;
  int *local_9c;
  undefined4 local_94;
  undefined4 local_74;
  undefined4 local_70;
  int *local_68;
  undefined4 local_5c;
  undefined4 local_58;
  int *local_54;
  undefined4 local_4c;
  int *local_48;
  int local_44;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860a30;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0(local_14);
  local_8 = 0;
  *param_1 = cUI_ObjectSettings::vftable;
  DAT_0094559c = param_1;
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_74 = 0;
  }
  else {
    local_74 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  param_1[0x51] = local_74;
  FUN_007d3f20(1);
  FUN_007d2110(param_1[0x51],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 2;
  if (pvVar1 == (void *)0x0) {
    local_54 = (int *)0x0;
  }
  else {
    local_54 = (int *)FUN_007cc390("labellabel",0x42480000,0x433e0000,0x43e10000,0x42a00000,0x20,
                                   param_1[0x51],0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_54 + 0x3c))("Label");
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 3;
  if (pvVar1 == (void *)0x0) {
    local_5c = 0;
  }
  else {
    local_5c = FUN_007d1cc0("input_background",0x42480000,0x43660000,0x43f50000,0x42700000,0x20,
                            param_1[0x51],0);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("saveloadedit_filelist_text.png");
  FUN_007d2110(local_5c,0);
  pvVar1 = operator_new(0x968);
  local_8._0_1_ = 4;
  if (pvVar1 == (void *)0x0) {
    local_a0 = 0;
  }
  else {
    local_a0 = FUN_007cf410(0,1,0x24,"chatEntry",0x42820000,0x436d0000,0x43960000,0x42200000,0x8020,
                            param_1[0x51]);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x54] = local_a0;
  CMFCToolBarsListPropertyPage::EnableUserDefinedToolbars
            ((CMFCToolBarsListPropertyPage *)param_1[0x54],0x2d);
  FUN_007cf940(FUN_007aab30);
  if (DAT_009181a4 != 0) {
    (**(code **)(*(int *)param_1[0x54] + 0x3c))(DAT_009181a4);
  }
  FUN_007d2110(param_1[0x54],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 5;
  if (pvVar1 == (void *)0x0) {
    local_9c = (int *)0x0;
  }
  else {
    local_9c = (int *)FUN_007cc390("indeplabel",0x42480000,0x43b40000,0x43e10000,0x42a00000,0x20,
                                   param_1[0x51],0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_9c + 0x3c))("Independence");
  pvVar1 = operator_new(500);
  local_8._0_1_ = 6;
  if (pvVar1 == (void *)0x0) {
    local_94 = 0;
  }
  else {
    local_94 = FUN_007c3150("mHudOnOffChecklist",0x42480000,0x43c30000,0x43010000,0x421c0000,0x20,
                            param_1[0x51]);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x52] = local_94;
  FUN_007d3f20(3);
  FUN_007c3ac0(&DAT_00873c74,0);
  FUN_007c3ac0(&DAT_00873ef0,1);
  if (DAT_009181a4 == 0) {
    FUN_007c3c10(0);
  }
  else {
    FUN_007c3c10(*(undefined4 *)(DAT_009181a4 + 0x30));
  }
  FUN_007d2110(param_1[0x52],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 7;
  if (pvVar1 == (void *)0x0) {
    local_48 = (int *)0x0;
  }
  else {
    local_48 = (int *)FUN_007cc390("teamLabel",0x42480000,0x43fa0000,0x43e10000,0x42a00000,0x20,
                                   param_1[0x51],0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_48 + 0x3c))(&DAT_00885478);
  pvVar1 = operator_new(500);
  local_8._0_1_ = 8;
  if (pvVar1 == (void *)0x0) {
    local_70 = 0;
  }
  else {
    local_70 = FUN_007c3150("teamChecklist",0x42480000,0x44048000,0x43010000,0x421c0000,0x20,
                            param_1[0x51]);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x53] = local_70;
  FUN_007d3f20(3);
  for (local_44 = 0; local_44 < 0x10; local_44 = local_44 + 1) {
    FUN_00482630(local_2c,local_44);
    local_8._0_1_ = 9;
    iVar3 = local_44;
    uVar2 = FUN_0041f870(local_44);
    FUN_007c3ac0(uVar2,iVar3);
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
  }
  if (DAT_009181a4 == 0) {
    FUN_007c3c10(0);
  }
  else {
    FUN_007c3c10(*(undefined4 *)(DAT_009181a4 + 0x34));
  }
  FUN_007d2110(param_1[0x53],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 10;
  if (pvVar1 == (void *)0x0) {
    local_4c = 0;
  }
  else {
    local_4c = FUN_007c2480("okbtn",0x42480000,0x442a0000,0x435c0000,0x42980000,0x20,param_1[0x51],0
                            ,0);
  }
  local_8._0_1_ = 0;
  param_1[0x55] = local_4c;
  FUN_007d3f20(3);
  FUN_007d2870("newon.png");
  (**(code **)(*(int *)param_1[0x55] + 0x40))("newclk.png");
  (**(code **)(*(int *)param_1[0x55] + 0x3c))("newclk.png");
  FUN_007c2950(&DAT_0089f2ac);
  FUN_007c23e0(FUN_007aaa40);
  FUN_007d2110(param_1[0x55],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0xb;
  if (pvVar1 == (void *)0x0) {
    local_58 = 0;
  }
  else {
    local_58 = FUN_007c2480("cancelbtn",0x438c0000,0x442a0000,0x435c0000,0x42980000,0x20,
                            param_1[0x51],0,0);
  }
  local_8._0_1_ = 0;
  param_1[0x56] = local_58;
  FUN_007d3f20(3);
  FUN_007d2870("newon.png");
  (**(code **)(*(int *)param_1[0x56] + 0x40))("newclk.png");
  (**(code **)(*(int *)param_1[0x56] + 0x3c))("newclk.png");
  FUN_007c2950("Cancel");
  FUN_007c23e0(FUN_007aaa50);
  FUN_007d2110(param_1[0x56],0);
  uVar2 = FUN_0081cb40("single",&DAT_008714b0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0xc;
  if (pvVar1 == (void *)0x0) {
    local_68 = (int *)0x0;
  }
  else {
    local_68 = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_68 + 0x40))("topcrnhv.png");
  (**(code **)(*local_68 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_007aaa60);
  FUN_007d2110(local_68,0);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

