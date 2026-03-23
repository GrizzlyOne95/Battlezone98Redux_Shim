
undefined4 FUN_00434a80(undefined2 *param_1)

{
  if (DAT_0260c22c == DAT_0260c230) {
    *param_1 = 0;
  }
  else {
    *param_1 = *(undefined2 *)(&DAT_02cf4420 + DAT_0260c22c * 2);
    DAT_0260c22c = DAT_0260c22c + 1;
    if (DAT_0260c22c == 0x40) {
      DAT_0260c22c = 0;
    }
  }
  return 0;
}

