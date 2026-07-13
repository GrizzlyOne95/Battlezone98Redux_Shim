
void FUN_00830294(int param_1)

{
  int iVar1;
  int *extraout_EDX;
  int *piVar2;
  int iVar3;
  
  iVar3 = 9;
  piVar2 = (int *)(param_1 + 0x98);
  do {
    iVar1 = *piVar2;
    if ((iVar1 != 0) && ((*(byte *)(iVar1 + 5) & 3) != 0)) {
      FUN_00830437(param_1,iVar1);
      piVar2 = extraout_EDX;
    }
    piVar2 = piVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}

