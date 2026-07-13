
undefined4 * __thiscall FUN_006cf730(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085288b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_006dd7e0(param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  *param_1 = uVar1;
  FUN_006d1180();
  local_8 = 0;
  FUN_006d33e0(param_1 + 2);
  ExceptionList = local_10;
  return param_1;
}

