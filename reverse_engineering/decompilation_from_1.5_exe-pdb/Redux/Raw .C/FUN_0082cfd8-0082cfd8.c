
void FUN_0082cfd8(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if ((param_2 == -0x2711) && (*(int *)(param_1 + 0x14) == *(int *)(param_1 + 0x28))) {
    FUN_0082df5b(param_1,"no calling environment");
  }
  puVar4 = (undefined4 *)FUN_0082c4a6(param_1,param_2);
  if (param_2 == -0x2711) {
    iVar2 = **(int **)(*(int *)(param_1 + 0x14) + 4);
    *(undefined4 *)(iVar2 + 0xc) = *(undefined4 *)(*(int *)(param_1 + 8) + -0x10);
    if ((*(int *)(*(int *)(param_1 + 8) + -8) < 4) ||
       (iVar3 = *(int *)(*(int *)(param_1 + 8) + -0x10), (*(byte *)(iVar3 + 5) & 3) == 0))
    goto LAB_0082d086;
    bVar1 = *(byte *)(iVar2 + 5);
  }
  else {
    iVar3 = *(int *)(param_1 + 8);
    *puVar4 = *(undefined4 *)(iVar3 + -0x10);
    puVar4[1] = *(undefined4 *)(iVar3 + -0xc);
    puVar4[2] = *(undefined4 *)(iVar3 + -8);
    if (((-0x2713 < param_2) || (*(int *)(*(int *)(param_1 + 8) + -8) < 4)) ||
       (iVar3 = *(int *)(*(int *)(param_1 + 8) + -0x10), (*(byte *)(iVar3 + 5) & 3) == 0))
    goto LAB_0082d086;
    iVar2 = **(int **)(*(int *)(param_1 + 0x14) + 4);
    bVar1 = *(byte *)(iVar2 + 5);
  }
  if ((bVar1 & 4) != 0) {
    FUN_0083001b(param_1,iVar2,iVar3);
  }
LAB_0082d086:
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0x10;
  return;
}

