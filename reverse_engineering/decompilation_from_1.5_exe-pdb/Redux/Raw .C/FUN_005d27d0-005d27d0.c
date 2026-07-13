
float10 FUN_005d27d0(float *param_1,float *param_2)

{
  return (float10)((*param_1 - *param_2) * (*param_1 - *param_2) +
                  (param_1[1] - param_2[1]) * (param_1[1] - param_2[1]));
}

