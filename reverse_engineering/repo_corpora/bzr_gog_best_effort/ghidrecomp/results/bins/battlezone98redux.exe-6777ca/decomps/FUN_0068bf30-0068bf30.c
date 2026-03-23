
undefined4
FUN_0068bf30(int param_1,int param_2,int param_3,int param_4,int *param_5,int *param_6,int *param_7,
            int *param_8,float *param_9,float *param_10,float *param_11,float *param_12)

{
  undefined4 uVar1;
  
  if ((((param_3 < *param_5) || (*param_5 + *param_7 <= param_1)) || (param_4 < *param_6)) ||
     (*param_6 + *param_8 <= param_2)) {
    uVar1 = 0;
  }
  else {
    if (*param_5 < param_1) {
      *param_9 = (*param_11 - *param_9) * ((float)(param_1 - *param_5) / (float)*param_7) + *param_9
      ;
      *param_7 = *param_7 - (param_1 - *param_5);
      *param_5 = param_1;
    }
    if (param_3 < *param_5 + *param_7) {
      *param_11 = (*param_11 - *param_9) * ((float)(param_3 - *param_5) / (float)*param_7) +
                  *param_9;
      *param_7 = param_3 - *param_5;
    }
    if (*param_6 < param_2) {
      *param_10 = (*param_12 - *param_10) * ((float)(param_2 - *param_6) / (float)*param_8) +
                  *param_10;
      *param_8 = *param_8 - (param_2 - *param_6);
      *param_6 = param_2;
    }
    if (param_4 < *param_6 + *param_8) {
      *param_12 = (*param_12 - *param_10) * ((float)(param_4 - *param_6) / (float)*param_8) +
                  *param_10;
      *param_8 = param_4 - *param_6;
    }
    uVar1 = 1;
  }
  return uVar1;
}

