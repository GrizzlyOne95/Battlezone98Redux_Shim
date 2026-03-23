
undefined4 * __thiscall FUN_0049b840(undefined4 *param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  void *pvVar2;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849484;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0047e9c0(param_2,param_3);
  local_8 = 0;
  *param_1 = CommTower::vftable;
  param_1[6] = CommTower::vftable;
  param_1[0x8e] = 0;
  pvVar2 = operator_new(0x14);
  local_8._0_1_ = 1;
  if (pvVar2 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_005c18e0(param_1);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  param_1[0x8f] = local_1c;
  *(undefined4 *)param_1[0x8f] = *(undefined4 *)(param_3 + 0x160);
  *(undefined4 *)(param_1[0x8f] + 4) = *(undefined4 *)(param_3 + 0x164);
  FUN_005ca980(param_2,uVar1);
  ExceptionList = local_10;
  return param_1;
}

