
float10 FUN_0082ba89(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  float10 fVar2;
  
  fVar2 = (float10)FUN_0082d3e1(param_1,param_2);
  if ((double)fVar2 == 0.0) {
    iVar1 = FUN_0082c9c5(param_1,param_2);
    if (iVar1 == 0) {
      FUN_0082c3e6(param_1,param_2,3);
    }
    fVar2 = (float10)(double)fVar2;
  }
  return fVar2;
}

