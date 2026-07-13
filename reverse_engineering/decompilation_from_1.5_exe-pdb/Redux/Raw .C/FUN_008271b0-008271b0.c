
int FUN_008271b0(char *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  char *pcVar3;
  FILE *local_8;
  
  if (param_2 == 0) {
    local_8 = fopen(param_1,"rb");
    if (local_8 != (FILE *)0x0) {
      setvbuf(local_8,(char *)0x0,4,0);
    }
  }
  else {
    local_8 = fopen(param_1,"rb+");
    if (((local_8 == (FILE *)0x0) && (piVar1 = _errno(), *piVar1 == 2)) &&
       (iVar2 = FUN_00826c40(param_1,0), iVar2 != 0)) {
      local_8 = fopen(param_1,"rb+");
    }
  }
  if (local_8 == (FILE *)0x0) {
    sprintf(&DAT_009467c0,"Could not open file \"%s\"",param_1);
    iVar2 = 0;
  }
  else {
    pcVar3 = strrchr(param_1,0x2f);
    if (pcVar3 != (char *)0x0) {
      param_1 = pcVar3 + 1;
    }
    pcVar3 = strrchr(param_1,0x5c);
    if (pcVar3 != (char *)0x0) {
      param_1 = pcVar3 + 1;
    }
    iVar2 = FUN_00827030(param_1,local_8);
    if (iVar2 == 0) {
      fclose(local_8);
      iVar2 = 0;
    }
  }
  return iVar2;
}

