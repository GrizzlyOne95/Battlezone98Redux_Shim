
char * FUN_0082c225(undefined4 param_1,undefined4 param_2,char *param_3,int *param_4)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  iVar2 = FUN_0082d490(param_1,param_2);
  if (iVar2 < 1) {
    if (param_4 != (int *)0x0) {
      if (param_3 == (char *)0x0) {
        iVar2 = 0;
      }
      else {
        pcVar3 = param_3;
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        iVar2 = (int)pcVar3 - (int)(param_3 + 1);
      }
      *param_4 = iVar2;
    }
    return param_3;
  }
  pcVar3 = (char *)FUN_0082ba59(param_1,param_2,param_4);
  return pcVar3;
}

