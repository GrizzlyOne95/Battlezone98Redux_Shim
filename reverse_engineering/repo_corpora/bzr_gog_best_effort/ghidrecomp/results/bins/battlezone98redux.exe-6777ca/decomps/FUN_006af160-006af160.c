
void FUN_006af160(void)

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
  }
  return;
}

