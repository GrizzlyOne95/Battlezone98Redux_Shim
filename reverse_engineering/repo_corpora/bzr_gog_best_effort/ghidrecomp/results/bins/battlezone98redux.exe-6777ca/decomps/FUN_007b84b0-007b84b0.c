
undefined4 * __fastcall FUN_007b84b0(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  int *local_c4;
  undefined4 local_bc;
  int *local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  int *local_a4;
  undefined4 local_9c;
  int *local_7c;
  undefined4 local_6c;
  undefined4 local_5c;
  undefined4 local_4c;
  undefined4 local_48;
  int *local_40;
  undefined4 local_3c;
  undefined4 local_38;
  int *local_30;
  int local_24;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861583;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d0fa0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cUI_PathSettings::vftable;
  DAT_009455cc = param_1;
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_38 = 0;
  }
  else {
    local_38 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  param_1[0x51] = local_38;
  FUN_007d3f20(1);
  FUN_007d2110(param_1[0x51],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 2;
  if (pvVar1 == (void *)0x0) {
    local_40 = (int *)0x0;
  }
  else {
    local_40 = (int *)FUN_007cc390("labellabel",0x42d20000,0x43520000,0x43e10000,0x42a00000,0x20,
                                   param_1[0x51],0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_40 + 0x3c))(&DAT_0087b984);
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 3;
  if (pvVar1 == (void *)0x0) {
    local_48 = 0;
  }
  else {
    local_48 = FUN_007d1cc0("input_background",0x42480000,0x43660000,0x43f50000,0x42700000,0x20,
                            param_1[0x51],0);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007d2870("saveloadedit_filelist_text.png");
  FUN_007d2110(local_48,0);
  local_24 = 0;
  if (DAT_009181a8 != 0) {
    local_24 = FUN_0046f0f0(*(undefined4 *)(DAT_009181a8 + 0x38));
  }
  pvVar1 = operator_new(0x968);
  local_8._0_1_ = 4;
  if (pvVar1 == (void *)0x0) {
    local_9c = 0;
  }
  else {
    local_9c = FUN_007cf410(0,1,0x24,"chatEntry",0x42820000,0x436d0000,0x43960000,0x42200000,0x8020,
                            param_1[0x51]);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x56] = local_9c;
  CMFCToolBarsListPropertyPage::EnableUserDefinedToolbars
            ((CMFCToolBarsListPropertyPage *)param_1[0x56],0x27);
  FUN_007cf940(FUN_007aab30);
  if (DAT_009181a8 != 0) {
    (**(code **)(*(int *)param_1[0x56] + 0x3c))(DAT_009181a8);
  }
  FUN_007d2110(param_1[0x56],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 5;
  if (pvVar1 == (void *)0x0) {
    local_a4 = (int *)0x0;
  }
  else {
    local_a4 = (int *)FUN_007cc390("pathtypelabel",0x42d20000,0x43b40000,0x43e10000,0x42a00000,0x20,
                                   param_1[0x51],0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_a4 + 0x3c))("Path Type");
  pvVar1 = operator_new(500);
  local_8._0_1_ = 6;
  if (pvVar1 == (void *)0x0) {
    local_ac = 0;
  }
  else {
    local_ac = FUN_007c3150("pathtypelist",0x42480000,0x43c30000,0x43010000,0x421c0000,0x20,
                            param_1[0x51]);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x52] = local_ac;
  FUN_007d3f20(3);
  FUN_007c3ac0(&DAT_0089fe8c,0);
  FUN_007c3ac0(&DAT_0089fe84,1);
  if (local_24 == 0) {
    FUN_007c3c10(0);
  }
  else {
    FUN_007c3c10(1);
  }
  FUN_007d2110(param_1[0x52],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 7;
  if (pvVar1 == (void *)0x0) {
    local_b4 = (int *)0x0;
  }
  else {
    local_b4 = (int *)FUN_007cc390("areatypelabel",0x42d20000,0x43fa0000,0x43e10000,0x42a00000,0x20,
                                   param_1[0x51],0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_b4 + 0x3c))("Area Type");
  pvVar1 = operator_new(500);
  local_8._0_1_ = 8;
  if (pvVar1 == (void *)0x0) {
    local_bc = 0;
  }
  else {
    local_bc = FUN_007c3150("areatypelist",0x42480000,0x44048000,0x43010000,0x421c0000,0x20,
                            param_1[0x51]);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x53] = local_bc;
  FUN_007d3f20(3);
  FUN_007c3ac0("Boring",0);
  FUN_007c3ac0("Interesting",1);
  if (local_24 == 0) {
    FUN_007c3c10(0);
  }
  else {
    FUN_007c3c10(*(undefined1 *)(local_24 + 8));
  }
  FUN_007d2110(param_1[0x53],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 9;
  if (pvVar1 == (void *)0x0) {
    local_c4 = (int *)0x0;
  }
  else {
    local_c4 = (int *)FUN_007cc390("areapartlabel",0x44174000,0x43b40000,0x43e10000,0x42a00000,0x20,
                                   param_1[0x51],0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_c4 + 0x3c))("Area Type");
  pvVar1 = operator_new(500);
  local_8._0_1_ = 10;
  if (pvVar1 == (void *)0x0) {
    local_a8 = 0;
  }
  else {
    local_a8 = FUN_007c3150("areapartlist",0x44098000,0x43c30000,0x43010000,0x421c0000,0x20,
                            param_1[0x51]);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x54] = local_a8;
  FUN_007d3f20(3);
  FUN_007c3ac0("Outside",0);
  FUN_007c3ac0("Inside",1);
  if (local_24 == 0) {
    FUN_007c3c10(1);
  }
  else {
    FUN_007c3c10(*(undefined1 *)(local_24 + 9));
  }
  FUN_007d2110(param_1[0x54],0);
  pvVar1 = operator_new(0x930);
  local_8._0_1_ = 0xb;
  if (pvVar1 == (void *)0x0) {
    local_30 = (int *)0x0;
  }
  else {
    local_30 = (int *)FUN_007cc390("unittypelabel",0x44174000,0x43fa0000,0x43e10000,0x42a00000,0x20,
                                   param_1[0x51],0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_30 + 0x3c))("Unit Type");
  pvVar1 = operator_new(500);
  local_8._0_1_ = 0xc;
  if (pvVar1 == (void *)0x0) {
    local_b0 = 0;
  }
  else {
    local_b0 = FUN_007c3150("unittypelist",0x44098000,0x44048000,0x43010000,0x421c0000,0x20,
                            param_1[0x51]);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x55] = local_b0;
  FUN_007d3f20(3);
  FUN_007c3ac0("Attack",0);
  FUN_007c3ac0("Defend",1);
  if (local_24 == 0) {
    FUN_007c3c10(1);
  }
  else {
    FUN_007c3c10(*(int *)(local_24 + 0x10) < 100);
  }
  FUN_007d2110(param_1[0x55],0);
  pvVar1 = operator_new(0x154);
  local_8._0_1_ = 0xd;
  if (pvVar1 == (void *)0x0) {
    local_3c = 0;
  }
  else {
    local_3c = FUN_007c48d0("Value","valueinput",0x442f0000,0x441b0000,0x43e10000,0x42a00000,
                            FUN_007b8130,FUN_007b8140,FUN_007b8150,FUN_007b8160,FUN_007b8170,
                            FUN_007b8180,0x20,param_1[0x51]);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x59] = local_3c;
  if (local_24 == 0) {
    FUN_007c4800(0);
  }
  else {
    FUN_007c4800(*(undefined4 *)(local_24 + 0xc));
  }
  FUN_007d2110(param_1[0x59],0);
  pvVar1 = operator_new(0x154);
  local_8._0_1_ = 0xe;
  if (pvVar1 == (void *)0x0) {
    local_4c = 0;
  }
  else {
    local_4c = FUN_007c48d0("Force","forceinput",0x44548000,0x441b0000,0x43e10000,0x42a00000,
                            FUN_007b80d0,FUN_007b80e0,FUN_007b80f0,FUN_007b8100,FUN_007b8110,
                            FUN_007b8120,0x20,param_1[0x51]);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x5a] = local_4c;
  if (local_24 == 0) {
    FUN_007c4800(0);
  }
  else {
    FUN_007c4800(*(undefined4 *)(local_24 + 0x10));
  }
  FUN_007d2110(param_1[0x5a],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0xf;
  if (pvVar1 == (void *)0x0) {
    local_5c = 0;
  }
  else {
    local_5c = FUN_007c2480("okbtn",0x42480000,0x442a0000,0x435c0000,0x42980000,0x20,param_1[0x51],0
                            ,0);
  }
  local_8._0_1_ = 0;
  param_1[0x57] = local_5c;
  FUN_007d3f20(3);
  FUN_007d2870("newon.png");
  (**(code **)(*(int *)param_1[0x57] + 0x40))("newclk.png");
  (**(code **)(*(int *)param_1[0x57] + 0x3c))("newclk.png");
  FUN_007c2950(&DAT_0089f2ac);
  FUN_007c23e0(FUN_007b8310);
  FUN_007d2110(param_1[0x57],0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0x10;
  if (pvVar1 == (void *)0x0) {
    local_6c = 0;
  }
  else {
    local_6c = FUN_007c2480("cancelbtn",0x438c0000,0x442a0000,0x435c0000,0x42980000,0x20,
                            param_1[0x51],0,0);
  }
  local_8._0_1_ = 0;
  param_1[0x58] = local_6c;
  FUN_007d3f20(3);
  FUN_007d2870("newon.png");
  (**(code **)(*(int *)param_1[0x58] + 0x40))("newclk.png");
  (**(code **)(*(int *)param_1[0x58] + 0x3c))("newclk.png");
  FUN_007c2950("Cancel");
  FUN_007c23e0(FUN_007b8320);
  FUN_007d2110(param_1[0x58],0);
  uVar2 = FUN_0081cb40("single",&DAT_008714b0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 0x11;
  if (pvVar1 == (void *)0x0) {
    local_7c = (int *)0x0;
  }
  else {
    local_7c = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_7c + 0x40))("topcrnhv.png");
  (**(code **)(*local_7c + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_007b8330);
  FUN_007d2110(local_7c,0);
  ExceptionList = local_10;
  return param_1;
}

