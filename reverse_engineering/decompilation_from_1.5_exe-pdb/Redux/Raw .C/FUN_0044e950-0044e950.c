
void __thiscall FUN_0044e950(int param_1,undefined4 *param_2)

{
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
  *param_2 = 0;
  param_2[3] = 0;
  *(undefined4 *)(param_2[1] + 8) = param_2[2];
  *(undefined4 *)(param_2[2] + 4) = param_2[1];
  return;
}

