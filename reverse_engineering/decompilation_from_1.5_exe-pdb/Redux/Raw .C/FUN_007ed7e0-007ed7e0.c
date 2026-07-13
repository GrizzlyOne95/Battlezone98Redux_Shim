
undefined4 * __thiscall FUN_007ed7e0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863feb;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = param_2;
  FUN_007d7140(uVar1);
  local_8 = 0;
  param_1[8] = 0;
  *(undefined1 *)(param_1 + 9) = 0;
  FUN_007d71d0(param_3);
  uVar2 = FUN_007d7240(param_1 + 1);
  param_1[8] = uVar2;
  *(undefined1 *)(param_1 + 9) = 1;
  ExceptionList = local_10;
  return param_1;
}

