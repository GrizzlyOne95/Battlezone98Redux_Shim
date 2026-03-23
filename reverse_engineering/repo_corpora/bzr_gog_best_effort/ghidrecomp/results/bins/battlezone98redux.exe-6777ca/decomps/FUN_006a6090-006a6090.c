
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006a6090(char *param_1)

{
  if (DAT_009310b4 != 0) {
    vsprintf(&DAT_02c00ac0,param_1,&stack0x00000008);
    _DAT_009310bc = "Schedule\\ScheduleGlue.cpp";
    _DAT_009310c0 = 0xbf2;
    FUN_006a5f50(0x8000,&DAT_02c00ac0,0);
  }
  return;
}

