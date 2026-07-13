
undefined4 __thiscall FUN_007de4d0(undefined4 param_1,int param_2)

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
  FUN_007de810(param_2 + 0x3c);
  ExceptionList = local_10;
  return param_1;
}

