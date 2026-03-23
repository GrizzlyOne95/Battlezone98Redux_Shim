
int FUN_004e1b90(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_2 + 0x48);
  iVar1 = FUN_00461430();
  iVar2 = FUN_004e0150();
  if (iVar2 == 0) {
    iVar2 = FUN_00572a70();
    if ((iVar2 == 0) && (param_1 == iVar1)) {
      if (DAT_025cfa1c == 0) {
        iVar3 = FUN_0043d130(iVar3 + -2,0);
      }
      else if (DAT_025cfa1c == 1) {
        iVar3 = FUN_0043d130(iVar3 + -1,0);
      }
    }
  }
  else {
    iVar3 = 0;
  }
  return iVar3;
}

