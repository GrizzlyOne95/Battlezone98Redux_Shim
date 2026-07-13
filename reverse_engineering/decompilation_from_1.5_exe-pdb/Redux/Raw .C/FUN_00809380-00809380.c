
undefined4 __thiscall FUN_00809380(undefined4 param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008648b8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_008018b0(param_2);
  local_8 = 0;
  FUN_008018b0(param_2 + 0x34);
  ExceptionList = local_10;
  return param_1;
}

