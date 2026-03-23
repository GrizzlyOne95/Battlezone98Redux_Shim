
float10 FUN_006978d0(undefined4 param_1,int param_2,int param_3,undefined4 param_4,
                    undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                    undefined4 param_9,undefined4 *param_10)

{
  float10 fVar1;
  double local_c;
  
  local_c = 0.0;
  *param_10 = 0;
  if (param_3 < param_2) {
    *param_10 = 0xffffffff;
  }
  else {
    fVar1 = (float10)FUN_00697940(param_1,&param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_9,param_10);
    local_c = (double)fVar1;
  }
  return (float10)local_c;
}

