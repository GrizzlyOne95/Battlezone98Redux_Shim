
void FUN_0082ef6c(int param_1,undefined4 *param_2)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  
  iVar2 = FUN_0082ec83(*param_2);
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
    FUN_00830222(param_1);
  }
  pcVar3 = FUN_0083aae9;
  if (iVar2 == 0x1b) {
    pcVar3 = FUN_0083bcb2;
  }
  iVar2 = (*pcVar3)(param_1,*param_2,param_2 + 1,param_2[4]);
  iVar4 = FUN_0082fba1(param_1,*(undefined1 *)(iVar2 + 0x48),*(undefined4 *)(param_1 + 0x48));
  iVar6 = 0;
  *(int *)(iVar4 + 0x10) = iVar2;
  if (*(char *)(iVar2 + 0x48) != '\0') {
    puVar7 = (undefined4 *)(iVar4 + 0x14);
    do {
      uVar5 = FUN_0082fc4b(param_1);
      *puVar7 = uVar5;
      iVar6 = iVar6 + 1;
      puVar7 = puVar7 + 1;
    } while (iVar6 < (int)(uint)*(byte *)(iVar2 + 0x48));
  }
  piVar1 = *(int **)(param_1 + 8);
  *piVar1 = iVar4;
  piVar1[2] = 6;
  if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0x11) {
    FUN_0082f194(param_1,1);
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  return;
}

