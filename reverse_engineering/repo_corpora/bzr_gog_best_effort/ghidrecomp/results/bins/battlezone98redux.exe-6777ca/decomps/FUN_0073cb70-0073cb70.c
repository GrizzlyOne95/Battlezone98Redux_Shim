
undefined4 * __thiscall FUN_0073cb70(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  FID_conflict_operator_(param_2 + 1);
  *(undefined1 *)(param_1 + 7) = *(undefined1 *)(param_2 + 7);
  param_1[8] = param_2[8];
  FID_conflict_operator_(param_2 + 9);
  *(undefined1 *)(param_1 + 0xf) = *(undefined1 *)(param_2 + 0xf);
  *(undefined1 *)((int)param_1 + 0x3d) = *(undefined1 *)((int)param_2 + 0x3d);
  *(undefined1 *)((int)param_1 + 0x3e) = *(undefined1 *)((int)param_2 + 0x3e);
  param_1[0x10] = param_2[0x10];
  param_1[0x11] = param_2[0x11];
  param_1[0x12] = param_2[0x12];
  *(undefined1 *)(param_1 + 0x13) = *(undefined1 *)(param_2 + 0x13);
  param_1[0x14] = param_2[0x14];
  *(undefined1 *)(param_1 + 0x15) = *(undefined1 *)(param_2 + 0x15);
  return param_1;
}

