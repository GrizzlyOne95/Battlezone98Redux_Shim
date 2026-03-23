
undefined4 __thiscall FUN_00711f90(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857c48;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006b1320(param_2,FUN_00713670);
  local_8 = 0;
  FUN_006f4320(param_3);
  ExceptionList = local_10;
  return param_1;
}

