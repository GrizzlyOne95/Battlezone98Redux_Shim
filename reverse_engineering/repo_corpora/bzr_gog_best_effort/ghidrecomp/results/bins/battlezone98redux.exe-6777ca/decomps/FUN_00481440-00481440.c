
uint FUN_00481440(char *param_1)

{
  uint uVar1;
  char *local_c;
  uint local_8;
  
  if (param_1 == (char *)0x0) {
    uVar1 = 0;
  }
  else {
    local_8 = 0x811c9dc5;
    for (local_c = param_1; *local_c != '\0'; local_c = local_c + 1) {
      uVar1 = tolower((int)*local_c);
      local_8 = (uVar1 & 0xff ^ local_8) * 0x1000193;
    }
    uVar1 = (local_8 >> 0xb ^ local_8) & 0x7ff;
  }
  return uVar1;
}

