
undefined4 FUN_0061d240(char *param_1)

{
  char cVar1;
  char *local_18;
  char *local_14;
  int local_10;
  char *local_c;
  
  local_c = param_1;
  do {
    cVar1 = *local_c;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  local_10 = (int)local_c - (int)(param_1 + 1);
  local_14 = &DAT_02cebcce;
  local_18 = param_1 + local_10 + -1;
  while( true ) {
    if (local_10 == 0) {
      return 1;
    }
    if (*local_14 != *local_18) break;
    local_10 = local_10 + -1;
    local_18 = local_18 + -1;
    local_14 = local_14 + -1;
  }
  return 0;
}

