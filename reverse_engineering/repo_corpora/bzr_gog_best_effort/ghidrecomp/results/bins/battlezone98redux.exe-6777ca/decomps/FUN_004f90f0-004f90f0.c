
float10 FUN_004f90f0(int param_1,float param_2)

{
  return (float10)(1.0 - ((param_2 - *(float *)(param_1 + 0x18)) /
                         ((*(float *)(param_1 + 0x20) - *(float *)(param_1 + 0x18)) + 1.0)) * 2.0);
}

