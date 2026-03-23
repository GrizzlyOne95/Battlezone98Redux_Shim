
void __fastcall FUN_0081bfd0(int *param_1)

{
  char cVar1;
  char *local_20;
  char *local_1c;
  int *local_18;
  int *local_14;
  int local_c;
  
  *param_1 = 0x3e;
  for (local_c = 0; local_c < *param_1; local_c = local_c + 1) {
    local_1c = &DAT_008f17e8 + local_c * 0x204;
    local_14 = param_1 + local_c * 0x81 + 1;
    do {
      cVar1 = *local_1c;
      *(char *)local_14 = cVar1;
      local_1c = local_1c + 1;
      local_14 = (int *)((int)local_14 + 1);
    } while (cVar1 != '\0');
    local_20 = s_throttle_up_008f18e8 + local_c * 0x204;
    local_18 = param_1 + local_c * 0x81 + 0x41;
    do {
      cVar1 = *local_20;
      *(char *)local_18 = cVar1;
      local_20 = local_20 + 1;
      local_18 = (int *)((int)local_18 + 1);
    } while (cVar1 != '\0');
    param_1[local_c * 0x81 + 0x81] = *(int *)(&DAT_008f19e8 + local_c * 0x204);
  }
  return;
}

