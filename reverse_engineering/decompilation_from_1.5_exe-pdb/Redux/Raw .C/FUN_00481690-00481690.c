
void FUN_00481690(int *param_1)

{
  int iVar1;
  int local_10;
  int local_c;
  int *local_8;
  
  if (param_1 == (int *)0x0) {
    local_8 = &DAT_0091739c;
  }
  else {
    local_8 = param_1;
  }
  if (*local_8 != 0) {
    for (local_c = 0; local_c < 0x800; local_c = local_c + 1) {
      local_10 = *(int *)(*local_8 + local_c * 4);
      while (local_10 != 0) {
        iVar1 = *(int *)(local_10 + 0x1c);
        FUN_00481880(local_8,local_10);
        local_10 = iVar1;
      }
    }
    local_8[1] = 0;
    local_8[3] = 0;
    local_8[4] = 0;
    free((void *)*local_8);
    *local_8 = 0;
  }
  return;
}

