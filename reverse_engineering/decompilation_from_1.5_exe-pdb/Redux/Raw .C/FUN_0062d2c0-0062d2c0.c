
void FUN_0062d2c0(int param_1,undefined4 param_2)

{
  for (; param_1 != 0; param_1 = *(int *)(param_1 + 0x7c)) {
    *(short *)(param_1 + 0x12) = *(short *)(param_1 + 0x12) + -1;
    if (*(int *)(param_1 + 0x80) != 0) {
      FUN_0062d2c0(*(undefined4 *)(param_1 + 0x80),param_2);
    }
  }
  return;
}

