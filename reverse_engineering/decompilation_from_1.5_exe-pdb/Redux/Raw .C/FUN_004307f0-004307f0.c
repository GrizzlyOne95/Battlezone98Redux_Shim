
char * FUN_004307f0(char *param_1)

{
  char cVar1;
  char *local_c;
  
  local_c = param_1;
  do {
    cVar1 = *local_c;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  return local_c + (1 - (int)(param_1 + 1));
}

