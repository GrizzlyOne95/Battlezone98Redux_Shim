
void __fastcall FUN_0078b1f0(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_1a0;
  int *local_198;
  undefined4 local_190;
  int local_180;
  undefined1 local_178 [256];
  char local_78 [100];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e9e8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0(local_14);
  local_8 = 0;
  *param_1 = cUI_Load::vftable;
  DAT_00945500 = param_1;
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_1a0 = 0;
  }
  else {
    local_1a0 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(1);
  FUN_007d2110(local_1a0,0);
  uVar2 = FUN_0081cb40("single",&DAT_008714b0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar1 == (void *)0x0) {
    local_198 = (int *)0x0;
  }
  else {
    local_198 = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_198 + 0x40))("topcrnhv.png");
  (**(code **)(*local_198 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar2);
  FUN_007c23e0(FUN_0078aea0);
  FUN_007d2110(local_198,0);
  uVar2 = DAT_0091830c;
  for (local_180 = 0; local_180 < 10; local_180 = local_180 + 1) {
    _snprintf(local_78,100,"LoadSlot_%d",local_180);
    pvVar1 = operator_new(0x1ec);
    local_8._0_1_ = 3;
    if (pvVar1 == (void *)0x0) {
      local_190 = 0;
    }
    else {
      local_190 = FUN_007c2480(local_78,0x43070000,(float)(local_180 * 0x44 + 0xb4),0x44898000,
                               0x42680000,0x22,local_1a0,0,0);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[local_180 + 0x51] = local_190;
    iVar3 = FUN_004fe280(local_180 + 1,local_178,0x100);
    if (iVar3 == 0) {
      uVar4 = FUN_0081cb40("multi_error","empty");
      FUN_007c2950(uVar4);
      FUN_007c3040(0);
    }
    else {
      FUN_007c2950(local_178);
      FUN_007c30e0(0x3f400000);
    }
    FUN_007d2870("mpcron.png");
    (**(code **)(*(int *)param_1[local_180 + 0x51] + 0x40))("mpcrclk.png");
    FUN_007d2110(param_1[local_180 + 0x51],0);
  }
  DAT_0091830c = uVar2;
  FUN_007c23c0(FUN_0078aff0);
  FUN_007c23c0(FUN_0078b010);
  FUN_007c23c0(FUN_0078b030);
  FUN_007c23c0(FUN_0078b050);
  FUN_007c23c0(FUN_0078b070);
  FUN_007c23c0(FUN_0078b090);
  FUN_007c23c0(FUN_0078b0b0);
  FUN_007c23c0(FUN_0078b0d0);
  FUN_007c23c0(FUN_0078b0f0);
  FUN_007c23c0(FUN_0078b110);
  FUN_007c23e0(FUN_0078aeb0);
  FUN_007c23e0(FUN_0078aed0);
  FUN_007c23e0(FUN_0078aef0);
  FUN_007c23e0(FUN_0078af10);
  FUN_007c23e0(FUN_0078af30);
  FUN_007c23e0(FUN_0078af50);
  FUN_007c23e0(FUN_0078af70);
  FUN_007c23e0(FUN_0078af90);
  FUN_007c23e0(FUN_0078afb0);
  FUN_007c23e0(FUN_0078afd0);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

