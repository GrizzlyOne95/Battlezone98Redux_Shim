
undefined4 * __thiscall FUN_006f61c0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085288b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_006ff510(param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  *param_1 = uVar1;
  FUN_006f6a60();
  local_8 = 0;
  FUN_006f7150(param_1 + 2);
  ExceptionList = local_10;
  return param_1;
}

