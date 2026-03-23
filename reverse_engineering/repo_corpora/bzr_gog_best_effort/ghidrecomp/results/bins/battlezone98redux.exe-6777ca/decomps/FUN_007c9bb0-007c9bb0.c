
void __thiscall FUN_007c9bb0(int param_1,float param_2,char param_3,char param_4)

{
  FUN_007d14b0(*(undefined4 *)(param_1 + 0xec),*(undefined4 *)(param_1 + 0xf0),
               *(float *)(param_1 + 0x14c) * param_2,*(undefined4 *)(param_1 + 0xf8));
  (**(code **)(**(int **)(param_1 + 0x120) + 0x118))(0);
  FUN_007d2e20();
  (**(code **)(**(int **)(param_1 + 0x120) + 0x16c))();
  if ((param_3 != '\0') || (param_4 != '\0')) {
    FUN_007c9c80(param_4);
  }
  return;
}

