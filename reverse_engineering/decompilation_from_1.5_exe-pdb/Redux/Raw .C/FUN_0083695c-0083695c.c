
undefined4 FUN_0083695c(undefined4 param_1)

{
  int _Y;
  float10 fVar1;
  double dVar2;
  
  _Y = FUN_0082ba1c(param_1,2);
  fVar1 = (float10)FUN_0082ba89(param_1,1);
  dVar2 = ldexp((double)fVar1,_Y);
  FUN_0082cd58(param_1,SUB84(dVar2,0),(int)((ulonglong)dVar2 >> 0x20));
  return 1;
}

