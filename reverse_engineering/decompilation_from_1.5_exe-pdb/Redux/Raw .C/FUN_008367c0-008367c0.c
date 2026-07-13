
undefined4 __thiscall FUN_008367c0(undefined4 param_1,undefined4 param_2)

{
  float10 fVar1;
  undefined1 auVar2 [16];
  
  fVar1 = (float10)FUN_0082ba89(param_2,1,param_1,param_1);
  auVar2._8_8_ = 0;
  auVar2._0_8_ = (double)fVar1;
  auVar2 = sqrtpd(auVar2,auVar2);
  FUN_0082cd58(param_2,auVar2._0_8_);
  return 1;
}

