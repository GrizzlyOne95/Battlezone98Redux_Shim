
undefined4 FUN_005cbe90(int param_1,int param_2,int param_3)

{
  float10 fVar1;
  
  if (*(float *)(param_3 + 4) < *(float *)(param_1 + 4)) {
    if ((*(float *)(param_2 + 4) <= *(float *)(param_3 + 4)) &&
       (fVar1 = (float10)FUN_005cbe30(param_1,param_2,param_3), (float)fVar1 < 0.0)) {
      return 0xffffffff;
    }
  }
  else if ((*(float *)(param_3 + 4) <= *(float *)(param_2 + 4) &&
            *(float *)(param_2 + 4) != *(float *)(param_3 + 4)) &&
          (fVar1 = (float10)FUN_005cbe30(param_1,param_2,param_3), 0.0 < (float)fVar1)) {
    return 1;
  }
  return 0;
}

