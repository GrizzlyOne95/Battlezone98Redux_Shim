
undefined4 FUN_0061e530(char *param_1,int param_2,FILE *param_3)

{
  bool bVar1;
  char *pcVar2;
  int iVar3;
  char *local_8;
  
  bVar1 = false;
  do {
    pcVar2 = fgets(param_1,param_2,param_3);
    if (pcVar2 == (char *)0x0) {
      return 0;
    }
    for (local_8 = param_1; *local_8 != '\0'; local_8 = local_8 + 1) {
      if (*local_8 == '\n') {
        *local_8 = '\0';
        break;
      }
      iVar3 = isspace((int)*local_8);
      if (iVar3 == 0) {
        bVar1 = true;
      }
    }
    if (bVar1) {
      return 1;
    }
  } while( true );
}

