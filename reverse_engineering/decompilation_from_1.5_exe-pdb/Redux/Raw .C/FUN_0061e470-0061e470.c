
undefined4 FUN_0061e470(byte *param_1,int param_2,FILE *param_3)

{
  bool bVar1;
  char *pcVar2;
  int iVar3;
  byte *local_8;
  
  bVar1 = false;
  do {
    pcVar2 = fgets((char *)param_1,param_2,param_3);
    if (pcVar2 == (char *)0x0) {
      return 0;
    }
    DAT_0091fef8 = DAT_0091fef8 + 1;
    for (local_8 = param_1; *local_8 != 0; local_8 = local_8 + 1) {
      if ((*local_8 == 10) || (*local_8 == 0x23)) {
        *local_8 = 0;
        break;
      }
      iVar3 = isspace((uint)*local_8);
      if (iVar3 == 0) {
        bVar1 = true;
      }
    }
    if (bVar1) {
      return 1;
    }
  } while( true );
}

