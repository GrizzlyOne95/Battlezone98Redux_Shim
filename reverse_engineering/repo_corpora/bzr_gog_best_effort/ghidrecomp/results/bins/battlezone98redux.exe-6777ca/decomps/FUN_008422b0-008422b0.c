
void FUN_008422b0(undefined4 *param_1,undefined4 *param_2)

{
  if ((HANDLE)*param_2 != (HANDLE)0x0) {
    FindClose((HANDLE)*param_2);
    *param_2 = 0;
  }
  *param_1 = DAT_009150d8;
  param_1[1] = DAT_009150dc;
  return;
}

