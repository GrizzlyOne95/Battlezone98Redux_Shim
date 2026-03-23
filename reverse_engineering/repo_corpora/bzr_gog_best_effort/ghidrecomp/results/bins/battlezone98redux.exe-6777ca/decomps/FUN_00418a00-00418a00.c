
bool __thiscall FUN_00418a00(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  bool bVar7;
  float10 fVar8;
  int local_14;
  int local_10;
  
  if (*(int *)(param_1 + 0x18) == 0) {
    bVar7 = false;
  }
  else {
    *(int *)(param_1 + 0x38) = (param_3 - param_2) / 2;
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x38) + param_2;
    *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x38) / 0x14;
    iVar2 = *(int *)(param_1 + 0x38) / 5;
    iVar1 = *(int *)(param_1 + 0x38);
    iVar3 = (*(int *)(param_1 + 0x38) - *(int *)(param_1 + 0x3c)) - iVar2;
    local_14 = *(int *)(DAT_0094672c + 0x3c);
    if (local_14 < 0) {
      local_14 = 0;
    }
    if (10 < local_14) {
      local_14 = 10;
    }
    FUN_00421b30(*(int *)(param_1 + 0x38) + 1 + *(int *)(param_1 + 0x38));
    for (local_10 = 1; iVar6 = iVar3, local_10 <= iVar3; local_10 = local_10 + 1) {
      fVar8 = (float10)FUN_004178d0((float)local_10 * (1.0 / (float)iVar3),
                                    (float)(10 - local_14) * 0.025 + 1.0);
      iVar6 = (int)((float)fVar8 * 65536.0 + 0.5);
      piVar4 = (int *)FUN_004200d0((iVar1 - *(int *)(param_1 + 0x3c)) - local_10);
      *piVar4 = iVar6;
      piVar4 = (int *)FUN_004200d0(iVar1 + *(int *)(param_1 + 0x3c) + local_10);
      *piVar4 = -iVar6;
    }
    while (local_10 = iVar6 + 1, local_10 <= iVar3 + iVar2) {
      puVar5 = (undefined4 *)FUN_004200d0((iVar1 - *(int *)(param_1 + 0x3c)) - local_10);
      *puVar5 = 0x10000;
      puVar5 = (undefined4 *)FUN_004200d0(iVar1 + *(int *)(param_1 + 0x3c) + local_10);
      *puVar5 = 0xffff0000;
      iVar6 = local_10;
    }
    bVar7 = *(int *)(param_1 + 0x18) != 0;
  }
  return bVar7;
}

