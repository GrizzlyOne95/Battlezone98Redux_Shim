
undefined4 * __thiscall FUN_005b83e0(undefined4 *param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c5a8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004e6bf0(param_2,param_3,0x40c00000);
  local_8 = 0;
  *param_1 = ScavGotoScrap::vftable;
  uVar2 = (**(code **)(*(int *)(param_2 + 0x18) + 4))(uVar1);
  FUN_005a3870(uVar2);
  param_1[0x3f] = 0x40a00000;
  param_1[0x1b] = 0x3f800000;
  param_1[0x48] = 0;
  ExceptionList = local_10;
  return param_1;
}

