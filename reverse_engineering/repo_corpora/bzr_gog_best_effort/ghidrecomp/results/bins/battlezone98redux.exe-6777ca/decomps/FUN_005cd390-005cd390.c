
bool FUN_005cd390(undefined4 param_1)

{
  int iVar1;
  bool bVar2;
  
  if (DAT_02a13c7b == '\0') {
    DAT_009182a4 = DAT_009182a4 + 1;
    iVar1 = FUN_00460fc0(param_1);
    if (iVar1 != 0) {
      FUN_00822560(iVar1,&stack0x00000008,&stack0x0000000c);
    }
    iVar1 = FUN_00821fb0();
    bVar2 = iVar1 == 1;
  }
  else {
    bVar2 = true;
  }
  return bVar2;
}

