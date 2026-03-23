
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006990e0(void)

{
  if (DAT_00930f7c == 0) {
    _DAT_009310bc = "Schedule\\Grasfire.c";
    _DAT_009310c0 = 0xeb;
    FUN_006a5f50(1,"Grassfire Closed without matching open.");
  }
  else {
    DAT_00930f7c = 0;
    free(DAT_02ceb808);
    free(DAT_02ceb804);
    free(DAT_02ceb80c);
    FUN_0069f010(DAT_02ceb818,0,DAT_02ceb810 + -1,0,DAT_02ceb814 + -1);
  }
  return;
}

