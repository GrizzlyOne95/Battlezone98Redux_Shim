
undefined4 FUN_0080e680(int param_1,double *param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  float10 fVar2;
  double in_XMM0_Qa;
  
  if (param_1 < 0) {
    if (param_1 < -0x133) {
      FUN_0080fcf0(param_2,param_3,param_4);
      fVar2 = (float10)FUN_007f5020(0x133);
      *param_2 = *param_2 / (double)fVar2;
      cVar1 = FUN_00435a30();
      if ((cVar1 != '\0') && (0x133 < -0x133 - param_1)) {
        return 0;
      }
      fVar2 = (float10)FUN_007f5020(-0x133 - param_1);
      *param_2 = *param_2 / (double)fVar2;
    }
    else {
      FUN_008448ce();
      fVar2 = (float10)FUN_007f5020(-param_1);
      *param_2 = in_XMM0_Qa / (double)fVar2;
    }
  }
  else {
    cVar1 = FUN_00435a30();
    if ((cVar1 != '\0') && (0x134 < param_1)) {
      return 0;
    }
    FUN_008448ce();
    fVar2 = (float10)FUN_007f5020(param_1);
    *param_2 = in_XMM0_Qa * (double)fVar2;
  }
  return 1;
}

