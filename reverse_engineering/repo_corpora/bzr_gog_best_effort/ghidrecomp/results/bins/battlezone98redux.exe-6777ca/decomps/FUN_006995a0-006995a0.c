
undefined4 * FUN_006995a0(undefined4 param_1,char *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  char *local_18;
  char *local_10;
  char *local_c;
  
  puVar2 = malloc(0x10);
  local_c = param_2;
  do {
    cVar1 = *local_c;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  pcVar3 = malloc((size_t)(local_c + (1 - (int)(param_2 + 1))));
  local_18 = param_2;
  local_10 = pcVar3;
  do {
    cVar1 = *local_18;
    *local_10 = cVar1;
    local_18 = local_18 + 1;
    local_10 = local_10 + 1;
  } while (cVar1 != '\0');
  puVar2[1] = pcVar3;
  *puVar2 = param_1;
  puVar2[3] = 0;
  return puVar2;
}

