
void FUN_004e3120(char *param_1,char *param_2,undefined4 *param_3)

{
  uint local_10;
  char *local_c;
  char *local_8;
  
  local_c = param_1;
  local_8 = param_2;
  for (local_10 = 0; local_10 < 8; local_10 = local_10 + 1) {
    if (*local_c == '.') {
      *local_8 = '\0';
    }
    else {
      *local_8 = *local_c;
      local_c = local_c + 1;
    }
    local_8 = local_8 + 1;
  }
  *param_3 = *(undefined4 *)local_c;
  return;
}

