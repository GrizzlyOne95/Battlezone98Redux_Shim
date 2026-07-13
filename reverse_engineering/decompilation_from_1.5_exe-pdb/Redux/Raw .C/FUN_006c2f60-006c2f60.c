
undefined4 * __thiscall FUN_006c2f60(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  param_1[4] = param_2[4];
  param_1[5] = param_2[5];
  param_1[6] = param_2[6];
  param_1[7] = param_2[7];
  FID_conflict_operator_(param_2 + 8);
  *(undefined1 *)(param_1 + 0xe) = *(undefined1 *)(param_2 + 0xe);
  *(undefined1 *)((int)param_1 + 0x39) = *(undefined1 *)((int)param_2 + 0x39);
  FUN_006ca7f0(param_2 + 0xf);
  FID_conflict_operator_(param_2 + 0x11);
  FUN_006caf60(param_2 + 0x17);
  *(undefined1 *)(param_1 + 0x19) = *(undefined1 *)(param_2 + 0x19);
  return param_1;
}

