
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006a5f50(uint param_1,char *param_2)

{
  char *pcVar1;
  undefined2 *local_c;
  
  if ((DAT_009310b4 & param_1) == 0) {
    _DAT_009310bc = 0;
  }
  else {
    vsprintf((char *)&DAT_02cc3390,param_2,&stack0x0000000c);
    local_c = (undefined2 *)&DAT_02cc338f;
    do {
      pcVar1 = (char *)((int)local_c + 1);
      local_c = (undefined2 *)((int)local_c + 1);
    } while (*pcVar1 != '\0');
    *local_c = 10;
    FUN_007d6a70(&DAT_02cc3390);
  }
  return;
}

