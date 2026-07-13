
void __thiscall FUN_007d3310(int param_1,undefined1 param_2)

{
  if (*(int *)(param_1 + 0x120) != 0) {
    (**(code **)(**(int **)(param_1 + 0x120) + 0x84))(param_2);
  }
  *(undefined1 *)(param_1 + 0xe9) = param_2;
  return;
}

