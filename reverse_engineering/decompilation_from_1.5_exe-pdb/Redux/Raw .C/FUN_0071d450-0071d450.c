
undefined4 __thiscall FUN_0071d450(undefined4 param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849b78;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006ac9a0(FUN_0071d4c0);
  local_8 = 0;
  FUN_0070ff20(param_2);
  ExceptionList = local_10;
  return param_1;
}

