
void FUN_00437a20(void)

{
  char cVar1;
  
  if ((DAT_00915580 != 0) && (DAT_00915588 != 0)) {
    if (DAT_008e75f4 != -1) {
      cVar1 = FUN_004376b0();
      if ((cVar1 != '\0') && (DAT_008e75f8 != -1)) {
        FUN_0043fa40(DAT_008e75f8);
      }
    }
    DAT_00915588 = 0;
  }
  return;
}

