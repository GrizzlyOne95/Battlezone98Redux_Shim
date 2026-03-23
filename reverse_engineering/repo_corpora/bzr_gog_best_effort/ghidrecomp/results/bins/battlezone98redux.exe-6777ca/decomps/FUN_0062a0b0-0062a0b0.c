
void FUN_0062a0b0(int param_1)

{
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_14 = 0;
  local_8 = 0;
  while( true ) {
    if ((0x1ff < local_8) || (DAT_00920c58 <= local_14)) goto LAB_0062a130;
    if ((*(int *)(&DAT_02a17498 + local_8 * 0x20) != 0) &&
       ((local_14 = local_14 + 1, *(int *)(&DAT_02a1749c + local_8 * 0x20) != 0 &&
        (*(int *)(*(int *)(&DAT_02a1749c + local_8 * 0x20) + 0x3c) == param_1)))) break;
    local_8 = local_8 + 1;
  }
  FUN_0062a5d0(local_8);
LAB_0062a130:
  local_8 = 0;
  while( true ) {
    if (DAT_00920c5c <= local_8) {
      return;
    }
    if (*(int *)(*(int *)(&DAT_02a1b498 + local_8 * 4) + 0x3c) == param_1) break;
    local_8 = local_8 + 1;
  }
  for (local_c = 0; local_c < 0x200; local_c = local_c + 1) {
    if (*(int *)(&DAT_02a1749c + local_c * 0x20) == *(int *)(&DAT_02a1b498 + local_8 * 4)) {
      FUN_0062a5d0(local_c);
    }
  }
  *(undefined4 *)(*(int *)(&DAT_02a1b498 + local_8 * 4) + 0x3c) = 0;
  *(undefined4 *)(*(int *)(&DAT_02a1b498 + local_8 * 4) + 0x38) = 0;
  free(*(void **)(&DAT_02a1b498 + local_8 * 4));
  while (local_10 = local_8 + 1, local_10 < DAT_00920c5c) {
    *(undefined4 *)(&DAT_02a1b494 + local_10 * 4) = *(undefined4 *)(&DAT_02a1b498 + local_10 * 4);
    local_8 = local_10;
  }
  DAT_00920c5c = DAT_00920c5c + -1;
  *(undefined4 *)(&DAT_02a1b498 + DAT_00920c5c * 4) = 0;
  return;
}

