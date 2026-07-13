
void __thiscall FUN_00841100(undefined4 *param_1,void **param_2)

{
  undefined4 *puVar1;
  int iVar2;
  void **ppvVar3;
  uint uVar4;
  uint local_48;
  void **local_44;
  void *local_40;
  undefined4 local_30;
  uint local_2c;
  void *local_28 [4];
  undefined4 local_18;
  uint local_14;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0086586a;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_48;
  ExceptionList = &local_c;
  local_44 = param_2;
  local_48 = 0;
  iVar2 = FUN_00840e80(DAT_008e7000 ^ (uint)&stack0xffffffac);
  if (iVar2 == -1) {
    local_14 = 7;
    local_18 = 0;
    local_28[0] = (void *)((uint)local_28[0] & 0xffff0000);
    ppvVar3 = local_28;
    uVar4 = 1;
  }
  else {
    puVar1 = param_1;
    if (7 < (uint)param_1[5]) {
      puVar1 = (undefined4 *)*param_1;
      param_1 = (undefined4 *)*param_1;
    }
    ppvVar3 = (void **)FUN_0083f6d0(param_1,(int)puVar1 + iVar2 * 2);
    uVar4 = 2;
  }
  param_2[5] = (void *)0x7;
  param_2[4] = (void *)0x0;
  *(undefined2 *)param_2 = 0;
  local_4 = 2;
  local_48 = uVar4;
  if (param_2 != ppvVar3) {
    if ((void *)0x7 < param_2[5]) {
      operator_delete(*param_2);
    }
    param_2[5] = (void *)0x7;
    param_2[4] = (void *)0x0;
    *(undefined2 *)param_2 = 0;
    FID_conflict__Assign_rv(ppvVar3);
  }
  if ((uVar4 & 2) != 0) {
    uVar4 = uVar4 & 0xfffffffd;
    if (7 < local_2c) {
      operator_delete(local_40);
    }
    local_2c = 7;
    local_30 = 0;
    local_40 = (void *)((uint)local_40 & 0xffff0000);
  }
  if (((uVar4 & 1) != 0) && (7 < local_14)) {
    operator_delete(local_28[0]);
  }
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

