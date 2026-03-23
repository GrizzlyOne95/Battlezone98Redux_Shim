
void FUN_004c8310(void)

{
  if (DAT_02cc40b8 != 0) {
    FUN_00591d00();
    FUN_00591c00();
    FUN_0046a230();
    FUN_00591fa0();
  }
  DAT_009454a4 = 0;
  DAT_009454ac = 0;
  FUN_005b0920(0);
  FUN_00780800(0);
  *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) & 0xfffffffe;
  return;
}

