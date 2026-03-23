
undefined4 FUN_005cd560(void)

{
  char cVar1;
  undefined4 uVar2;
  float10 fVar3;
  float10 extraout_ST0;
  
  DAT_009182a4 = 0;
  if (DAT_02a13c7b == '\0') {
    if (DAT_02a13d64 == '\0') {
      uVar2 = 0;
    }
    else {
      fVar3 = (float10)FUN_00822d80();
      if (DAT_02a13d60 <= (float)fVar3) {
        if ((DAT_0091989c != 0x20) && (cVar1 = FUN_005c73b0(), cVar1 == '\0')) {
          return 0;
        }
        FUN_0049f0b0();
        FUN_00822d80();
        DAT_02a13d60 = (float)extraout_ST0 + 1.5;
        DAT_0091989c = 0;
        uVar2 = 1;
      }
      else {
        FUN_0049f0b0();
        DAT_0091989c = 0;
        uVar2 = 0;
      }
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

