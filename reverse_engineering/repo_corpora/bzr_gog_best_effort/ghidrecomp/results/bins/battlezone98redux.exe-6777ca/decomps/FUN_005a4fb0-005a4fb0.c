
undefined4 * __thiscall FUN_005a4fb0(undefined4 *param_1,int param_2,int param_3)

{
  uint uVar1;
  void *pvVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a404;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_005fe690(param_2,param_3);
  local_8 = 0;
  *param_1 = PersonStraight::vftable;
  param_1[2] = 2;
  if (param_3 != 0) {
    pvVar2 = operator_new(0x18);
    local_8._0_1_ = 1;
    if (pvVar2 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_00460390(0,2);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x10] = local_1c;
    puVar3 = (undefined4 *)(**(code **)(*(int *)(param_2 + 0x18) + 0xc))(uVar1);
    **(undefined4 **)(param_1[0x10] + 8) = *puVar3;
    iVar4 = (**(code **)(*(int *)(param_2 + 0x18) + 0xc))();
    *(undefined4 *)(*(int *)(param_1[0x10] + 8) + 4) = *(undefined4 *)(iVar4 + 8);
    puVar3 = (undefined4 *)(**(code **)(*(int *)(param_3 + 0x18) + 0xc))();
    *(undefined4 *)(*(int *)(param_1[0x10] + 8) + 8) = *puVar3;
    iVar4 = (**(code **)(*(int *)(param_3 + 0x18) + 0xc))();
    *(undefined4 *)(*(int *)(param_1[0x10] + 8) + 0xc) = *(undefined4 *)(iVar4 + 8);
    *(undefined4 *)(param_1[0x10] + 0x10) = 0;
    param_1[0x11] = 1;
  }
  ExceptionList = local_10;
  return param_1;
}

