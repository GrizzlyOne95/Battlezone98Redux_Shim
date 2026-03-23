
void FUN_0043c230(void)

{
  float10 fVar1;
  int local_8;
  
  DAT_0260c930 = 0xffffd8f0;
  for (local_8 = 1; local_8 < 0x65; local_8 = local_8 + 1) {
    fVar1 = (float10)FUN_0043c210((float)local_8 / 100.0);
    (&DAT_0260c930)[local_8] = (int)((float)fVar1 * 400.0);
  }
  return;
}

