
void __fastcall FUN_007ba6f0(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_1a4;
  undefined4 local_19c;
  int *local_198;
  undefined4 local_194;
  int local_180;
  undefined1 local_178 [256];
  char local_78 [100];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008616e7;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d0fa0(local_14);
  local_8 = 0;
  *param_1 = cUI_Save::vftable;
  param_1[0x53] = 0;
  param_1[0x5e] = 0;
  param_1[0x5f] = 0;
  param_1[0x60] = 0;
  param_1[0x61] = 0;
  param_1[0xbd] = 0xffffffff;
  DAT_009455d0 = param_1;
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_1a4 = 0;
  }
  else {
    local_1a4 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  param_1[0x51] = local_1a4;
  FUN_007d3f20(1);
  FUN_007d2110(param_1[0x51],0);
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 2;
  if (pvVar1 == (void *)0x0) {
    local_19c = 0;
  }
  else {
    local_19c = FUN_007d1cc0("Save_box",0x42f00000,0x428c0000,0x44300000,0x43a20000,0x20,
                             param_1[0x51],0);
  }
  local_8._0_1_ = 0;
  param_1[0x52] = local_19c;
  FUN_007d2870("saveload_box.png");
  FUN_007d2110(param_1[0x52],0);
  uVar2 = FUN_0081cb40("single",&DAT_008714b0);
  pvVar1 = operator_new(0x1ec);
  local_8._0_1_ = 3;
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
  FUN_007c23e0(FUN_007b96f0);
  FUN_007d2110(local_198,0);
  uVar2 = DAT_0091830c;
  for (local_180 = 0; local_180 < 10; local_180 = local_180 + 1) {
    _snprintf(local_78,100,"SaveSlot_%d",local_180);
    pvVar1 = operator_new(0x1ec);
    local_8._0_1_ = 4;
    if (pvVar1 == (void *)0x0) {
      local_194 = 0;
    }
    else {
      local_194 = FUN_007c2480(local_78,0x43070000,(float)(local_180 * 0x3c + 400),0x44898000,
                               0x425c0000,0x22,param_1[0x51],0,0);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[local_180 + 0x54] = local_194;
    iVar3 = FUN_004fe280(local_180 + 1,local_178,0x100);
    if (iVar3 == 0) {
      uVar4 = FUN_0081cb40("multi_error","empty");
      FUN_007c2950(uVar4);
    }
    else {
      FUN_007c2950(local_178);
      FUN_007c30e0(0x3f400000);
    }
    FUN_007d2870("mpcron.png");
    (**(code **)(*(int *)param_1[local_180 + 0x54] + 0x40))("mpcrclk.png");
    FUN_007d2110(param_1[local_180 + 0x54],0);
  }
  DAT_0091830c = uVar2;
  FUN_007c23c0(FUN_007b9840);
  FUN_007c23c0(FUN_007b9860);
  FUN_007c23c0(FUN_007b9880);
  FUN_007c23c0(FUN_007b98a0);
  FUN_007c23c0(FUN_007b98c0);
  FUN_007c23c0(FUN_007b98e0);
  FUN_007c23c0(FUN_007b9900);
  FUN_007c23c0(FUN_007b9920);
  FUN_007c23c0(FUN_007b9940);
  FUN_007c23c0(FUN_007b9960);
  FUN_007c23e0(FUN_007b9700);
  FUN_007c23e0(FUN_007b9720);
  FUN_007c23e0(FUN_007b9740);
  FUN_007c23e0(FUN_007b9760);
  FUN_007c23e0(FUN_007b9780);
  FUN_007c23e0(FUN_007b97a0);
  FUN_007c23e0(FUN_007b97c0);
  FUN_007c23e0(FUN_007b97e0);
  FUN_007c23e0(FUN_007b9800);
  FUN_007c23e0(FUN_007b9820);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

