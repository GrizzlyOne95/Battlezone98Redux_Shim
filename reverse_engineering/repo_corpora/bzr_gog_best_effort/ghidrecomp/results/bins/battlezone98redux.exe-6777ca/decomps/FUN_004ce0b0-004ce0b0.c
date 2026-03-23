
void FUN_004ce0b0(void)

{
  DAT_0260db0c = DAT_0260db08;
  while( true ) {
    if (DAT_0260db00 <= DAT_0260db0c) {
      return;
    }
    if (*DAT_0260db0c == '\r') break;
    DAT_0260db0c = DAT_0260db0c + 1;
  }
  *DAT_0260db0c = '\0';
  return;
}

