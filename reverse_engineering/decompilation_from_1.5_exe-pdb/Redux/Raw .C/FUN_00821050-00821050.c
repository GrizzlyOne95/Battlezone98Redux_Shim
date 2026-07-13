
void FUN_00821050(void)

{
  if (DAT_008fe240 == 2) {
    if (DAT_008fe23c == 1) {
      FUN_00623eb0();
      FUN_00437bd0();
      FUN_00822ab0();
    }
    FUN_00820fe0(DAT_008fe23c);
  }
  else {
    if (DAT_008fe23c == 1) {
      FUN_00623ff0();
      FUN_00437bc0();
      FUN_00822a70();
    }
    DAT_008fe23c = FUN_00820fe0(2);
  }
  return;
}

