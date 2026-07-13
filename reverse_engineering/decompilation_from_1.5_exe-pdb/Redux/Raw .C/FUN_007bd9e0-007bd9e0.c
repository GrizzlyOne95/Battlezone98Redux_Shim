
undefined4 * __thiscall FUN_007bd9e0(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ebbb;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = param_2;
  FUN_00423890(uVar1);
  local_8 = 0;
  FUN_007bdda0(param_1,param_2,param_1 + 1);
  ExceptionList = local_10;
  return param_1;
}

