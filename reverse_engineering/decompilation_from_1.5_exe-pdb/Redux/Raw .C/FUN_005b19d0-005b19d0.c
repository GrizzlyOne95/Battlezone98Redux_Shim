
void __thiscall FUN_005b19d0(int param_1,float param_2)

{
  if (0.0 < *(float *)(*(int *)(param_1 + 8) + 0x278)) {
    FUN_004c0c40(*(undefined4 *)(param_1 + 0x38));
  }
  *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) - *(float *)(param_1 + 0x3c) * param_2;
  FUN_004ca430(param_2);
  return;
}

