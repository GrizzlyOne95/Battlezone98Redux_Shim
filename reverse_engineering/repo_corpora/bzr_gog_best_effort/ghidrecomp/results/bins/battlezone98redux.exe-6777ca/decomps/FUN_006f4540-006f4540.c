
undefined4 * __thiscall
FUN_006f4540(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00854140;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = param_2;
  param_1[1] = param_3;
  local_8 = 1;
  FUN_006f6410(param_4);
  local_8 = 0xffffffff;
  FUN_00417c60(uVar1);
  ExceptionList = local_10;
  return param_1;
}

