
float10 FUN_004c1050(float param_1,float param_2,float param_3)

{
  if ((0.0 <= param_3) && (param_3 <= 1.0)) {
    param_2 = (param_2 - param_1) * param_3 + param_1;
  }
  return (float10)param_2;
}

