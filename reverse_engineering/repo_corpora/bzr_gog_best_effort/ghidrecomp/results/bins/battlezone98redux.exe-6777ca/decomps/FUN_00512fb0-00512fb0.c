
undefined4 * __fastcall FUN_00512fb0(undefined4 *param_1)

{
  int local_c;
  
  FUN_0045ca60();
  *param_1 = Misn01Mission::vftable;
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    param_1[local_c + 0x22] = 0;
  }
  return param_1;
}

