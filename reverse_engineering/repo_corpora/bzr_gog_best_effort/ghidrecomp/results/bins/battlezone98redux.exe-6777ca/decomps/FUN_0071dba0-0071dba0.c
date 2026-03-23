
undefined4 __thiscall FUN_0071dba0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008541d8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0071e5c0(param_3);
  local_8 = 0;
  FUN_0071e180(param_2);
  ExceptionList = local_10;
  return param_1;
}

