
float10 FUN_004464c0(void)

{
  DAT_00946734 = DAT_00946734 + 1 & 0xff;
  return (float10)*(float *)(&DAT_02cc3ba0 + DAT_00946734 * 4);
}

