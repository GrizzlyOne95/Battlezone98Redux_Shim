
void FUN_007cf980(char *param_1)

{
  char cVar1;
  uint local_10;
  char *local_c;
  
  local_10 = 0;
  while( true ) {
    local_c = param_1;
    do {
      cVar1 = *local_c;
      local_c = local_c + 1;
    } while (cVar1 != '\0');
    if ((uint)((int)local_c - (int)(param_1 + 1)) <= local_10) break;
    FUN_007cfa70(param_1[local_10]);
    local_10 = local_10 + 1;
  }
  return;
}

