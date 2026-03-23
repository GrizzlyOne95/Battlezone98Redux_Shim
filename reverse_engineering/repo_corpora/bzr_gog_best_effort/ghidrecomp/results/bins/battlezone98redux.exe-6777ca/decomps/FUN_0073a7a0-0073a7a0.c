
undefined4 * __thiscall FUN_0073a7a0(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 local_c4 [176];
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085a7eb;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  local_14 = param_1;
  FUN_004203f0(param_2,3,1);
  local_8 = 0;
  FUN_0073abd0(local_c4);
  local_8 = 0xffffffff;
  FUN_00417f10(uVar1);
  ExceptionList = local_10;
  return local_14;
}

