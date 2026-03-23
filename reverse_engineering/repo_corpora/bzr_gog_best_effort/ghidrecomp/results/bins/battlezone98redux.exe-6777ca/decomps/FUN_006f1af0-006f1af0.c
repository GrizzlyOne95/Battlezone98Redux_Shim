
char * FUN_006f1af0(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *local_14;
  char *local_10;
  char *local_c;
  
  local_c = param_1;
  do {
    cVar1 = *local_c;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  local_10 = local_c + (1 - (int)(param_1 + 1));
  pcVar2 = (char *)FUN_0083d92c(local_10);
  local_14 = pcVar2;
  for (; local_10 != (char *)0x0; local_10 = local_10 + -1) {
    *local_14 = *param_1;
    local_14 = local_14 + 1;
    param_1 = param_1 + 1;
  }
  return pcVar2;
}

