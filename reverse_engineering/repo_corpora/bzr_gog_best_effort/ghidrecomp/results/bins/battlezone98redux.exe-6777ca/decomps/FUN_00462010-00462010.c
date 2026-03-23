
float10 FUN_00462010(float *param_1,float *param_2)

{
  return (float10)((*param_1 - *param_2) * (*param_1 - *param_2) +
                  (param_1[2] - param_2[2]) * (param_1[2] - param_2[2]));
}

