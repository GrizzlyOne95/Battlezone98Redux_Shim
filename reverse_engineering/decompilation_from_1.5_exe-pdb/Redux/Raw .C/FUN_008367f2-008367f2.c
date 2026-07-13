
undefined4 FUN_008367f2(undefined4 param_1)

{
  float10 fVar1;
  double dVar2;
  undefined8 uVar3;
  double dVar4;
  double dVar5;
  
  uVar3 = CONCAT44(1,param_1);
  fVar1 = (float10)FUN_0082ba89(param_1,1);
  dVar2 = (double)fVar1;
  fVar1 = (float10)FUN_0082ba89(param_1,2,uVar3,dVar2);
  dVar5 = (double)fVar1;
  dVar4 = dVar2;
  __libm_sse2_pow();
  FUN_0082cd58(param_1,dVar2,dVar4,dVar5);
  return 1;
}

