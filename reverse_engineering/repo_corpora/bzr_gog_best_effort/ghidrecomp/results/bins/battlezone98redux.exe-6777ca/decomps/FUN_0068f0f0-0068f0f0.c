
void FUN_0068f0f0(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
                 undefined4 *param_5)

{
  if ((param_1 < 0) || (DAT_00920f00 <= param_1)) {
    param_1 = 0;
  }
  param_1 = param_1 * 0x24;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = *(undefined4 *)(&DAT_025f8f48 + param_1);
  }
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = *(undefined4 *)(&DAT_025f8f4c + param_1);
  }
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = *(undefined4 *)(&DAT_025f8f50 + param_1);
  }
  if (param_5 != (undefined4 *)0x0) {
    *param_5 = *(undefined4 *)(&DAT_025f8f54 + param_1);
  }
  return;
}

