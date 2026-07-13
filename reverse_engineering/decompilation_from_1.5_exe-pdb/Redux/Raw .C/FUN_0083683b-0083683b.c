
undefined4 __thiscall FUN_0083683b(undefined4 param_1,undefined4 param_2)

{
  float10 fVar1;
  double dVar2;
  undefined8 uVar3;
  
  uVar3 = CONCAT44(1,param_2);
  fVar1 = (float10)FUN_0082ba89(param_2,1,param_1,param_1);
  dVar2 = (double)fVar1;
  __libm_sse2_log(uVar3,dVar2);
  FUN_0082cd58(param_2,dVar2);
  return 1;
}

