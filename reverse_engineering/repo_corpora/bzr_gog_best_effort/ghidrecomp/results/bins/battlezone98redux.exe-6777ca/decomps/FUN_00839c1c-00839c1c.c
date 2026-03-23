
void FUN_00839c1c(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  piVar1 = *(int **)(param_1 + 0x30);
  iVar2 = *(int *)(param_1 + 0x34);
  iVar3 = *piVar1;
  FUN_0083b0a4(param_1,0);
  FUN_0083cd4c(piVar1,0,0);
  if (piVar1[6] + 1U < 0x40000000) {
    uVar4 = FUN_00838869(iVar2,*(undefined4 *)(iVar3 + 0xc),*(int *)(iVar3 + 0x2c) << 2,
                         piVar1[6] << 2);
  }
  else {
    uVar4 = FUN_008388ab(iVar2);
  }
  *(undefined4 *)(iVar3 + 0xc) = uVar4;
  *(int *)(iVar3 + 0x2c) = piVar1[6];
  if (piVar1[6] + 1U < 0x40000000) {
    uVar4 = FUN_00838869(iVar2,*(undefined4 *)(iVar3 + 0x14),*(int *)(iVar3 + 0x30) << 2,
                         piVar1[6] << 2);
  }
  else {
    uVar4 = FUN_008388ab(iVar2);
  }
  *(undefined4 *)(iVar3 + 0x14) = uVar4;
  *(int *)(iVar3 + 0x30) = piVar1[6];
  if (piVar1[10] + 1U < 0x10000000) {
    uVar4 = FUN_00838869(iVar2,*(undefined4 *)(iVar3 + 8),*(int *)(iVar3 + 0x28) << 4,
                         piVar1[10] << 4);
  }
  else {
    uVar4 = FUN_008388ab(iVar2);
  }
  *(undefined4 *)(iVar3 + 8) = uVar4;
  *(int *)(iVar3 + 0x28) = piVar1[10];
  if (piVar1[0xb] + 1U < 0x40000000) {
    uVar4 = FUN_00838869(iVar2,*(undefined4 *)(iVar3 + 0x10),*(int *)(iVar3 + 0x34) << 2,
                         piVar1[0xb] << 2);
  }
  else {
    uVar4 = FUN_008388ab(iVar2);
  }
  *(undefined4 *)(iVar3 + 0x10) = uVar4;
  *(int *)(iVar3 + 0x34) = piVar1[0xb];
  if ((int)(short)piVar1[0xc] + 1U < 0x15555556) {
    uVar4 = FUN_00838869(iVar2,*(undefined4 *)(iVar3 + 0x18),*(int *)(iVar3 + 0x38) * 0xc,
                         (short)piVar1[0xc] * 0xc);
  }
  else {
    uVar4 = FUN_008388ab(iVar2);
  }
  *(undefined4 *)(iVar3 + 0x18) = uVar4;
  *(int *)(iVar3 + 0x38) = (int)(short)piVar1[0xc];
  if (*(byte *)(iVar3 + 0x48) + 1 < 0x40000000) {
    uVar4 = FUN_00838869(iVar2,*(undefined4 *)(iVar3 + 0x1c),*(int *)(iVar3 + 0x24) << 2,
                         (uint)*(byte *)(iVar3 + 0x48) << 2);
  }
  else {
    uVar4 = FUN_008388ab(iVar2);
  }
  *(undefined4 *)(iVar3 + 0x1c) = uVar4;
  *(uint *)(iVar3 + 0x24) = (uint)*(byte *)(iVar3 + 0x48);
  *(int *)(param_1 + 0x30) = piVar1[2];
  if ((*(int *)(param_1 + 0x10) == 0x11d) || (*(int *)(param_1 + 0x10) == 0x11e)) {
    FUN_00838fac(param_1,*(int *)(param_1 + 0x18) + 0x10,
                 *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xc));
  }
  *(int *)(iVar2 + 8) = *(int *)(iVar2 + 8) + -0x20;
  return;
}

