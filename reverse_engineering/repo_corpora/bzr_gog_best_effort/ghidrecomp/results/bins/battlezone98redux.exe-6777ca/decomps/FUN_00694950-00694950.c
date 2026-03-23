
void FUN_00694950(int *param_1)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 100; local_8 = local_8 + 1) {
    *(float *)(&DAT_02bff188 + local_8 * 4 + *param_1 * 400) =
         *(float *)(&DAT_02bfeff8 + local_8 * 4) * *(float *)(param_1[0x18] + 0x98 + local_8 * 4);
  }
  return;
}

