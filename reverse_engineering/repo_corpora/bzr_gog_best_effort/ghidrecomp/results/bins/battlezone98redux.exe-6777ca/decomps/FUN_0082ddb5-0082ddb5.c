
undefined2 * FUN_0082ddb5(int param_1,uint param_2)

{
  if ((param_2 & 0x100) != 0) {
    if (*(int *)(*(int *)(param_1 + 8) + 8 + (param_2 & 0xfffffeff) * 0x10) == 4) {
      return (undefined2 *)(*(int *)(*(int *)(param_1 + 8) + (param_2 & 0xfffffeff) * 0x10) + 0x10);
    }
  }
  return &DAT_0088d940;
}

