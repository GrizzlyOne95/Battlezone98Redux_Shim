
undefined4 * __fastcall FUN_005eba50(undefined4 *param_1)

{
  int local_c;
  
  FUN_0045ca60();
  *param_1 = Tran05Mission::vftable;
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    param_1[local_c + 0x36] = 0;
  }
  return param_1;
}

