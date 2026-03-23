
undefined4 __thiscall FUN_004fed90(undefined4 param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084aa68;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  basic_string<>(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_004d07f0(param_2,param_1);
  ExceptionList = local_10;
  return param_1;
}

