
undefined4 __thiscall FUN_007bb5a0(undefined4 param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e298;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004fbb90(param_2);
  local_8 = 0;
  FUN_007bb540(param_2 + 0x18);
  FUN_007bb540(param_2 + 0x20);
  ExceptionList = local_10;
  return param_1;
}

