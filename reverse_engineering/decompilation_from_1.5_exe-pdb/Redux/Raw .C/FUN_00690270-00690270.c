
void FUN_00690270(void)

{
  if (DAT_00930f24 != 0) {
    FUN_006a5f50(1,"AI_AIPInit called twice without matching Close\n");
  }
  FUN_0069d210(&DAT_00930f68);
  DAT_00930f24 = 1;
  FUN_00690480();
  return;
}

