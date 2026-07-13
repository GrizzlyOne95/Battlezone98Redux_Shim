
void FUN_0069d0f0(int param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  int local_28;
  char *local_1c;
  char *local_14;
  char *local_10;
  int local_c;
  
  local_10 = param_2;
  do {
    cVar1 = *local_10;
    local_10 = local_10 + 1;
  } while (cVar1 != '\0');
  local_c = (int)local_10 - (int)(param_2 + 1);
  if (param_2[local_c + -1] != '\\') {
    local_c = local_c + 1;
    local_28 = 1;
  }
  pcVar2 = malloc(local_c + 1);
  local_1c = param_2;
  local_14 = pcVar2;
  do {
    cVar1 = *local_1c;
    *local_14 = cVar1;
    local_1c = local_1c + 1;
    local_14 = local_14 + 1;
  } while (cVar1 != '\0');
  if (local_28 != 0) {
    pcVar2[local_c + -1] = '\\';
    pcVar2[local_c] = '\0';
  }
  FUN_0069d3c0(param_1 + 0x10,pcVar2,pcVar2);
  return;
}

