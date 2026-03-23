
int * __fastcall FUN_004238b0(int *param_1)

{
  char *pcVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  
  pcVar1 = (char *)FUN_004242d0(*param_1);
  if (*pcVar1 == '\0') {
    puVar2 = (undefined4 *)FUN_004242f0(*param_1);
    pcVar1 = (char *)FUN_004242d0(*puVar2);
    if (*pcVar1 == '\0') {
      puVar2 = (undefined4 *)FUN_004242f0(*param_1);
      iVar3 = FUN_00424310(*puVar2);
      *param_1 = iVar3;
    }
    else {
      while( true ) {
        piVar4 = (int *)FUN_004242e0(*param_1);
        iVar3 = *piVar4;
        pcVar1 = (char *)FUN_004242d0(iVar3);
        if ((*pcVar1 != '\0') || (piVar4 = (int *)FUN_004242f0(iVar3), *param_1 != *piVar4)) break;
        *param_1 = iVar3;
      }
      *param_1 = iVar3;
    }
  }
  return param_1;
}

