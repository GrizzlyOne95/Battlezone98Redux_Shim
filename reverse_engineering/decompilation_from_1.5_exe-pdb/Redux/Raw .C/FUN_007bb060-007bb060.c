
undefined4 * __thiscall
FUN_007bb060(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846128;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007bb000(param_4);
  local_8 = 0;
  *param_1 = boost::system::system_error::vftable;
  param_1[3] = param_2;
  param_1[4] = param_3;
  basic_string<>(uVar1);
  ExceptionList = local_10;
  return param_1;
}

