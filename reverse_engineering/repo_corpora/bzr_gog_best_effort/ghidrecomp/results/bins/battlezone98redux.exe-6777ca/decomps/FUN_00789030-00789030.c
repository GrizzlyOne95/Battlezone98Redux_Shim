
undefined4 * __fastcall FUN_00789030(undefined4 *param_1)

{
  uint uVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 local_68;
  int *local_58;
  int *local_4c;
  int *local_44;
  int *local_3c;
  int *local_38;
  int *local_34;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e82c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0(uVar1);
  local_8 = 0;
  *param_1 = cUI_Esc::vftable;
  DAT_009454ec = param_1;
  *(undefined1 *)(param_1 + 0x51) = 0;
  pvVar2 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar2 == (void *)0x0) {
    local_68 = 0;
  }
  else {
    local_68 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(2);
  FUN_007d2870("esc_center.png");
  FUN_007d2110(local_68,0);
  uVar3 = FUN_0081cb40("escape","return_to_game");
  uVar4 = FUN_0081cb40("escape","save_game");
  uVar5 = FUN_0081cb40("escape","load_game");
  uVar6 = FUN_0081cb40("escape","restart_mission");
  uVar7 = FUN_0081cb40("escape","abort_mission");
  uVar8 = FUN_0081cb40("escape","options",uVar1,uVar7);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar2 == (void *)0x0) {
    local_44 = (int *)0x0;
  }
  else {
    local_44 = (int *)FUN_007c2480(&DAT_00877f98,0x3f800000,0,0x43ab0000,0x429a0000,0x20,0,
                                   0x41e00000,0);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_44 + 0x40))("topcrnhv.png");
  (**(code **)(*local_44 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar3);
  FUN_007c23e0(FUN_00788ea0);
  FUN_007d2110(local_44,0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 3;
  if (pvVar2 == (void *)0x0) {
    local_4c = (int *)0x0;
  }
  else {
    local_4c = (int *)FUN_007c2480("Options_EscScreen",0,0x447ac000,0x43ab0000,0x429a0000,0x24,0,
                                   0x41e00000,0x40a00000);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_4c + 0x40))("topcrnhv.png");
  (**(code **)(*local_4c + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar8);
  FUN_007c23e0(FUN_00788eb0);
  FUN_007d2110(local_4c,0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 4;
  if (pvVar2 == (void *)0x0) {
    local_3c = (int *)0x0;
  }
  else {
    local_3c = (int *)FUN_007c2480(&DAT_0087d2a8,0x43fe0000,0x43500000,0x43d30000,0x43020000,0x20,
                                   local_68,0,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_3c + 0x40))("optionhv.png");
  (**(code **)(*local_3c + 0x3c))("optionck.png");
  FUN_007c2950(uVar4);
  FUN_007c30e0(0x3fc00000);
  FUN_007c23e0(FUN_00788ed0);
  FUN_007d2110(local_3c,0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 5;
  if (pvVar2 == (void *)0x0) {
    local_34 = (int *)0x0;
  }
  else {
    local_34 = (int *)FUN_007c2480(&DAT_0087d1e8,0x43fe0000,0x43c10000,0x43d30000,0x43020000,0x20,
                                   local_68,0,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_34 + 0x40))("optionhv.png");
  (**(code **)(*local_34 + 0x3c))("optionck.png");
  FUN_007c2950(uVar5);
  FUN_007c30e0(0x3fc00000);
  FUN_007c23e0(FUN_00788ec0);
  FUN_007d2110(local_34,0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 6;
  if (pvVar2 == (void *)0x0) {
    local_58 = (int *)0x0;
  }
  else {
    local_58 = (int *)FUN_007c2480("Restart",0x43fe0000,0x440d0000,0x43d30000,0x43020000,0x20,
                                   local_68,0,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_58 + 0x40))("optionhv.png");
  (**(code **)(*local_58 + 0x3c))("optionck.png");
  FUN_007c2950(uVar6);
  FUN_007c30e0(0x3fc00000);
  FUN_007c23e0(FUN_00788ef0);
  FUN_007d2110(local_58,0);
  pvVar2 = operator_new(0x1ec);
  local_8._0_1_ = 7;
  if (pvVar2 == (void *)0x0) {
    local_38 = (int *)0x0;
  }
  else {
    local_38 = (int *)FUN_007c2480("Abort",0x43fe0000,0x44394000,0x43d30000,0x43020000,0x20,local_68
                                   ,0,0);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  (**(code **)(*local_38 + 0x40))("optionhv.png");
  (**(code **)(*local_38 + 0x3c))("optionck.png");
  FUN_007c2950(uVar7);
  FUN_007c30e0(0x3fc00000);
  FUN_007c23e0(FUN_00788ee0);
  FUN_007d2110(local_38,0);
  (*(code *)PTR_FUN_008e75e8)();
  ExceptionList = local_10;
  return param_1;
}

