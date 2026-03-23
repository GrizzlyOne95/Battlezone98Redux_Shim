
float10 FUN_004f90a0(int param_1,float param_2)

{
  return (float10)(((param_2 - *(float *)(param_1 + 0x14)) /
                   ((*(float *)(param_1 + 0x1c) - *(float *)(param_1 + 0x14)) + 1.0)) * 2.0 - 1.0);
}

