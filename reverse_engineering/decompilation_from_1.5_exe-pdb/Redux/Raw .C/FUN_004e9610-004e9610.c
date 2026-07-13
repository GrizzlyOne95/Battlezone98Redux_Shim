
float10 FUN_004e9610(float param_1)

{
  float10 fVar1;
  
  if (param_1 < 0.5) {
    if (param_1 < 0.25) {
      if (param_1 < 0.0) {
        fVar1 = (float10)0;
      }
      else {
        fVar1 = (float10)(param_1 + 0.5);
      }
    }
    else {
      fVar1 = (float10)(param_1 * 0.5 + 0.75);
    }
  }
  else {
    fVar1 = (float10)1;
  }
  return fVar1;
}

