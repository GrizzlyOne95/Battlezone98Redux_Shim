
undefined4 __thiscall FUN_00735da0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856cc8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  <>(param_3);
  local_8 = 0;
  FUN_00735e10(param_2);
  ExceptionList = local_10;
  return param_1;
}

