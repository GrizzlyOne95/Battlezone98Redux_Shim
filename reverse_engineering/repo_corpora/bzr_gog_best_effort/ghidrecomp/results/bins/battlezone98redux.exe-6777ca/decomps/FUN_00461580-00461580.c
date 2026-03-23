
undefined4 * __thiscall FUN_00461580(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847398;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_005d7300(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = AiProcess::vftable;
  param_1[2] = param_2;
  param_1[4] = 0;
  FUN_0045ccc0(param_1);
  param_1[3] = param_3;
  param_1[5] = 0;
  if (param_1[3] != 0) {
    FUN_004db910(param_1);
  }
  ExceptionList = local_10;
  return param_1;
}

