
undefined4 FUN_00437380(void)

{
  LCID LVar1;
  undefined4 uVar2;
  
  LVar1 = GetSystemDefaultLCID();
  if ((LVar1 & 0x3ff) == 9) {
    uVar2 = 1;
  }
  else if ((LVar1 & 0x3ff) == 0xc) {
    uVar2 = 2;
  }
  else if ((LVar1 & 0x3ff) == 7) {
    uVar2 = 3;
  }
  else if ((LVar1 & 0x3ff) == 10) {
    uVar2 = 4;
  }
  else if ((LVar1 & 0x3ff) == 0x10) {
    uVar2 = 5;
  }
  else if ((LVar1 & 0x3ff) == 0x16) {
    uVar2 = 6;
  }
  else if ((LVar1 & 0x3ff) == 0x19) {
    uVar2 = 7;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

