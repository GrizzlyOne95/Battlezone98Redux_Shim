
undefined4 * __fastcall FUN_004b18a0(undefined4 *param_1)

{
  int local_c;
  
  FUN_0045ca60();
  *param_1 = DemoMission::vftable;
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    param_1[local_c + 0x33] = 0;
  }
  return param_1;
}

