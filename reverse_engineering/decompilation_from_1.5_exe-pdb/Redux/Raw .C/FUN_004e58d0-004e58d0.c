
undefined4 * __thiscall FUN_004e58d0(undefined4 *param_1,int param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  void *pvVar4;
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
  *param_1 = GotoTask::vftable;
  if (param_3 == 0) {
    uVar2 = FUN_004623e0();
    FUN_007d6b70("GotoTask: me=\"%s\" who=NULL\n",uVar2);
    param_1[2] = 0xd;
    param_1[3] = 0xd;
    param_1[0x4d] = 0;
    *(undefined1 *)(param_1 + 0x4f) = 0;
    param_1[0x4e] = 0;
  }
  else {
    param_1[2] = 1;
    param_1[3] = 1;
    puVar3 = (undefined4 *)(**(code **)(*(int *)(param_3 + 0x18) + 0xc))(uVar1);
    param_1[0x50] = *puVar3;
    param_1[0x51] = puVar3[1];
    param_1[0x52] = puVar3[2];
    pvVar4 = operator_new(0x18);
    local_8._0_1_ = 1;
    if (pvVar4 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      puVar3 = param_1 + 0x50;
      uVar2 = (**(code **)(*(int *)(param_2 + 0x18) + 0xc))(puVar3);
      local_1c = FUN_00460490(uVar2,puVar3);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x4d] = local_1c;
    *(undefined1 *)(param_1 + 0x4f) = 1;
    param_1[0x4e] = 0;
    *(undefined1 *)((int)param_1 + 0x13d) = 1;
    *(undefined1 *)((int)param_1 + 0x13e) = 0;
    uVar2 = FUN_00462380();
    param_1[0x1e] = uVar2;
  }
  ExceptionList = local_10;
  return param_1;
}

