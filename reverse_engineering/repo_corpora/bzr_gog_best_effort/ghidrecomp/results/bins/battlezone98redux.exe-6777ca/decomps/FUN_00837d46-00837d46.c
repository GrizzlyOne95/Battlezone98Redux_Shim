
char * FUN_00837d46(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  char *pcVar4;
  undefined4 uVar5;
  FILE *_File;
  char *pcVar6;
  
  uVar3 = FUN_0082bd93(param_1,param_2,&DAT_008752b0,&DAT_00871328);
  FUN_0082c82c(param_1,0xffffd8ef,param_3);
  pcVar4 = (char *)FUN_0082d377(param_1,0xffffffff,0);
  if (pcVar4 == (char *)0x0) {
    FUN_0082bc39(param_1,"\'package.%s\' must be a string",param_3);
  }
  FUN_0082cd08(param_1,&DAT_008a1ad8,0);
  while( true ) {
    cVar1 = *pcVar4;
    pcVar6 = pcVar4;
    while (cVar1 == ';') {
      pcVar6 = pcVar6 + 1;
      cVar1 = *pcVar6;
    }
    if (*pcVar6 == '\0') {
      return (char *)0x0;
    }
    pcVar4 = strchr(pcVar6,0x3b);
    pcVar2 = pcVar6;
    if (pcVar4 == (char *)0x0) {
      do {
        pcVar4 = pcVar2;
        pcVar2 = pcVar4 + 1;
      } while (*pcVar4 != '\0');
    }
    FUN_0082cd08(param_1,pcVar6,(int)pcVar4 - (int)pcVar6);
    if (pcVar4 == (char *)0x0) break;
    uVar5 = FUN_0082d377(param_1,0xffffffff,0,&DAT_0088d940,uVar3);
    pcVar6 = (char *)FUN_0082bd93(param_1,uVar5);
    FUN_0082cf99(param_1,0xfffffffe);
    _File = fopen(pcVar6,"r");
    if (_File != (FILE *)0x0) {
      fclose(_File);
      return pcVar6;
    }
    FUN_0082cc9e(param_1,"\n\tno file \'%s\'",pcVar6);
    FUN_0082cf99(param_1,0xfffffffe);
    FUN_0082c61c(param_1,2);
  }
  return (char *)0x0;
}

