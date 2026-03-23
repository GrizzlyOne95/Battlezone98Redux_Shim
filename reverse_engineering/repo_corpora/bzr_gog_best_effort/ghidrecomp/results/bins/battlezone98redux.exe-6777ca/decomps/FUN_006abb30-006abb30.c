
void FUN_006abb30(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 local_40 [44];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ff88;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_004486f0(*param_1,param_1[1],param_2);
  local_8 = 0;
  FUN_006d89d0(local_40,uVar1);
  local_8 = 0xffffffff;
  FUN_00448770();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

