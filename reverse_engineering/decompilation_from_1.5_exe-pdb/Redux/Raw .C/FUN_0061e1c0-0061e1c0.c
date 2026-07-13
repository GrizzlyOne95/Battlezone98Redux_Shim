
int FUN_0061e1c0(char *param_1)

{
  int iVar1;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (DAT_0091a364 <= local_8) {
      iVar1 = FUN_0061df70(param_1);
      return iVar1;
    }
    iVar1 = _stricmp(&DAT_0091a368 + local_8 * 0x28,param_1);
    if (iVar1 == 0) break;
    local_8 = local_8 + 1;
  }
  if ((&DAT_0091a434)[local_8] != 0) {
    return local_8;
  }
  return -1;
}

