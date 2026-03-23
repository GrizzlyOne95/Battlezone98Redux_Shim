
undefined4 __fastcall FUN_00667460(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e298;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00662ea0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_006673e0();
  FUN_006673e0();
  ExceptionList = local_10;
  return param_1;
}

