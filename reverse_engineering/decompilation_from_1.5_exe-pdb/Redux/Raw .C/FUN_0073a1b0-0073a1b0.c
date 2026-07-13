
undefined4 FUN_0073a1b0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008554c1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = forward<>(4,param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (iVar1 != 0) {
    FUN_0073a2c0(param_2);
  }
  ExceptionList = local_10;
  return 5;
}

