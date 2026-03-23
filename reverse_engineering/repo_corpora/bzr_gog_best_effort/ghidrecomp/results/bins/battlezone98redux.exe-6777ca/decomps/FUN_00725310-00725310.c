
void __thiscall FUN_00725310(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858fd8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00726b60(param_2);
  local_8 = 0;
  FUN_0072a040(param_1 + 4,local_54);
  FUN_00417c60(uVar1);
  local_8 = 0xffffffff;
  FUN_00725f50();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

