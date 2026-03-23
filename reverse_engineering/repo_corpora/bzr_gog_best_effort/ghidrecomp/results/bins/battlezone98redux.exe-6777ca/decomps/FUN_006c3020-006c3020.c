
undefined4 * __thiscall FUN_006c3020(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  *(undefined1 *)(param_1 + 4) = *(undefined1 *)(param_2 + 4);
  param_1[6] = param_2[6];
  param_1[7] = param_2[7];
  param_1[8] = param_2[8];
  param_1[9] = param_2[9];
  FUN_006ca7f0(param_2 + 10);
  *(undefined1 *)(param_1 + 0xc) = *(undefined1 *)(param_2 + 0xc);
  *(undefined1 *)((int)param_1 + 0x31) = *(undefined1 *)((int)param_2 + 0x31);
  param_1[0xd] = param_2[0xd];
  FUN_006cafb0(param_2 + 0xe);
  param_1[0x10] = param_2[0x10];
  return param_1;
}

