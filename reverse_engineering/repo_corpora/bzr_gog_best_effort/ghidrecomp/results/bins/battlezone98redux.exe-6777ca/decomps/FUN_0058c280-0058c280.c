
char * FUN_0058c280(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = FUN_0058be00(param_1);
  iVar2 = FUN_0058be00(param_2);
  if ((((iVar1 < DAT_02ce99c0) || (DAT_02ce99a0 <= iVar1)) || (iVar2 < DAT_02cd9984)) ||
     (DAT_02ce99c4 <= iVar2)) {
    pcVar3 = (char *)0x0;
  }
  else {
    iVar2 = (int)((iVar2 - DAT_02cd9984) + (iVar2 - DAT_02cd9984 >> 0x1f & 0xfU)) >> 4;
    iVar1 = (int)((iVar1 - DAT_02ce99c0) + (iVar1 - DAT_02ce99c0 >> 0x1f & 0xfU)) >> 4;
    if ((iVar2 < 0) || (DAT_02a13cb8 < iVar2)) {
      pcVar3 = (char *)0x0;
    }
    else if ((iVar1 < 0) || (DAT_02a13c84 < iVar1)) {
      pcVar3 = (char *)0x0;
    }
    else if (DAT_0091814c == 0) {
      pcVar3 = (char *)0x0;
    }
    else {
      pcVar3 = (char *)((iVar2 * DAT_02a13c70 + iVar1) * 0x118 + DAT_0091814c);
      if (*pcVar3 == '\0') {
        FUN_00591710(iVar2,iVar1);
      }
    }
  }
  return pcVar3;
}

