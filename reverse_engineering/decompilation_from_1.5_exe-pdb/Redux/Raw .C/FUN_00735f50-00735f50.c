
undefined4 __thiscall FUN_00735f50(undefined4 param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856cc8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  <>(param_2);
  local_8 = 0;
  FUN_00734690(param_2 + 0x38);
  ExceptionList = local_10;
  return param_1;
}

