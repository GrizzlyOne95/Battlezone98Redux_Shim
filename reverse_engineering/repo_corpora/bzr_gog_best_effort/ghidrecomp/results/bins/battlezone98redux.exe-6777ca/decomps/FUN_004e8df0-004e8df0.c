
undefined4 * FUN_004e8df0(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 local_20 [4];
  float local_1c;
  float local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a518;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_005fe690(param_1,param_2);
  local_8 = 0;
  *local_14 = GunTowerAttack::vftable;
  local_14[2] = 5;
  local_14[0x1c] = 0;
  FUN_00466be0(param_1,&local_18,&local_1c,local_20,local_14 + 0x2d,uVar1);
  local_14[0x27] = local_18 * local_18;
  local_14[0x28] = local_1c * local_1c;
  ExceptionList = local_10;
  return local_14;
}

