
void FUN_007c6920(void)

{
  undefined4 uVar1;
  bool bVar2;
  
  bVar2 = 0xfffffffe < DAT_009455f0;
  DAT_009455f0 = DAT_009455f0 + 1;
  DAT_009455f4 = DAT_009455f4 + (uint)bVar2;
  uVar1 = __aullshr();
  FUN_004346d0(uVar1,DAT_009455f0);
  return;
}

