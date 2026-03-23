
undefined4 FUN_0083864a(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00838733(param_1,1);
  FUN_0082cd58(param_1,(double)(int)((uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8 |
                                    (uVar1 & 0xff00 | uVar1 << 0x10) << 8));
  return 1;
}

