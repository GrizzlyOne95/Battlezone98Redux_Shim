
void __fastcall FUN_006a8fe0(int *param_1)

{
  if (*param_1 != 0) {
    free((void *)*param_1);
  }
  *param_1 = 0;
  param_1[3] = 0;
  return;
}

