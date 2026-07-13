
void FUN_0081eb30(void)

{
  int iStack_14;
  int local_8;
  
  for (local_8 = 0; local_8 < 0x100; local_8 = local_8 + 1) {
    iStack_14 = (int)((ulonglong)
                      (1.0 / SQRT((double)((ulonglong)(uint)(local_8 << 0xd) << 0x20 |
                                          0x3fe0000000000000))) >> 0x20);
    (&DAT_02cc3fa0)[local_8] = (char)(iStack_14 + 0x400 >> 0xc);
  }
  DAT_02cc4020 = 0xff;
  return;
}

