
float10 FUN_006987d0(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,int param_6,undefined4 param_7,undefined4 *param_8,
                    int *param_9,undefined4 param_10)

{
  int iVar1;
  float10 fVar2;
  double local_14;
  
  if (*(char *)(*param_2 * 0x50 + param_6) == '(') {
    *param_2 = *param_2 + 1;
    iVar1 = FUN_006985c0(*param_2 * 0x50 + param_6);
    if (iVar1 != 0) {
      *param_2 = *param_2 + 1;
      if (*(char *)(*param_2 * 0x50 + param_6) != ')') {
        FUN_006978b0("Unmatched parenthesis in type-casting\n");
        return (float10)-1.0;
      }
      *param_2 = *param_2 + 1;
      fVar2 = (float10)FUN_006984f0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_9,param_10);
      local_14 = (double)fVar2;
      if (iVar1 == 1) {
        *param_8 = 1;
        local_14 = (double)(int)fVar2;
      }
      else {
        *param_8 = 0;
        *param_9 = (int)(double)*param_9;
      }
      return (float10)local_14;
    }
    fVar2 = (float10)FUN_00697940(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_9,param_10);
    if (*(char *)(*param_2 * 0x50 + param_6) != ')') {
      FUN_006978b0("Unmatched parentheses\n");
      return (float10)-1.0;
    }
    *param_2 = *param_2 + 1;
  }
  else {
    fVar2 = (float10)FUN_006989a0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_9,param_10);
  }
  local_14 = (double)fVar2;
  return (float10)local_14;
}

