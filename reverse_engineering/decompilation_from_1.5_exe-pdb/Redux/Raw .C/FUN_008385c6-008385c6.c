
undefined4 FUN_008385c6(undefined4 param_1)

{
  byte bVar1;
  uint uVar2;
  
  uVar2 = FUN_00838733(param_1,1);
  bVar1 = FUN_00838733(param_1,2);
  FUN_0082cd58(param_1,(double)(int)(uVar2 << (bVar1 & 0x1f) | uVar2 >> 0x20 - (bVar1 & 0x1f)));
  return 1;
}

