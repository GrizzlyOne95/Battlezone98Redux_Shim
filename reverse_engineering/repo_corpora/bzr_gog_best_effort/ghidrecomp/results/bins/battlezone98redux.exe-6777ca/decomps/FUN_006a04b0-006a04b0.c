
uint FUN_006a04b0(char *param_1)

{
  char cVar1;
  int local_10;
  uint local_8;
  
  local_8 = 1;
  while( true ) {
    if (DAT_02ceb7fc <= (int)local_8) {
      return 0;
    }
    cVar1 = *(char *)(DAT_02ceb7e8 + local_8 * 0x9c);
    if (cVar1 == '\0') {
      local_10 = strncmp(param_1,(char *)(*(int *)(DAT_02ceb7e8 + 4 + local_8 * 0x9c) + 0x14),0x51);
    }
    else if (cVar1 == '\x01') {
      local_10 = strncmp(param_1,(char *)(*(int *)(DAT_02ceb7e8 + 4 + local_8 * 0x9c) + 0x40),0x51);
    }
    if (local_10 == 0) break;
    local_8 = local_8 + 1;
  }
  return local_8 & 0xffff;
}

