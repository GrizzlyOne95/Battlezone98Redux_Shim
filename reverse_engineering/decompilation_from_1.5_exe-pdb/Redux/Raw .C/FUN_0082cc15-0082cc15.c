
void FUN_0082cc15(int param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
    FUN_00830222(param_1);
  }
  uVar3 = FUN_0082c489(param_1);
  iVar4 = FUN_0082fb61(param_1,param_3,uVar3);
  *(undefined4 *)(iVar4 + 0x10) = param_2;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + param_3 * -0x10;
  if (param_3 != 0) {
    puVar6 = (undefined4 *)(param_3 * 0x10 + 0x18 + iVar4);
    do {
      puVar1 = puVar6 + -4;
      puVar5 = (undefined4 *)((int)puVar1 + *(int *)(param_1 + 8) + (-0x18 - iVar4));
      *puVar1 = *puVar5;
      puVar6[-3] = puVar5[1];
      puVar6[-2] = puVar5[2];
      param_3 = param_3 + -1;
      puVar6 = puVar1;
    } while (param_3 != 0);
  }
  piVar2 = *(int **)(param_1 + 8);
  *piVar2 = iVar4;
  piVar2[2] = 6;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  return;
}

