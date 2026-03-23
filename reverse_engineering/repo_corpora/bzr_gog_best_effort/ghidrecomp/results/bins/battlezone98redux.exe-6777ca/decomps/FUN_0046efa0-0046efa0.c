
void FUN_0046efa0(void)

{
  char cVar1;
  int *piVar2;
  int local_10;
  int local_c;
  int local_8;
  
  for (local_8 = 0; local_8 < 2; local_8 = local_8 + 1) {
    for (local_c = 0; local_c < 0x10; local_c = local_c + 1) {
      if (*(int *)(&DAT_0260d640 + local_c * 4 + local_8 * 0x40) != 0) {
        operator_delete__(*(void **)(&DAT_0260d640 + local_c * 4 + local_8 * 0x40));
        *(undefined4 *)(&DAT_0260d640 + local_c * 4 + local_8 * 0x40) = 0;
      }
    }
  }
  for (local_10 = 0; local_10 < 0x10; local_10 = local_10 + 1) {
    if (*(int *)(&DAT_0260d6d8 + local_10 * 4) != 0) {
      operator_delete(*(void **)(&DAT_0260d6d8 + local_10 * 4));
      *(undefined4 *)(&DAT_0260d6d8 + local_10 * 4) = 0;
    }
  }
  while (cVar1 = FUN_0042d8f0(), cVar1 == '\0') {
    piVar2 = (int *)FUN_0045e220();
    if (*piVar2 != 0) {
      FUN_0046f0c0(1);
    }
  }
  return;
}

