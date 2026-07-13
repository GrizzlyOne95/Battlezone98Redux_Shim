
void FUN_00437a70(void)

{
  char local_28 [32];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_008e75f8 != -1) {
    if (DAT_00915580 != 0) {
      FUN_0043fa20(DAT_008e75f8);
    }
    FUN_0043fa60(DAT_008e75f8);
    sprintf(local_28,"%02d.ogg",DAT_008e75f4);
    FUN_00481990(local_28);
    DAT_008e75f8 = -1;
  }
  DAT_00915580 = 0;
  DAT_00915588 = 0;
  FUN_0083e885();
  return;
}

