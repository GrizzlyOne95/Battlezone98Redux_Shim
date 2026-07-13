
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0062c280(void)

{
  uint local_8;
  
  for (local_8 = 0; local_8 < 0x1401; local_8 = local_8 + 1) {
    FUN_0062c210(&DAT_02a1f570 + local_8 * 0xe4);
  }
  FUN_0062cc60();
  DAT_00920c7c = 0;
  _DAT_00920c70 = 0;
  DAT_00920c78 = 0;
  for (local_8 = 0; local_8 < 0x33; local_8 = local_8 + 1) {
    *(undefined4 *)(&DAT_02a1f4a0 + local_8 * 4) = 0;
    *(undefined4 *)(&DAT_02b3c658 + local_8 * 4) = 0;
  }
  DAT_00920c68 = 0;
  DAT_00920c74 = 0;
  return;
}

