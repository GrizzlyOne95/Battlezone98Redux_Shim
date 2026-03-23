
undefined4 * __thiscall FUN_006f5df0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085427b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_006ff500(param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  *param_1 = uVar1;
  FUN_0068b0a0();
  local_8 = 0;
  FUN_006d7500(param_1 + 1);
  ExceptionList = local_10;
  return param_1;
}

