
void FUN_006904f0(void)

{
  int local_c;
  int local_8;
  
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    for (local_c = 0; local_c < 3; local_c = local_c + 1) {
      if (*(int *)(&DAT_02bfdcb0 + local_c * 4 + local_8 * 0x10) != 0) {
        free(*(void **)(&DAT_02bfdcb0 + local_c * 4 + local_8 * 0x10));
        *(undefined4 *)(&DAT_02bfdcb0 + local_c * 4 + local_8 * 0x10) = 0;
      }
    }
  }
  return;
}

