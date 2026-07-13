
undefined4 __thiscall FUN_007e98d0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008634d8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007de600(param_2);
  local_8 = 0;
  FUN_007de810(param_3);
  ExceptionList = local_10;
  return param_1;
}

