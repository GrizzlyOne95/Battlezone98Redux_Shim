
void FUN_0082de88(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (*(int *)(param_1 + 0x74) != 0) {
    puVar3 = (undefined4 *)(*(int *)(param_1 + 0x20) + *(int *)(param_1 + 0x74));
    if (puVar3[2] != 6) {
      FUN_0082f657(param_1,5);
    }
    puVar1 = *(undefined4 **)(param_1 + 8);
    *puVar1 = puVar1[-4];
    puVar1[1] = puVar1[-3];
    puVar1[2] = puVar1[-2];
    iVar2 = *(int *)(param_1 + 8);
    *(undefined4 *)(iVar2 + -0x10) = *puVar3;
    *(undefined4 *)(iVar2 + -0xc) = puVar3[1];
    *(undefined4 *)(iVar2 + -8) = puVar3[2];
    if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0x11) {
      FUN_0082f194(param_1,1);
    }
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
    FUN_0082f062(param_1,*(int *)(param_1 + 8) + -0x20,1);
  }
  FUN_0082f657(param_1,2);
  return;
}

