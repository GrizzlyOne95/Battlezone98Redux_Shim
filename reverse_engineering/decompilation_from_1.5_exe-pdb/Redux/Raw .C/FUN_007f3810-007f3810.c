
void __thiscall FUN_007f3810(int *param_1,short *param_2)

{
  *param_1 = *param_1 + 1;
  if (*param_2 == 10) {
    param_1[1] = param_1[1] + 1;
    param_1[2] = 1;
  }
  else {
    param_1[2] = param_1[2] + 1;
  }
  return;
}

