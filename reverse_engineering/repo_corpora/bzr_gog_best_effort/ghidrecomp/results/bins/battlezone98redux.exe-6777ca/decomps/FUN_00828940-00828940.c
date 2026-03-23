
char * FUN_00828940(char *param_1,char *param_2)

{
  char cVar1;
  char *local_10;
  char *local_c;
  
  if (param_1 == (char *)0x0) {
    param_2 = (char *)0x0;
  }
  else {
    local_10 = param_1;
    local_c = param_2;
    do {
      cVar1 = *local_10;
      *local_c = cVar1;
      local_10 = local_10 + 1;
      local_c = local_c + 1;
    } while (cVar1 != '\0');
  }
  return param_2;
}

