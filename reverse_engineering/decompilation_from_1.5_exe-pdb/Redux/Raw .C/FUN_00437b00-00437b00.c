
void FUN_00437b00(void)

{
  int iVar1;
  
  if (((DAT_008e75f8 != -1) && (DAT_00915580 != 0)) && (DAT_00915588 == 0)) {
    iVar1 = FUN_0043faa0(DAT_008e75f8);
    if (iVar1 == 0) {
      if (DAT_00915584 == 0) {
        FUN_00437a70();
        iVar1 = DAT_008e75f4 + 1;
        if (DAT_008e75f4 + 1 == DAT_008e75f0) {
          iVar1 = DAT_008e75f4 + 2;
        }
        DAT_008e75f4 = iVar1;
        if (DAT_008e75fc < DAT_008e75f4) {
          DAT_008e75f4 = DAT_008e7600;
        }
        FUN_004378f0();
      }
      else {
        FUN_0043fa00(DAT_008e75f8);
        FUN_0043f9e0(DAT_008e75f8);
      }
    }
  }
  return;
}

