
undefined4 FUN_007ff000(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008646c8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = 0;
  <>(param_2);
  local_8 = 0;
  FUN_007fc730(local_24);
  local_14 = local_14 | 1;
  local_8 = 0xffffffff;
  FUN_007fb7a0(uVar1);
  ExceptionList = local_10;
  return param_1;
}

