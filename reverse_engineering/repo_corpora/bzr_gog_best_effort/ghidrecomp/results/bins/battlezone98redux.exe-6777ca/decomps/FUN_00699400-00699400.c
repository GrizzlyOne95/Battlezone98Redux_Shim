
undefined4 * FUN_00699400(char *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  char *local_18;
  char *local_14;
  char *local_c;
  
  puVar2 = malloc(0x10);
  local_c = param_1;
  do {
    cVar1 = *local_c;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  pcVar3 = malloc((size_t)(local_c + (1 - (int)(param_1 + 1))));
  local_18 = param_1;
  local_14 = pcVar3;
  do {
    cVar1 = *local_18;
    *local_14 = cVar1;
    local_18 = local_18 + 1;
    local_14 = local_14 + 1;
  } while (cVar1 != '\0');
  *puVar2 = pcVar3;
  puVar2[1] = 0;
  puVar2[2] = 0;
  puVar2[3] = 0;
  return puVar2;
}

