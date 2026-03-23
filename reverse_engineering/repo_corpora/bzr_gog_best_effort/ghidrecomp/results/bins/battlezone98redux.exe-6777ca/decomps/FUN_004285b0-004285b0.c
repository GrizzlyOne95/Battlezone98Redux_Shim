
int * __fastcall FUN_004285b0(int *param_1)

{
  char *pcVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  
  pcVar1 = (char *)FUN_004242d0(*param_1);
  if (*pcVar1 == '\0') {
    puVar3 = (undefined4 *)FUN_00417780(*param_1);
    pcVar1 = (char *)FUN_004242d0(*puVar3);
    if (*pcVar1 == '\0') {
      puVar3 = (undefined4 *)FUN_00417780(*param_1);
      iVar4 = FUN_00425010(*puVar3);
      *param_1 = iVar4;
    }
    else {
      while( true ) {
        piVar2 = (int *)FUN_004242e0(*param_1);
        iVar4 = *piVar2;
        pcVar1 = (char *)FUN_004242d0(iVar4);
        if ((*pcVar1 != '\0') || (piVar2 = (int *)FUN_00417780(iVar4), *param_1 != *piVar2)) break;
        *param_1 = iVar4;
      }
      pcVar1 = (char *)FUN_004242d0(*param_1);
      if (*pcVar1 == '\0') {
        *param_1 = iVar4;
      }
    }
  }
  else {
    piVar2 = (int *)FUN_004242f0(*param_1);
    *param_1 = *piVar2;
  }
  return param_1;
}

