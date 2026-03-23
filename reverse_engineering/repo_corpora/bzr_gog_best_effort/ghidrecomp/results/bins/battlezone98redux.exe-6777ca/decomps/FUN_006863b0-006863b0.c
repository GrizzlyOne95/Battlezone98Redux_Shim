
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006863b0(int param_1,int *param_2)

{
  float fVar1;
  
  if (param_2 != (int *)0x0) {
    fVar1 = *(float *)(param_1 + 0x10) * 0.9;
    (**(code **)(*param_2 + 0x2c))
              ((float)*(double *)(param_1 + 0x160) - _DAT_025f8e4c,
               (float)*(double *)(param_1 + 0x168),
               (float)-*(double *)(param_1 + 0x170) - _DAT_025f8e54,fVar1);
    (**(code **)(*param_2 + 0x38))(fVar1,fVar1,fVar1);
  }
  return;
}

