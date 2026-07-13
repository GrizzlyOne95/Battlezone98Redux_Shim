
undefined4 __thiscall FUN_007e3a80(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008634a8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007de230(param_2);
  local_8 = 0;
  FUN_007d9f70(param_3);
  ExceptionList = local_10;
  return param_1;
}

