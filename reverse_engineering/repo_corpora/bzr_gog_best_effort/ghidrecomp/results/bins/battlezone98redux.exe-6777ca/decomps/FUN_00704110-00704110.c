
undefined4 __thiscall FUN_00704110(undefined4 param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856c68;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006acc60(FUN_00706ea0);
  local_8 = 0;
  FUN_006e51f0(param_2);
  ExceptionList = local_10;
  return param_1;
}

