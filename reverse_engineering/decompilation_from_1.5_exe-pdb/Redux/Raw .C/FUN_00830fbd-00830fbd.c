
undefined4 FUN_00830fbd(undefined4 param_1,int param_2,double *param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar2 = FUN_00830cca(param_1,param_2,param_3);
  iVar2 = iVar2 + 1;
  if (iVar2 < *(int *)(param_2 + 0x1c)) {
    piVar3 = (int *)(iVar2 * 0x10 + *(int *)(param_2 + 0xc) + 8);
    do {
      if (*piVar3 != 0) {
        *(undefined4 *)(param_3 + 1) = 3;
        *param_3 = (double)(iVar2 + 1);
        puVar5 = (undefined4 *)(iVar2 * 0x10 + *(int *)(param_2 + 0xc));
        *(undefined4 *)(param_3 + 2) = *puVar5;
        *(undefined4 *)((int)param_3 + 0x14) = puVar5[1];
        *(undefined4 *)(param_3 + 3) = puVar5[2];
        return 1;
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 4;
    } while (iVar2 < *(int *)(param_2 + 0x1c));
  }
  iVar2 = iVar2 - *(int *)(param_2 + 0x1c);
  iVar4 = 1 << (*(byte *)(param_2 + 7) & 0x1f);
  if (iVar2 < iVar4) {
    iVar1 = *(int *)(param_2 + 0x10);
    piVar3 = (int *)(iVar2 * 0x20 + 8 + iVar1);
    do {
      if (*piVar3 != 0) {
        iVar2 = iVar2 * 0x20;
        *(undefined4 *)param_3 = *(undefined4 *)(iVar1 + 0x10 + iVar2);
        *(undefined4 *)((int)param_3 + 4) = *(undefined4 *)(iVar1 + 0x14 + iVar2);
        *(undefined4 *)(param_3 + 1) = *(undefined4 *)(iVar1 + 0x18 + iVar2);
        iVar4 = *(int *)(param_2 + 0x10);
        *(undefined4 *)(param_3 + 2) = *(undefined4 *)(iVar4 + iVar2);
        *(undefined4 *)((int)param_3 + 0x14) = *(undefined4 *)(iVar4 + 4 + iVar2);
        *(undefined4 *)(param_3 + 3) = *(undefined4 *)(iVar4 + 8 + iVar2);
        return 1;
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 8;
    } while (iVar2 < iVar4);
  }
  return 0;
}

