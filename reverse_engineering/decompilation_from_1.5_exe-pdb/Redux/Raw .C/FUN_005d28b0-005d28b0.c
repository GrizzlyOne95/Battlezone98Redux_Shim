
int __thiscall FUN_005d28b0(int param_1,int param_2,int param_3)

{
  *(int *)(param_1 + 0x10) = param_2;
  *(int *)(param_1 + 0x14) = param_3;
  *(float *)(param_1 + 8) = (float)param_2 * 10.0 + DAT_009182f8 + 5.0;
  *(float *)(param_1 + 0xc) = (float)param_3 * 10.0 + DAT_009182fc + 5.0;
  *(undefined1 *)(param_1 + 0x19) = 0;
  *(undefined1 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0xbf800000;
  *(undefined4 *)(param_1 + 0x24) = 0x3f800000;
  return param_1;
}

