
undefined4 __thiscall FUN_007271b0(undefined4 param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008541d8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006e5080(param_2);
  local_8 = 0;
  FUN_0071e180(param_2 + 0x40);
  ExceptionList = local_10;
  return param_1;
}

