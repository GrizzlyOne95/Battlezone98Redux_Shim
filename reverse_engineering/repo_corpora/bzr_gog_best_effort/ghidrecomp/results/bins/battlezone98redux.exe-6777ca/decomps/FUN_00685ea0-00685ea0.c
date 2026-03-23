
void FUN_00685ea0(int *param_1)

{
  if (*param_1 != 0) {
    (**(code **)(*(int *)*param_1 + 100))();
    (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x194))(*param_1);
    *param_1 = 0;
  }
  return;
}

