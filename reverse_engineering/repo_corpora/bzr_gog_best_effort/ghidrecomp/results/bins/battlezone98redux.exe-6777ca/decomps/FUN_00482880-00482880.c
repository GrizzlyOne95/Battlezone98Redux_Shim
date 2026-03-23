
void FUN_00482880(void)

{
  undefined1 auStack_17c [180];
  undefined4 uStack_c8;
  undefined1 *local_c4;
  undefined1 local_c0 [184];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uStack_c8 = 0x482898;
  FUN_00482e20();
  uStack_c8 = 0x48289d;
  FUN_007d4500();
  uStack_c8 = 0x4828a8;
  FUN_00482690();
  local_c0[0] = 0;
  local_c4 = auStack_17c;
  FUN_004828f0(local_c0);
  FUN_00489dc0();
  uStack_c8 = 0x4828df;
  FUN_00482800();
  uStack_c8 = 0x4828e9;
  FUN_0083e885();
  return;
}

