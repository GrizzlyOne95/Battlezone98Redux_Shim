
undefined * FUN_004e3750(void)

{
  int local_10;
  undefined *local_c;
  uint local_8;
  
  local_10 = 0;
  local_c = (undefined *)0x0;
  for (local_8 = 0; local_8 < 0x400; local_8 = local_8 + 1) {
    if (((*(int *)(&DAT_02a0db30 + local_8 * 0x18) != 0) &&
        (*(int *)(&DAT_02a0db34 + local_8 * 0x18) < 1)) &&
       (local_10 < *(int *)(&DAT_02a0db38 + local_8 * 0x18))) {
      local_10 = *(int *)(&DAT_02a0db38 + local_8 * 0x18);
      local_c = &DAT_02a0db28 + local_8 * 0x18;
    }
  }
  if (local_c != (undefined *)0x0) {
    free(*(void **)(local_c + 8));
    *(undefined4 *)(local_c + 8) = 0;
    DAT_00917b04 = DAT_00917b04 + -1;
  }
  return local_c;
}

