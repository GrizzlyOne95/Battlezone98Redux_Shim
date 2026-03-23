
float10 FUN_00698220(undefined4 param_1,int *param_2,int param_3,undefined4 param_4,
                    undefined4 param_5,int param_6,undefined4 param_7,int *param_8,int *param_9,
                    undefined4 param_10)

{
  float10 fVar1;
  double local_24;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  char local_5;
  
  fVar1 = (float10)FUN_006983a0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,&local_10,
                                &local_c,param_10);
  local_24 = (double)fVar1;
  if (*param_2 <= param_3) {
    while ((local_5 = *(char *)(*param_2 * 0x50 + param_6), local_5 == '*' ||
           (*(char *)(*param_2 * 0x50 + param_6) == '/'))) {
      *param_2 = *param_2 + 1;
      fVar1 = (float10)FUN_006983a0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                    &local_1c,&local_18,param_10);
      if ((local_10 == 0) || (local_1c == 0)) {
        local_14 = 0;
      }
      else {
        local_14 = 1;
      }
      local_10 = local_14;
      if (local_14 == 0) {
        if (local_5 == '*') {
          local_24 = local_24 * (double)fVar1;
        }
        else {
          local_24 = local_24 / (double)fVar1;
        }
      }
      else if (local_5 == '*') {
        local_c = local_c * local_18;
      }
      else {
        local_c = local_c / local_18;
      }
    }
  }
  *param_8 = local_10;
  if (local_10 == 0) {
    *param_9 = (int)local_24;
  }
  else {
    *param_9 = local_c;
    local_24 = (double)local_c;
  }
  return (float10)local_24;
}

