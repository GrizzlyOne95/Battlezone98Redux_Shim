
void FUN_006af0d0(byte param_1,undefined4 param_2,char param_3,undefined4 param_4,int param_5)

{
  char cVar1;
  int iVar2;
  
  iVar2 = get();
  if (iVar2 == 0x40) {
    cVar1 = FUN_006c9460();
    if (cVar1 == '\0') {
      FUN_006d8cf0(0x2746);
    }
    else {
      FUN_006d8cf0(0x3e3);
    }
  }
  else {
    iVar2 = get();
    if (iVar2 == 0x4d2) {
      FUN_006d8cf0(0x274d);
    }
    else {
      cVar1 = FUN_004c85a0();
      if ((((cVar1 != '\0') && (param_5 == 0)) && ((param_1 & 0x10) != 0)) && (param_3 == '\0')) {
        FUN_006d8e00(2);
      }
    }
  }
  return;
}

