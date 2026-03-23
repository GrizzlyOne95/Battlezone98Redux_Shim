
void FUN_006a2780(int param_1,int param_2)

{
  int local_1c;
  int local_18;
  int local_14;
  int *local_10;
  int local_c;
  char local_5;
  
  local_5 = *(char *)(DAT_009310a8 + param_2 * DAT_02c00ed8 + param_1);
  if (local_5 == -1) {
    local_14 = FUN_0067ac40();
    for (local_c = 0; local_c < local_14; local_c = local_c + 1) {
      local_10 = (int *)FUN_0067ac60(local_c);
      if ((param_1 == *local_10) && (local_10[1] == param_2)) {
        return;
      }
    }
    local_1c = param_1;
    local_18 = param_2;
    FUN_006a62f0(&local_1c);
  }
  return;
}

