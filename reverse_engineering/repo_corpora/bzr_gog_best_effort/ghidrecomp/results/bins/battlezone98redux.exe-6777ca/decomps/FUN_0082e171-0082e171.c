
undefined4 FUN_0082e171(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  for (uVar1 = *(uint *)(param_1 + 0x14); (0 < param_2 && (*(uint *)(param_1 + 0x28) < uVar1));
      uVar1 = uVar1 - 0x18) {
    param_2 = param_2 + -1;
    if (*(char *)(**(int **)(uVar1 + 4) + 6) == '\0') {
      param_2 = param_2 - *(int *)(uVar1 + 0x14);
    }
  }
  if (param_2 == 0) {
    if (*(uint *)(param_1 + 0x28) < uVar1) {
      *(int *)(param_3 + 0x60) = (int)(uVar1 - *(uint *)(param_1 + 0x28)) / 0x18;
      return 1;
    }
  }
  else if (param_2 < 0) {
    *(undefined4 *)(param_3 + 0x60) = 0;
    return 1;
  }
  return 0;
}

