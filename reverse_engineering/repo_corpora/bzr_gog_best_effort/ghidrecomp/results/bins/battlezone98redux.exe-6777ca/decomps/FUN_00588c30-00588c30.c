
void FUN_00588c30(char *param_1,char *param_2,char *param_3,uint param_4,uint param_5)

{
  char cVar1;
  char *pcVar2;
  char *local_14;
  uint local_c;
  
  pcVar2 = strrchr(param_1,0x2e);
  if (pcVar2 == (char *)0x0) {
    strncpy(param_2,param_1,param_4);
    param_2[param_4 - 1] = '\0';
    strncpy(param_3,param_1,param_5);
    param_3[param_5 - 1] = '\0';
  }
  else {
    local_c = (int)pcVar2 - (int)param_1;
    if (param_4 < local_c) {
      local_c = param_4;
    }
    memcpy(param_2,param_1,local_c);
    param_2[local_c] = '\0';
    param_2[param_4 - 1] = '\0';
    local_14 = pcVar2 + 1;
    do {
      cVar1 = *local_14;
      local_14 = local_14 + 1;
    } while (cVar1 != '\0');
    local_c = (int)local_14 - (int)(pcVar2 + 2);
    if (param_5 < local_c) {
      local_c = param_5;
    }
    memcpy(param_3,pcVar2 + 1,local_c);
    param_3[local_c] = '\0';
    param_3[param_5 - 1] = '\0';
  }
  return;
}

