
float10 __thiscall FUN_0068a080(undefined4 param_1,double param_2)

{
  float10 fVar1;
  
  if (0.001 < param_2) {
    __libm_sse2_pow(param_1);
    fVar1 = (float10)(float)param_2;
  }
  else {
    fVar1 = (float10)0;
  }
  return fVar1;
}

