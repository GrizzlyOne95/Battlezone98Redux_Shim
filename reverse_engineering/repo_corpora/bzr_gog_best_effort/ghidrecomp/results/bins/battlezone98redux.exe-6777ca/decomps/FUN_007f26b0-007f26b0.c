
void __thiscall FUN_007f26b0(int *param_1,char *param_2)

{
  *param_1 = *param_1 + 1;
  if (*param_2 == '\n') {
    param_1[1] = param_1[1] + 1;
    param_1[2] = 1;
  }
  else {
    param_1[2] = param_1[2] + 1;
  }
  return;
}

