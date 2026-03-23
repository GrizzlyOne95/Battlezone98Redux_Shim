
void __thiscall FUN_007d3650(int param_1,undefined4 param_2,undefined4 param_3,undefined1 param_4)

{
  FUN_007d3480(param_2,param_3,param_4);
  if (*(int *)(param_1 + 0x120) != 0) {
    (**(code **)(**(int **)(param_1 + 0x120) + 0x118))(0);
    FUN_007d2e20();
    (**(code **)(**(int **)(param_1 + 0x120) + 0x16c))();
  }
  return;
}

