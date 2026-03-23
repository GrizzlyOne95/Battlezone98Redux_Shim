
float10 FUN_006984f0(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,int param_6,undefined4 param_7,int *param_8,int *param_9,
                    undefined4 param_10)

{
  bool bVar1;
  float10 fVar2;
  undefined8 local_10;
  
  bVar1 = *(char *)(*param_2 * 0x50 + param_6) == '-';
  if (bVar1) {
    *param_2 = *param_2 + 1;
  }
  fVar2 = (float10)FUN_006987d0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_9,param_10);
  local_10 = (double)fVar2;
  if (*param_8 == 0) {
    if (bVar1) {
      local_10 = local_10 * -1.0;
    }
    *param_9 = (int)local_10;
  }
  else {
    if (bVar1) {
      *param_9 = -*param_9;
    }
    local_10 = (double)*param_9;
  }
  return (float10)local_10;
}

