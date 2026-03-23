
void FUN_004e36f0(void)

{
  uint local_8;
  
  for (local_8 = 0; local_8 < 0x400; local_8 = local_8 + 1) {
    if (*(int *)(&DAT_02a0db30 + local_8 * 0x18) != 0) {
      free(*(void **)(&DAT_02a0db30 + local_8 * 0x18));
      *(undefined4 *)(&DAT_02a0db30 + local_8 * 0x18) = 0;
    }
  }
  return;
}

