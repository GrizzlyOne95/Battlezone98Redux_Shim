
void FUN_0083a00d(int param_1,undefined4 *param_2,undefined1 param_3)

{
  param_2[1] = 0xffffffff;
  *(undefined1 *)((int)param_2 + 10) = param_3;
  *(undefined1 *)(param_2 + 2) = *(undefined1 *)(param_1 + 0x32);
  *(undefined1 *)((int)param_2 + 9) = 0;
  *param_2 = *(undefined4 *)(param_1 + 0x14);
  *(undefined4 **)(param_1 + 0x14) = param_2;
  return;
}

