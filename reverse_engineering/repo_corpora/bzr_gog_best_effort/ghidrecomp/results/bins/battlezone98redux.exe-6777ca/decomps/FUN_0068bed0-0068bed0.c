
int FUN_0068bed0(char *param_1)

{
  int iVar1;
  int local_8;
  
  local_8 = DAT_00920f00;
  if (param_1 == (char *)0x0) {
    local_8 = 0;
  }
  else {
    do {
      local_8 = local_8 + -1;
      if (local_8 < 1) {
        return 0;
      }
      iVar1 = _strnicmp(&DAT_00920f08 + local_8 * 0x20,param_1,0x20);
    } while (iVar1 != 0);
  }
  return local_8;
}

