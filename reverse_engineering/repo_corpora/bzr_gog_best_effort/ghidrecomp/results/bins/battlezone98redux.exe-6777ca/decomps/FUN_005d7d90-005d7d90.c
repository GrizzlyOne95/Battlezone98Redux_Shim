
undefined4 * __thiscall FUN_005d7d90(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847688;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_005fe690(param_2,param_3);
  local_8 = 0;
  *param_1 = SoldierAttack::vftable;
  uVar2 = FUN_004775b0(param_3,uVar1);
  param_1[0x41] = uVar2;
  FUN_004776e0(param_2,param_1);
  param_1[2] = 1;
  param_1[3] = 1;
  param_1[0x3c] = 0x42200000;
  ExceptionList = local_10;
  return param_1;
}

