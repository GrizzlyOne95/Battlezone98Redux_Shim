
undefined4 __thiscall FUN_00727290(undefined4 param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855578;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006f62b0(param_2);
  local_8 = 0;
  FUN_006f63a0(param_2 + 0x18);
  ExceptionList = local_10;
  return param_1;
}

