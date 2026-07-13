
undefined4 __thiscall FUN_00727220(undefined4 param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855518;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006e51f0(param_2);
  local_8 = 0;
  FUN_0071e1c0(param_2 + 0x38);
  ExceptionList = local_10;
  return param_1;
}

