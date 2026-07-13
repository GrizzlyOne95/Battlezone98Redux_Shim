
void FUN_0062d3b0(int param_1,undefined4 param_2,undefined4 param_3)

{
  if (param_1 != 0) {
    *(short *)(param_1 + 0x12) = *(short *)(param_1 + 0x12) + (short)param_2;
    for (param_1 = *(int *)(param_1 + 0x80); param_1 != 0; param_1 = *(int *)(param_1 + 0x7c)) {
      FUN_0062d3b0(param_1,param_2,param_3);
    }
  }
  return;
}

