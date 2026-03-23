
float10 FUN_005cbe30(float *param_1,float *param_2,float *param_3)

{
  return (float10)((*param_2 - *param_1) * (param_3[1] - param_1[1]) -
                  (param_2[1] - param_1[1]) * (*param_3 - *param_1));
}

