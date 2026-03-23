
void FUN_004e31a0(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int local_10;
  char *local_c;
  char *local_8;
  
  local_8 = param_1;
  local_10 = 0;
  for (local_c = (char *)&param_2; (local_10 < 8 && (*local_c != '\0')); local_c = local_c + 1) {
    *local_8 = *local_c;
    local_8 = local_8 + 1;
    local_10 = local_10 + 1;
  }
  *(undefined4 *)local_8 = param_4;
  local_8[4] = '\0';
  return;
}

