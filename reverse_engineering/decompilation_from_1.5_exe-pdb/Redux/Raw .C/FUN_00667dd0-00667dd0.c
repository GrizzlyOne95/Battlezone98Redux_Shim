
undefined4 * __thiscall FUN_00667dd0(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  FID_conflict_operator_(param_2 + 1);
  FID_conflict_operator_(param_2 + 7);
  FID_conflict_operator_(param_2 + 0xd);
  param_1[0x13] = param_2[0x13];
  param_1[0x14] = param_2[0x14];
  return param_1;
}

