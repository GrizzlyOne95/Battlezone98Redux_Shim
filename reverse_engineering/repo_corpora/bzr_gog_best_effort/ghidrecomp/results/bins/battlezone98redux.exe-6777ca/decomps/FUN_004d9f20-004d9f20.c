
void FUN_004d9f20(void)

{
  uint local_8;
  
  for (local_8 = 0; local_8 < 0x1000; local_8 = local_8 + 1) {
    *(uint *)(&DAT_0260dc80 + local_8 * 0x400) = local_8;
    *(uint *)(&DAT_0260dc24 + local_8 * 0x400) = local_8 - 1;
  }
  DAT_02a0db20 = local_8 - 1;
  DAT_02a0db24 = local_8;
  return;
}

