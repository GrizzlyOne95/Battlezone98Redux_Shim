
undefined4 * FUN_006994c0(undefined4 param_1,char *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  char *local_18;
  char *local_14;
  char *local_10;
  
  puVar2 = malloc(0x28);
  local_10 = param_2;
  do {
    cVar1 = *local_10;
    local_10 = local_10 + 1;
  } while (cVar1 != '\0');
  pcVar3 = malloc((size_t)(local_10 + (1 - (int)(param_2 + 1))));
  local_18 = param_2;
  local_14 = pcVar3;
  do {
    cVar1 = *local_18;
    *local_14 = cVar1;
    local_18 = local_18 + 1;
    local_14 = local_14 + 1;
  } while (cVar1 != '\0');
  puVar2[1] = pcVar3;
  *puVar2 = param_1;
  puVar2[6] = 0;
  puVar2[2] = 0;
  puVar2[8] = 0;
  puVar2[9] = 0;
  puVar2[7] = 0;
  return puVar2;
}

