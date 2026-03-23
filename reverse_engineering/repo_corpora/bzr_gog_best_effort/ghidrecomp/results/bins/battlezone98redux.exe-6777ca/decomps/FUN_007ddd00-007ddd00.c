
undefined4 __thiscall FUN_007ddd00(undefined4 param_1,int param_2)

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
  FUN_007de110(param_2 + 0x18);
  ExceptionList = local_10;
  return param_1;
}

