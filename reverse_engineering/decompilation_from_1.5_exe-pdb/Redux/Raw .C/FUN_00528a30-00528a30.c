
undefined4 * __fastcall FUN_00528a30(undefined4 *param_1)

{
  int local_c;
  
  FUN_0045ca60();
  *param_1 = Misn07Mission::vftable;
  for (local_c = 0; local_c < 0x70; local_c = local_c + 1) {
    param_1[local_c + 0x147] = 0;
  }
  return param_1;
}

