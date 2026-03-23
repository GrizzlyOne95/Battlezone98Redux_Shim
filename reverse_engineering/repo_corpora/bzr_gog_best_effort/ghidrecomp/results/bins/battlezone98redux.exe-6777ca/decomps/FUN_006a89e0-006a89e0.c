
void FUN_006a89e0(int param_1)

{
  if (param_1 != 0) {
    if ((*(int *)(param_1 + 0x28) != 0) && (*(int *)(*(int *)(param_1 + 0x28) + 0x14) == param_1)) {
      *(undefined4 *)(*(int *)(param_1 + 0x28) + 0x14) = 0;
    }
    *(undefined4 *)(param_1 + 0x28) = 0;
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  return;
}

