
undefined4 __fastcall FUN_0081be80(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008458bb;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0081bef0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  basic_string<>();
  local_8 = 0;
  vector<>();
  ExceptionList = local_10;
  return param_1;
}

