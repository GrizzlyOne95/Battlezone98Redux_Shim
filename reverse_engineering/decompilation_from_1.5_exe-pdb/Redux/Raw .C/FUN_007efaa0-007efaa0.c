
void __thiscall FUN_007efaa0(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 local_3f;
  char local_3e;
  char local_3d;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863fb0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_007ed7e0(*param_1,0xffffffff);
  local_8 = 0;
  local_3d = 0;
  local_3f = 0;
  FUN_007ed940(*param_1);
  local_8._0_1_ = 1;
  local_3d = FUN_007f0690(param_2,*param_1,param_1[1],param_1[2],param_1[3],&local_3f,uVar1);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007ed6c0();
  if (local_3d != '\0') {
    FUN_007ed8e0(0xffffffff,1);
  }
  local_3e = local_3d;
  local_8 = 0xffffffff;
  FUN_007ed880();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

