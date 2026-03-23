
undefined4 __thiscall FUN_007e3d70(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863458;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00726de0(param_2);
  local_8 = 0;
  FUN_007de110(param_3);
  ExceptionList = local_10;
  return param_1;
}

