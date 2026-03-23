
void FUN_006899e0(void)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
    *(int *)(&DAT_008ed6b0 + local_8 * 4) = (local_8 + 1) * 0x20;
  }
  return;
}

