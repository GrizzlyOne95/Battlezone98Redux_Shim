
float10 __thiscall FUN_004bacd0(int param_1,float param_2)

{
  if (param_2 < *(float *)(param_1 + 0x6c)) {
    *(float *)(param_1 + 0x6c) = param_2;
  }
  return (float10)(param_2 - *(float *)(param_1 + 0x6c));
}

