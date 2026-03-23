
undefined4 __thiscall FUN_008366a4(undefined4 param_1,undefined4 param_2)

{
  double dVar1;
  float10 fVar2;
  double dVar3;
  double dVar4;
  
  fVar2 = (float10)FUN_0082ba89(param_2,1,param_1,param_1);
  dVar1 = (double)fVar2;
  dVar4 = (double)((ulonglong)dVar1 & 0x8000000000000000);
  dVar3 = (double)(-(ulonglong)((double)((ulonglong)dVar1 ^ (ulonglong)dVar4) < 4503599627370496.0)
                   & 0x4330000000000000 | (ulonglong)dVar4);
  dVar3 = (dVar1 + dVar3) - dVar3;
  FUN_0082cd58(param_2,dVar3 - (double)(-(ulonglong)(dVar4 < dVar3 - dVar1) & 0x3ff0000000000000));
  return 1;
}

