
void __thiscall FUN_008405e0(undefined4 *param_1,void **param_2)

{
  short *psVar1;
  short sVar2;
  char cVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  int iVar7;
  short *psVar8;
  uint uVar9;
  void **ppvVar10;
  uint local_48;
  void **local_44;
  void *local_40 [4];
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
  puStack_8 = &LAB_0086578a;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_48;
  ExceptionList = &local_c;
  local_48 = 0;
  iVar7 = param_1[4];
  local_44 = param_2;
  iVar4 = FUN_008407b0(param_1,iVar7,DAT_008e7000 ^ (uint)&stack0xffffffa8);
  if ((iVar7 != 0) && (iVar4 != 0)) {
    puVar5 = param_1;
    if (7 < (uint)param_1[5]) {
      puVar5 = (undefined4 *)*param_1;
    }
    sVar2 = *(short *)((int)puVar5 + iVar4 * 2);
    if (((sVar2 == 0x2f) || (sVar2 == 0x5c)) && (cVar3 = FUN_00840b30(param_1,iVar4), cVar3 == '\0')
       ) {
      uVar6 = FUN_00840370();
      local_14 = 7;
      local_28[0] = (void *)((uint)local_28[0] & 0xffff0000);
      local_18 = 0;
      FID_conflict_assign(uVar6,0,0xffffffff);
      ppvVar10 = local_28;
      uVar9 = 1;
      goto LAB_008406ea;
    }
  }
  if (7 < (uint)param_1[5]) {
    param_1 = (undefined4 *)*param_1;
  }
  local_2c = 7;
  psVar1 = (short *)((int)param_1 + iVar4 * 2);
  local_30 = 0;
  local_40[0] = (void *)((uint)local_40[0] & 0xffff0000);
  if (*psVar1 == 0) {
    iVar7 = 0;
  }
  else {
    psVar8 = psVar1;
    do {
      sVar2 = *psVar8;
      psVar8 = psVar8 + 1;
    } while (sVar2 != 0);
    iVar7 = (int)psVar8 - (int)(psVar1 + 1) >> 1;
  }
  FUN_0083fdc0(psVar1,iVar7);
  ppvVar10 = local_40;
  uVar9 = 2;
LAB_008406ea:
  param_2[5] = (void *)0x7;
  param_2[4] = (void *)0x0;
  *(undefined2 *)param_2 = 0;
  local_4 = 2;
  local_48 = uVar9;
  if (param_2 != ppvVar10) {
    if ((void *)0x7 < param_2[5]) {
      operator_delete(*param_2);
    }
    param_2[5] = (void *)0x7;
    param_2[4] = (void *)0x0;
    *(undefined2 *)param_2 = 0;
    FID_conflict__Assign_rv(ppvVar10);
  }
  if ((uVar9 & 2) != 0) {
    uVar9 = uVar9 & 0xfffffffd;
    if (7 < local_2c) {
      operator_delete(local_40[0]);
    }
    local_2c = 7;
    local_30 = 0;
    local_40[0] = (void *)((uint)local_40[0] & 0xffff0000);
  }
  if (((uVar9 & 1) != 0) && (7 < local_14)) {
    operator_delete(local_28[0]);
  }
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

