
undefined4 __thiscall FUN_00810ef0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008648b8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_00417780(param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  FUN_008018b0(uVar1);
  local_8 = 0;
  uVar1 = FUN_00417780(param_3);
  FUN_008018b0(uVar1);
  ExceptionList = local_10;
  return param_1;
}

