
undefined4 FUN_0043b210(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if ((*(uint *)(param_1 + 0x70) & 0x200) == 0) {
    iVar2 = FUN_00481af0(param_1 + 4);
    *(int *)(param_1 + 0x50) = iVar2;
    *(int *)(param_1 + 0x4c) = iVar2;
    if (iVar2 == 0) {
      return 0;
    }
    uVar1 = FUN_00481a60(param_1 + 4);
    *(undefined4 *)(param_1 + 0x54) = uVar1;
  }
  else {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x4c);
    if (*(int *)(param_1 + 0x50) == 0) {
      return 0;
    }
  }
  if (**(int **)(param_1 + 0x4c) == 0x30534147) {
    *(int *)(param_1 + 0x50) = *(int *)(param_1 + 0x50) + 0x1c;
    puVar3 = *(undefined4 **)(param_1 + 0x4c);
    puVar4 = (undefined4 *)(param_1 + 0x30);
    for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    FUN_0043b040(*(undefined4 *)(param_1 + 0x4c),param_1 + 0x30);
  }
  *(undefined1 *)(param_1 + 0x6f) = *(undefined1 *)(param_1 + 0x34);
  if ((*(uint *)(param_1 + 0x70) & 0x200) == 0) {
    FUN_00481990(param_1 + 4);
    *(undefined4 *)(param_1 + 0x4c) = 0;
    *(undefined4 *)(param_1 + 0x50) = 0;
    *(undefined4 *)(param_1 + 0x54) = 0;
  }
  if ((*(uint *)(param_1 + 0x14) >> 0xc & 0xf) == 3) {
    *(int *)(param_1 + 0x40) = (int)((float)*(int *)(param_1 + 0x40) * DAT_008e7648);
  }
  return 1;
}

