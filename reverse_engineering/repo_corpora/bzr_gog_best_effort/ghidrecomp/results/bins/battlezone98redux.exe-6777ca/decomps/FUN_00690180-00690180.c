
void FUN_00690180(void)

{
  if (DAT_00930f0c != 0) {
    FUN_006a5f50(1,"AI_SpecialForcesInit called twice without matching Close\n");
  }
  FUN_0069d210(&DAT_00930f10);
  DAT_00930f0c = 1;
  return;
}

