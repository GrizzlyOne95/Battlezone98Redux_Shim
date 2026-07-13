
void FUN_0043cf50(int param_1)

{
  if (*(int *)(param_1 + 0x7c) != 0) {
    if (*(int *)(param_1 + 0x80) != 0) {
      (**(code **)(**(int **)(param_1 + 0x80) + 8))(*(undefined4 *)(param_1 + 0x80));
    }
    (**(code **)(**(int **)(param_1 + 0x7c) + 8))(*(undefined4 *)(param_1 + 0x7c));
    *(undefined4 *)(param_1 + 0x7c) = 0;
    *(undefined4 *)(param_1 + 0x80) = 0;
  }
  return;
}

