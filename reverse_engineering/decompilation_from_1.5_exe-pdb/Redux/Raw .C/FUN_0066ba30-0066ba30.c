
undefined4 __thiscall FUN_0066ba30(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_20 [4];
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e9e9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_14 = 0;
  local_18 = param_1;
  local_1c = FUN_0066c440(local_20,param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  FUN_0066c410(local_1c);
  local_8 = 0;
  local_14 = local_14 | 1;
  FUN_0066a3f0();
  ExceptionList = local_10;
  return param_2;
}

