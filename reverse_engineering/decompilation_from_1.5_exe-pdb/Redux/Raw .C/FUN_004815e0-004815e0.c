
void FUN_004815e0(int *param_1)

{
  int local_10;
  int *local_c;
  int local_8;
  
  if (param_1 == (int *)0x0) {
    local_c = &DAT_0091739c;
  }
  else {
    local_c = param_1;
  }
  local_c[3] = 0;
  local_c[4] = 0;
  for (local_10 = 0; local_10 < 0x800; local_10 = local_10 + 1) {
    for (local_8 = *(int *)(*local_c + local_10 * 4); local_8 != 0;
        local_8 = *(int *)(local_8 + 0x1c)) {
      if (*(short *)(local_8 + 0x14) == 0) {
        *(undefined2 *)(local_8 + 0x14) = 1;
        FUN_004814c0(local_8);
      }
    }
  }
  return;
}

