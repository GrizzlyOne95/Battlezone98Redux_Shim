
void __thiscall FUN_0067a780(int param_1,float param_2)

{
  float10 fVar1;
  
  *(float *)(param_1 + 0xb0) = param_2;
  fVar1 = (float10)log2f(param_2 + 1.1754944e-38);
  *(float *)(param_1 + 0x34) = (float)fVar1 * 32.0;
  if (*(byte *)(param_1 + 0xac) < 100) {
    fVar1 = (float10)FUN_00461fd0(*(undefined4 *)(param_1 + 0x34));
    *(float *)(param_1 + 0x34) = (float)fVar1;
  }
  return;
}

