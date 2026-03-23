
void FUN_0058c5d0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int local_10;
  
  iVar4 = FUN_0058c280(*(float *)(param_1 + 8) + 0.1,*(undefined4 *)(param_1 + 4));
  if (iVar4 != 0) {
    iVar5 = FUN_0058be00(*(undefined4 *)(param_1 + 8));
    iVar1 = *(int *)(iVar4 + 0x10);
    local_10 = FUN_0058be00(*(undefined4 *)(param_1 + 4));
    local_10 = local_10 - *(int *)(iVar4 + 0x14);
    iVar6 = FUN_0058be00(*(undefined4 *)(param_1 + 0xc));
    iVar2 = *(int *)(iVar4 + 0x14);
    while (local_10 < iVar6 - iVar2) {
      piVar7 = (int *)FUN_004200d0(*(undefined1 *)(iVar4 + 0x18 + local_10 * 0x10 + (iVar5 - iVar1))
                                  );
      iVar3 = *piVar7;
      local_10 = FUN_0058be00(*(undefined4 *)(iVar3 + 0xc));
      local_10 = local_10 - *(int *)(iVar4 + 0x14);
      if ((*(int *)(iVar3 + 0x10) != 6) && (*(int *)(iVar3 + 0x10) != 5)) {
        FUN_0058bf50(param_1,iVar3);
      }
    }
  }
  return;
}

