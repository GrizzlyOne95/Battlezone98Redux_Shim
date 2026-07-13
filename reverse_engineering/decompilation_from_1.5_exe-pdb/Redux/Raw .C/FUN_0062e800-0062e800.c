
float10 FUN_0062e800(float param_1,float param_2)

{
  float10 fVar1;
  
  fVar1 = (float10)FUN_0062e7d0(param_1,param_2);
  param_1 = (float)fVar1;
  if (param_1 < 0.0) {
    param_1 = param_1 + param_2;
  }
  return (float10)param_1;
}

