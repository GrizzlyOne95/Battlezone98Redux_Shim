
void FUN_0082db70(int param_1,int param_2)

{
  undefined *puVar1;
  
  if (*(char *)(param_2 + 6) == '\0') {
    *(int *)(param_1 + 0x10) = *(int *)(*(int *)(param_2 + 0x10) + 0x20) + 0x10;
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(*(int *)(param_2 + 0x10) + 0x3c);
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(*(int *)(param_2 + 0x10) + 0x40);
    puVar1 = &DAT_0089df3c;
    if (*(int *)(param_1 + 0x1c) != 0) {
      puVar1 = &DAT_0087d49c;
    }
    *(undefined **)(param_1 + 0xc) = puVar1;
  }
  else {
    *(undefined4 *)(param_1 + 0x1c) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x20) = 0xffffffff;
    *(undefined **)(param_1 + 0x10) = &DAT_0086ec20;
    *(undefined **)(param_1 + 0xc) = &DAT_00884fe0;
  }
  FUN_0082e741(param_1 + 0x24,*(undefined4 *)(param_1 + 0x10),0x3c);
  return;
}

