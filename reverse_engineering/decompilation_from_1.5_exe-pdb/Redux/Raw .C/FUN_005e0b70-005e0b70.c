
void FUN_005e0b70(void)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    operator_delete(*(void **)(&DAT_00918370 + local_8 * 4));
    *(undefined4 *)(&DAT_00918370 + local_8 * 4) = 0;
  }
  return;
}

