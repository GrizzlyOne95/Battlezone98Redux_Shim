
float10 FUN_007f5ca0(undefined4 param_1,undefined4 param_2,double *param_3)

{
  float10 fVar1;
  double dVar2;
  
  fVar1 = (float10)FUN_007f5020();
  dVar2 = floor(*param_3 / (double)fVar1);
  return (float10)dVar2;
}

