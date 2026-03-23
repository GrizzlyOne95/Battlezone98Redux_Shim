
char * FUN_0082bc6c(undefined4 param_1,undefined4 param_2,char *param_3,undefined4 param_4)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  undefined4 uVar4;
  
  FUN_0082cdd2(param_1,param_2);
  do {
    pcVar2 = strchr(param_3,0x2e);
    pcVar1 = param_3;
    if (pcVar2 == (char *)0x0) {
      do {
        pcVar2 = pcVar1;
        pcVar1 = pcVar2 + 1;
      } while (*pcVar2 != '\0');
    }
    FUN_0082cd08(param_1,param_3,(int)pcVar2 - (int)param_3);
    FUN_0082ce65(param_1,0xfffffffe);
    iVar3 = FUN_0082d490(param_1,0xffffffff);
    if (iVar3 == 0) {
      FUN_0082d226(param_1,0xfffffffe);
      uVar4 = param_4;
      if (*pcVar2 == '.') {
        uVar4 = 1;
      }
      FUN_0082c68b(param_1,0,uVar4);
      FUN_0082cd08(param_1,param_3,(int)pcVar2 - (int)param_3);
      FUN_0082cdd2(param_1,0xfffffffe);
      FUN_0082d1fa(param_1,0xfffffffc);
    }
    else {
      iVar3 = FUN_0082d490(param_1,0xffffffff);
      if (iVar3 != 5) {
        FUN_0082d226(param_1,0xfffffffd);
        return param_3;
      }
    }
    FUN_0082cf99(param_1,0xfffffffe);
    param_3 = pcVar2 + 1;
  } while (*pcVar2 == '.');
  return (char *)0x0;
}

