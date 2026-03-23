
undefined4 * __thiscall FUN_0046dd90(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847588;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0047e9c0(param_2,param_3);
  local_8 = 0;
  *param_1 = AnimBuilding::vftable;
  param_1[6] = AnimBuilding::vftable;
  FUN_0062a270(param_1[0x3d],4,param_1 + 0x8e,uVar1);
  ExceptionList = local_10;
  return param_1;
}

