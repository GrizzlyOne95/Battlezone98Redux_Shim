
float10 FUN_006983a0(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,int param_6,undefined4 param_7,int *param_8,int *param_9,
                    undefined4 param_10)

{
  float10 fVar1;
  float10 fVar2;
  double local_28;
  undefined1 local_20 [4];
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  fVar1 = (float10)FUN_006984f0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,&local_8,
                                &local_14,param_10);
  local_28 = (double)fVar1;
  if (*(char *)(*param_2 * 0x50 + param_6) == '^') {
    *param_2 = *param_2 + 1;
    fVar2 = (float10)FUN_006983a0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,&local_1c,
                                  local_20,param_10);
    if ((local_8 == 0) || (local_1c == 0)) {
      local_18 = 0;
    }
    else {
      local_18 = 1;
    }
    local_8 = local_18;
    if (local_18 == 0) {
      __libm_sse2_pow();
    }
    else {
      local_10 = 1;
      for (local_c = 0; (double)local_c < (double)fVar2; local_c = local_c + 1) {
        local_10 = (int)fVar1 * local_10;
      }
      local_14 = local_10;
    }
  }
  *param_8 = local_8;
  if (local_8 == 0) {
    *param_9 = (int)local_28;
  }
  else {
    *param_9 = local_14;
    local_28 = (double)local_14;
  }
  return (float10)local_28;
}

