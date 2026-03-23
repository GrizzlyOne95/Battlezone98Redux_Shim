
int FUN_00416290(char *param_1)

{
  char cVar1;
  int local_10;
  char *local_c;
  
  if (*param_1 == '\0') {
    local_10 = 0;
  }
  else {
    local_c = param_1;
    do {
      cVar1 = *local_c;
      local_c = local_c + 1;
    } while (cVar1 != '\0');
    local_10 = (int)local_c - (int)(param_1 + 1);
  }
  return local_10;
}

