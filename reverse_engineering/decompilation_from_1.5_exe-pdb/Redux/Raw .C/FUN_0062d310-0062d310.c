
void FUN_0062d310(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    if (*(ushort *)(param_1 + 0x12) < 2) {
      FUN_0062d200(param_1,param_2);
    }
    else {
      *(short *)(param_1 + 0x12) = *(short *)(param_1 + 0x12) + -1;
      FUN_0062d2c0(*(undefined4 *)(param_1 + 0x80),param_2);
    }
  }
  return;
}

