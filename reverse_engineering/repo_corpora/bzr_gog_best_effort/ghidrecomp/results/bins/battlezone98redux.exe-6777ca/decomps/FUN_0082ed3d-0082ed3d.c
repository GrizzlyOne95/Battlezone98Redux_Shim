
int FUN_0082ed3d(int param_1,int param_2,int param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  double *pdVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  int local_8;
  
  uVar8 = (uint)*(byte *)(param_2 + 0x49);
  local_8 = 0;
  if (param_3 < (int)uVar8) {
    iVar5 = uVar8 - param_3;
    param_3 = param_3 + iVar5;
    do {
      *(undefined4 *)(*(int *)(param_1 + 8) + 8) = 0;
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  if ((*(byte *)(param_2 + 0x4a) & 4) != 0) {
    iVar5 = param_3 - uVar8;
    if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
      FUN_00830222(param_1);
    }
    if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) <=
        (int)((uint)*(byte *)(param_2 + 0x4b) * 0x10)) {
      FUN_0082f194(param_1,(uint)*(byte *)(param_2 + 0x4b));
    }
    local_8 = FUN_00830f66(param_1,iVar5,1);
    iVar6 = 0;
    if (0 < iVar5) {
      iVar7 = iVar5 * -0x10;
      do {
        puVar9 = (undefined4 *)(*(int *)(param_1 + 8) + iVar7);
        iVar6 = iVar6 + 1;
        puVar2 = (undefined4 *)FUN_00831114(param_1,local_8,iVar6);
        iVar7 = iVar7 + 0x10;
        *puVar2 = *puVar9;
        puVar2[1] = puVar9[1];
        puVar2[2] = puVar9[2];
      } while (iVar6 < iVar5);
    }
    uVar3 = FUN_008309f4(param_1,&DAT_00894d94,1);
    pdVar4 = (double *)FUN_00831159(param_1,local_8,uVar3);
    *(undefined4 *)(pdVar4 + 1) = 3;
    *pdVar4 = (double)iVar5;
  }
  iVar5 = *(int *)(param_1 + 8);
  if (uVar8 != 0) {
    puVar2 = (undefined4 *)(iVar5 + param_3 * -0x10 + 8);
    do {
      puVar9 = *(undefined4 **)(param_1 + 8);
      *(undefined4 **)(param_1 + 8) = puVar9 + 4;
      *puVar9 = puVar2[-2];
      puVar9[1] = puVar2[-1];
      puVar9[2] = *puVar2;
      *puVar2 = 0;
      puVar2 = puVar2 + 4;
      uVar8 = uVar8 - 1;
    } while (uVar8 != 0);
  }
  if (local_8 != 0) {
    piVar1 = *(int **)(param_1 + 8);
    *(int **)(param_1 + 8) = piVar1 + 4;
    *piVar1 = local_8;
    piVar1[2] = 5;
  }
  return iVar5;
}

