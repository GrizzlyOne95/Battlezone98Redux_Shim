
void FUN_0043b6b0(int param_1)

{
  if (param_1 != 0) {
    FUN_0043bf80(param_1);
    FUN_0043cf50(param_1);
    if (*(int *)(param_1 + 0x4c) != 0) {
      if ((*(uint *)(param_1 + 0x70) & 0x200) == 0) {
        FUN_00481990(param_1 + 4);
      }
      *(undefined4 *)(param_1 + 0x4c) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x50) = 0;
    }
  }
  return;
}

