
undefined4 FUN_00836920(undefined4 param_1)

{
  float10 fVar1;
  double dVar2;
  int *_Y;
  int local_8;
  
  _Y = &local_8;
  fVar1 = (float10)FUN_0082ba89(param_1,1);
  dVar2 = frexp((double)fVar1,_Y);
  FUN_0082cd58(param_1,SUB84(dVar2,0),(int)((ulonglong)dVar2 >> 0x20));
  FUN_0082ccca(param_1,local_8);
  return 2;
}

