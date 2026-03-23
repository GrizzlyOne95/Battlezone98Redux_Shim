
undefined4 * __fastcall FUN_007b61a0(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int *local_5c;
  int *local_54;
  int *local_4c;
  int *local_44;
  int *local_3c;
  undefined4 local_34;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861360;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d0fa0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cUI_OptionsParent::vftable;
  DAT_009455c4 = param_1;
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_34 = 0;
  }
  else {
    local_34 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(1);
  FUN_007d2870("esc_center.png");
  FUN_007d2110(local_34,0);
  uVar2 = FUN_0081cb40("options",&DAT_008714b0);
  uVar3 = FUN_0081cb40("options","play_options");
  uVar4 = FUN_0081cb40("options","graphic_options");
  uVar5 = FUN_0081cb40("options","audio_options");
  uVar6 = FUN_0081cb40("options","input_config");
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar1 == (void *)0x0) {
    local_3c = (int *)0x0;
  }
  else {
    local_3c = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_3c + 0x40))("topcrnhv.png");
  (**(code **)(*local_3c + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_007b60d0);
  FUN_007d2110(local_3c,0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 3;
  if (pvVar1 == (void *)0x0) {
    local_44 = (int *)0x0;
  }
  else {
    local_44 = (int *)FUN_007c2480(&DAT_0089fc10,0x43fe0000,0x43500000,0x43d30000,0x43020000,0x20,
                                   local_34,0,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_44 + 0x40))("optionhv.png");
  (**(code **)(*local_44 + 0x3c))("optionck.png");
  FUN_007c2950(uVar3);
  FUN_007c30e0(0x3fa66666);
  FUN_007c23e0(FUN_007b6110);
  FUN_007d2110(local_44,0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 4;
  if (pvVar1 == (void *)0x0) {
    local_4c = (int *)0x0;
  }
  else {
    local_4c = (int *)FUN_007c2480("Graphic",0x43fe0000,0x43c10000,0x43d30000,0x43020000,0x20,
                                   local_34,0,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_4c + 0x40))("optionhv.png");
  (**(code **)(*local_4c + 0x3c))("optionck.png");
  FUN_007c2950(uVar4);
  FUN_007c30e0(0x3fa66666);
  FUN_007c23e0(FUN_007b60f0);
  FUN_007d2110(local_4c,0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 5;
  if (pvVar1 == (void *)0x0) {
    local_54 = (int *)0x0;
  }
  else {
    local_54 = (int *)FUN_007c2480("Audio",0x43fe0000,0x440d0000,0x43d30000,0x43020000,0x20,local_34
                                   ,0,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_54 + 0x40))("optionhv.png");
  (**(code **)(*local_54 + 0x3c))("optionck.png");
  FUN_007c2950(uVar5);
  FUN_007c30e0(0x3fa66666);
  FUN_007c23e0(FUN_007b60e0);
  FUN_007d2110(local_54,0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 6;
  if (pvVar1 == (void *)0x0) {
    local_5c = (int *)0x0;
  }
  else {
    local_5c = (int *)FUN_007c2480("Input",0x43fe0000,0x44394000,0x43d30000,0x43020000,0x20,local_34
                                   ,0,0);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  (**(code **)(*local_5c + 0x40))("optionhv.png");
  (**(code **)(*local_5c + 0x3c))("optionck.png");
  FUN_007c2950(uVar6);
  FUN_007c30e0(0x3fa66666);
  FUN_007c23e0(FUN_007b6100);
  FUN_007d2110(local_5c,0);
  ExceptionList = local_10;
  return param_1;
}

