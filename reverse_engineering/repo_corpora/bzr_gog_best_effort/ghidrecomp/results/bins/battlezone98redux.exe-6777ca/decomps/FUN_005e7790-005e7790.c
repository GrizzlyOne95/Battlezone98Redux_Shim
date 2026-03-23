
undefined4 * __fastcall FUN_005e7790(undefined4 *param_1)

{
  int local_c;
  
  FUN_0045ca60();
  *param_1 = Tran02Mission::vftable;
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    param_1[local_c + 0x23] = 0;
  }
  return param_1;
}

