
void FUN_00434390(undefined4 *param_1)

{
  char *pcVar1;
  char *local_10;
  char *local_c;
  
  *param_1 = 0;
  param_1[1] = 0;
  local_c = (char *)FUN_00434140(&DAT_00915540,0x2e);
  if (local_c == (char *)0x0) {
    local_c = &DAT_00915540;
    pcVar1 = local_c;
    do {
      local_c = pcVar1;
      pcVar1 = local_c + 1;
    } while (*local_c != '\0');
  }
  local_10 = local_c + -0x915540;
  if ((int)local_10 < 0x11) {
    memcpy(param_1,&DAT_00915540,(size_t)local_10);
  }
  return;
}

