
float10 FUN_006989a0(undefined4 param_1,int *param_2,undefined4 param_3,int param_4,int param_5,
                    int param_6,int param_7,undefined4 *param_8,int *param_9,undefined4 *param_10)

{
  int iVar1;
  float10 fVar2;
  double local_10;
  int local_8;
  
  local_10 = 0.0;
  local_8 = -1;
  if (*(int *)(param_7 + *param_2 * 4) == 3) {
    *param_9 = (int)*(double *)(param_5 + *param_2 * 8);
    local_10 = *(double *)(param_5 + *param_2 * 8);
    *param_8 = 0;
  }
  else if (*(int *)(param_7 + *param_2 * 4) == 1) {
    *param_9 = *(int *)(param_4 + *param_2 * 4);
    local_10 = (double)*(int *)(param_4 + *param_2 * 4);
    *param_8 = 1;
  }
  else if (*(int *)(param_7 + *param_2 * 4) == 4) {
    fVar2 = (float10)FUN_0069cd40(param_1,*param_2 * 0x50 + param_6,&local_8);
    local_10 = (double)fVar2;
    if (local_8 == -1) {
      fVar2 = (float10)FUN_0069cc40(param_1,*param_2 * 0x50 + param_6,&local_8);
      local_10 = (double)fVar2;
      if (local_8 == -1) {
        iVar1 = FUN_0069cb20(param_1,*param_2 * 0x50 + param_6,&local_8);
        *param_9 = iVar1;
        if (local_8 == -1) {
          *param_10 = 0xffffffff;
          FUN_006978b0("Variable not declared");
          return (float10)-1.0;
        }
        *param_8 = 1;
        local_10 = (double)*param_9;
      }
      else {
        *param_8 = 0;
        *param_9 = (int)fVar2;
      }
    }
    else {
      *param_8 = 0;
      *param_9 = (int)fVar2;
    }
  }
  *param_2 = *param_2 + 1;
  return (float10)local_10;
}

