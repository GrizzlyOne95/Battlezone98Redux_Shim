
undefined4 * __fastcall FUN_0073ae30(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085a818;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0073b750(0);
  local_8 = 0;
  *param_1 = cGogInterface::vftable;
  param_1[2] = 1;
  FUN_007d6a70("gogInitState = 1;\n",uVar1);
  ExceptionList = local_10;
  return param_1;
}

