
void FUN_006901c0(void)

{
  undefined4 uVar1;
  int local_8;
  
  if (DAT_00930f0c == 0) {
    FUN_006a5f50(1,"AI_SpecialForcesClose called without matching Open\n");
  }
  else {
    for (local_8 = 0; local_8 < DAT_00930f18; local_8 = local_8 + 1) {
      uVar1 = FUN_0069d590(&DAT_00930f10,local_8);
      FUN_00690240(uVar1);
    }
    FUN_0069d280(&DAT_00930f10);
    DAT_00930f0c = 0;
  }
  return;
}

