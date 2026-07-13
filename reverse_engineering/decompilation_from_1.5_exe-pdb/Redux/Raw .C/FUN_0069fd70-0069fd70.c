
void FUN_0069fd70(void)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (DAT_00920c9a != '\0') {
    for (local_8 = 1; local_8 < DAT_02ceb7fc; local_8 = local_8 + 1) {
      free(*(void **)(DAT_02ceb7e8 + 0xc + local_8 * 0x9c));
      free(*(void **)(DAT_02ceb7e8 + 0x10 + local_8 * 0x9c));
      free(*(void **)(DAT_02ceb7e8 + 0x14 + local_8 * 0x9c));
    }
    for (local_8 = 0; local_8 < DAT_02ceb800; local_8 = local_8 + 1) {
      local_c = *(void **)(DAT_02ceb7ec + local_8 * 4);
      if (local_c != (void *)0x0) {
        local_10 = *(void **)((int)local_c + 4);
        while (local_c != (void *)0x0) {
          free(local_c);
          local_c = local_10;
          if (local_10 != (void *)0x0) {
            local_10 = *(void **)((int)local_10 + 4);
          }
        }
      }
    }
    free((void *)DAT_02ceb7ec);
    free((void *)DAT_02ceb7e8);
    DAT_00920c9a = '\0';
  }
  return;
}

