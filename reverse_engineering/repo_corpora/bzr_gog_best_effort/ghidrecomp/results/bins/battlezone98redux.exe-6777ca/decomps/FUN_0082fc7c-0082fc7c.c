
void FUN_0082fc7c(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  iVar2 = *(int *)(param_1 + 0x10);
  piVar3 = *(int **)(iVar2 + 0x30);
  piVar4 = (int *)*piVar3;
  if (piVar4 == piVar3) {
    *(undefined4 *)(iVar2 + 0x30) = 0;
  }
  else {
    *piVar3 = *piVar4;
  }
  *piVar4 = **(undefined4 **)(iVar2 + 0x70);
  **(int **)(iVar2 + 0x70) = (int)piVar4;
  *(byte *)((int)piVar4 + 5) = *(byte *)(iVar2 + 0x14) & 3 | *(byte *)((int)piVar4 + 5) & 0xf8;
  iVar5 = piVar4[2];
  if ((iVar5 != 0) && ((*(byte *)(iVar5 + 6) & 4) == 0)) {
    puVar8 = (undefined4 *)FUN_0083347b(iVar5,2,*(undefined4 *)(*(int *)(param_1 + 0x10) + 0xc4));
    if (puVar8 != (undefined4 *)0x0) {
      uVar6 = *(undefined4 *)(iVar2 + 0x40);
      uVar1 = *(undefined1 *)(param_1 + 0x39);
      *(undefined1 *)(param_1 + 0x39) = 0;
      *(int *)(iVar2 + 0x40) = *(int *)(iVar2 + 0x44) * 2;
      puVar7 = *(undefined4 **)(param_1 + 8);
      *puVar7 = *puVar8;
      puVar7[1] = puVar8[1];
      puVar7[2] = puVar8[2];
      iVar5 = *(int *)(param_1 + 8);
      *(int **)(iVar5 + 0x10) = piVar4;
      *(undefined4 *)(iVar5 + 0x18) = 7;
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x20;
      FUN_0082f062(param_1,*(int *)(param_1 + 8) + -0x20,0);
      *(undefined1 *)(param_1 + 0x39) = uVar1;
      *(undefined4 *)(iVar2 + 0x40) = uVar6;
    }
  }
  return;
}

