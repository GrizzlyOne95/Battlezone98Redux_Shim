
undefined4 FUN_00629fe0(void)

{
  int local_8;
  
  DAT_00920c58 = 0;
  DAT_00920c5c = 0;
  for (local_8 = 0; local_8 < 0x1000; local_8 = local_8 + 1) {
    if (*(int *)(&DAT_02a1b498 + local_8 * 4) != 0) {
      free(*(void **)(&DAT_02a1b498 + local_8 * 4));
    }
  }
  memset(&DAT_02a1b498,0,0x4000);
  memset(&DAT_02a17498,0,0x4000);
  return 0;
}

