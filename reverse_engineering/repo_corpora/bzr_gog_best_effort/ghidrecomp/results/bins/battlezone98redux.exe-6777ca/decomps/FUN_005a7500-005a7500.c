
undefined4 * FUN_005a7500(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c2c8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0047e9c0(param_1,param_2);
  local_8 = 0;
  *local_14 = PowerPlant::vftable;
  local_14[6] = PowerPlant::vftable;
  local_18 = local_14;
  FUN_0041fe40(&local_18);
  FUN_0062a270(local_14[0x3d],4,local_14 + 0x8e,uVar1);
  ExceptionList = local_10;
  return local_14;
}

