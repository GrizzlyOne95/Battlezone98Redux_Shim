
void FUN_0062e860(int param_1)

{
  if (param_1 != 0) {
    *(int *)(param_1 + 0x88) = param_1;
    DAT_02b3c72c = *(int *)(param_1 + 0x80);
    for (param_1 = DAT_02b3c72c; param_1 != 0; param_1 = *(int *)(param_1 + 0x7c)) {
      *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) | 0x40;
      *(undefined4 *)(param_1 + 0x84) = 0xb;
    }
  }
  return;
}

