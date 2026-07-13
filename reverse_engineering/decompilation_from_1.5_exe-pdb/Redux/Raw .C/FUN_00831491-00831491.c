
void FUN_00831491(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  byte bVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  
  bVar1 = *(byte *)(param_2 + 7);
  iVar7 = *(int *)(param_2 + 0x1c);
  puVar2 = *(undefined **)(param_2 + 0x10);
  if (iVar7 < param_3) {
    FUN_008315d2(param_1,param_2,param_3);
  }
  FUN_00831635(param_1,param_2,param_4);
  if (param_3 < iVar7) {
    *(int *)(param_2 + 0x1c) = param_3;
    iVar8 = param_3 << 4;
    iVar10 = param_3;
    do {
      iVar3 = *(int *)(param_2 + 0xc);
      if (*(int *)(iVar3 + 8 + iVar8) != 0) {
        puVar4 = (undefined4 *)FUN_00831114(param_1,param_2,iVar10 + 1);
        *puVar4 = *(undefined4 *)(iVar3 + iVar8);
        puVar4[1] = *(undefined4 *)(iVar3 + 4 + iVar8);
        puVar4[2] = *(undefined4 *)(iVar3 + 8 + iVar8);
      }
      iVar10 = iVar10 + 1;
      iVar8 = iVar8 + 0x10;
    } while (iVar10 < iVar7);
    if (param_3 + 1U < 0x10000000) {
      uVar5 = FUN_00838869(param_1,*(undefined4 *)(param_2 + 0xc),iVar7 << 4,param_3 << 4);
    }
    else {
      uVar5 = FUN_008388ab(param_1);
    }
    *(undefined4 *)(param_2 + 0xc) = uVar5;
  }
  iVar8 = 1 << (bVar1 & 0x1f);
  iVar7 = iVar8 + -1;
  if (-1 < iVar7) {
    piVar9 = (int *)(puVar2 + iVar7 * 0x20 + 8);
    do {
      if (*piVar9 != 0) {
        piVar6 = (int *)FUN_008310b4(param_1,param_2,piVar9 + 2);
        *piVar6 = piVar9[-2];
        piVar6[1] = piVar9[-1];
        piVar6[2] = *piVar9;
      }
      iVar7 = iVar7 + -1;
      piVar9 = piVar9 + -8;
    } while (-1 < iVar7);
  }
  if (puVar2 != &DAT_0086eef0) {
    FUN_00838869(param_1,puVar2,iVar8 << 5,0);
  }
  return;
}

