
void FUN_004e3250(void)

{
  uint local_8;
  
  DAT_00917b04 = 0;
  for (local_8 = 0; local_8 < 0x400; local_8 = local_8 + 1) {
    *(undefined4 *)(&DAT_02a0db30 + local_8 * 0x18) = 0;
  }
  return;
}

