
undefined4 FUN_0083676e(undefined4 param_1)

{
  float10 fVar1;
  double dVar2;
  double *_Y;
  double local_c;
  
  _Y = &local_c;
  fVar1 = (float10)FUN_0082ba89(param_1,1);
  dVar2 = modf((double)fVar1,_Y);
  FUN_0082cd58(param_1,SUB84(local_c,0),(int)((ulonglong)local_c >> 0x20),dVar2);
  FUN_0082cd58(param_1,SUB84(dVar2,0),(int)((ulonglong)dVar2 >> 0x20));
  return 2;
}

