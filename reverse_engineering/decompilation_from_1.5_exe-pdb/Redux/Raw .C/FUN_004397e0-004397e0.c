
void __fastcall FUN_004397e0(int *param_1)

{
  FUN_00439b20();
  if (((char)param_1[0x20] == '\0') && (*param_1 != 0)) {
    operator_delete__((void *)*param_1);
    *param_1 = 0;
  }
  return;
}

