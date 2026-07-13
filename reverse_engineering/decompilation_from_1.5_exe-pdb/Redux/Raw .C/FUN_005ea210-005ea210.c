
undefined4 * __fastcall FUN_005ea210(undefined4 *param_1)

{
  int local_c;
  
  FUN_0045ca60();
  *param_1 = Tran04Mission::vftable;
  for (local_c = 0; local_c < 8; local_c = local_c + 1) {
    param_1[local_c + 0x27] = 0;
  }
  return param_1;
}

