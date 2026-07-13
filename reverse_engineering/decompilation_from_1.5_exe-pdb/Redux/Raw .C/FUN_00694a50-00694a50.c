
void FUN_00694a50(int *param_1)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 100; local_8 = local_8 + 1) {
    *(undefined4 *)(&DAT_02bff188 + local_8 * 4 + *param_1 * 400) = 0x3f800000;
  }
  return;
}

