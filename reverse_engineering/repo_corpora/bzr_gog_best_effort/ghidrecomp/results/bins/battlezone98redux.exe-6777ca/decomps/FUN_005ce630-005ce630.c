
bool FUN_005ce630(int param_1)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = FUN_004f3fe0();
  if (iVar1 == 0) {
    bVar2 = false;
  }
  else {
    iVar1 = FUN_00477590(iVar1);
    bVar2 = param_1 == iVar1;
  }
  return bVar2;
}

