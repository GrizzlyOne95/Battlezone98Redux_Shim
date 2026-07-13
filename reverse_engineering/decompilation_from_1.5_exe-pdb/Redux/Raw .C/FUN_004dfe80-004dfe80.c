
void __thiscall FUN_004dfe80(int param_1,char *param_2,int *param_3)

{
  char cVar1;
  char *pcVar2;
  char *local_1c;
  char *local_14;
  char *local_10;
  char *local_c;
  
  if (*(int *)(param_1 + 0xe8) == 0) {
    *param_2 = '\0';
    local_c = param_2 + 1;
    *param_3 = *param_3 + 1;
  }
  else {
    local_10 = *(char **)(param_1 + 0xe8);
    pcVar2 = local_10 + 1;
    do {
      cVar1 = *local_10;
      local_10 = local_10 + 1;
    } while (cVar1 != '\0');
    *param_3 = (int)(local_10 + (1 - (int)pcVar2) + *param_3);
    local_1c = *(char **)(param_1 + 0xe8);
    local_14 = param_2;
    do {
      cVar1 = *local_1c;
      *local_14 = cVar1;
      local_1c = local_1c + 1;
      local_14 = local_14 + 1;
    } while (cVar1 != '\0');
    local_c = param_2 + (int)(local_10 + (1 - (int)pcVar2));
  }
  FUN_00422c10(local_c,param_3);
  return;
}

