
void __fastcall FUN_0045b9c0(undefined4 *param_1)

{
  if (param_1[2] != 0) {
    operator_delete__((void *)param_1[2]);
    param_1[2] = 0;
  }
  *param_1 = 0;
  param_1[1] = 0;
  return;
}

