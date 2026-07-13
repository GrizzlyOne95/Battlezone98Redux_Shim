
void FUN_0062cf50(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    if (DAT_00920c80 == 0) {
      *(short *)(param_1 + 0x12) = *(short *)(param_1 + 0x12) + 1;
      DAT_00920c80 = 1;
      FUN_0062cf50(*(undefined4 *)(param_1 + 0x80),param_2);
      DAT_00920c80 = 0;
    }
    else {
      for (; param_1 != 0; param_1 = *(int *)(param_1 + 0x7c)) {
        *(short *)(param_1 + 0x12) = *(short *)(param_1 + 0x12) + 1;
        FUN_0062cf50(*(undefined4 *)(param_1 + 0x80),param_2);
      }
    }
  }
  return;
}

