
bool FUN_00430830(char *param_1,void *param_2,char *param_3)

{
  char cVar1;
  char *local_c;
  
  local_c = param_1;
  do {
    cVar1 = *local_c;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  local_c = local_c + (1 - (int)(param_1 + 1));
  if (local_c <= param_3) {
    memcpy(param_2,param_1,(size_t)local_c);
  }
  return local_c <= param_3;
}

