
void FUN_00437800(int param_1)

{
  int iVar1;
  
  if (DAT_008e75f8 != -1) {
    if ((0 < param_1) && (DAT_00915580 == 0)) {
      DAT_00915580 = 1;
      DAT_00915584 = DAT_00918324;
      FUN_0043f9e0(DAT_008e75f8);
    }
    if (DAT_00915580 != 0) {
      iVar1 = FUN_0043fa80(DAT_008e75f8);
      if (iVar1 != 0) {
        if (param_1 < 1) {
          iVar1 = FUN_0043faa0(DAT_008e75f8);
          if (iVar1 != 0) {
            DAT_00915588 = 1;
            FUN_0043fa20(DAT_008e75f8);
          }
          _putchar(DAT_008e75f8);
        }
        else {
          iVar1 = FUN_0043faa0(DAT_008e75f8);
          if (iVar1 == 0) {
            DAT_00915588 = 0;
            FUN_0043fa40(DAT_008e75f8);
          }
          FUN_0043fac0(DAT_008e75f8,param_1);
        }
      }
    }
  }
  return;
}

