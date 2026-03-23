
void FUN_00830650(undefined4 param_1,int param_2)

{
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  int iVar1;
  int *piVar2;
  
  if ((*(byte *)(*(int *)(param_2 + 0xc) + 5) & 3) != 0) {
    FUN_00830437(param_1,*(int *)(param_2 + 0xc));
    param_2 = extraout_EDX;
  }
  if (*(char *)(param_2 + 6) == '\0') {
    if ((*(byte *)(*(int *)(param_2 + 0x10) + 5) & 3) != 0) {
      FUN_00830437(param_1,*(int *)(param_2 + 0x10));
      param_2 = extraout_EDX_01;
    }
    iVar1 = 0;
    if (*(char *)(param_2 + 7) != '\0') {
      piVar2 = (int *)(param_2 + 0x14);
      do {
        if ((*(byte *)(*piVar2 + 5) & 3) != 0) {
          FUN_00830437(param_1,*piVar2);
          param_2 = extraout_EDX_02;
        }
        iVar1 = iVar1 + 1;
        piVar2 = piVar2 + 1;
      } while (iVar1 < (int)(uint)*(byte *)(param_2 + 7));
    }
  }
  else {
    iVar1 = 0;
    if (*(char *)(param_2 + 7) != '\0') {
      piVar2 = (int *)(param_2 + 0x18);
      do {
        if ((3 < piVar2[2]) && ((*(byte *)(*piVar2 + 5) & 3) != 0)) {
          FUN_00830437(param_1,*piVar2);
          param_2 = extraout_EDX_00;
        }
        iVar1 = iVar1 + 1;
        piVar2 = piVar2 + 4;
      } while (iVar1 < (int)(uint)*(byte *)(param_2 + 7));
    }
  }
  return;
}

