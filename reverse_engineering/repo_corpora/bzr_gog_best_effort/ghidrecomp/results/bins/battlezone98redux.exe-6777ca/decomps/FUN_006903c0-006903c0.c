
void FUN_006903c0(void)

{
  undefined4 uVar1;
  int local_8;
  
  FUN_006a5fd0("AIPClose BEGINS\n");
  if (DAT_00930f24 == 0) {
    FUN_006a5f50(1,"AI_AIPClose called without matching Init\n");
  }
  else {
    for (local_8 = 0; local_8 < DAT_00930f70; local_8 = local_8 + 1) {
      uVar1 = FUN_0069d590(&DAT_00930f68,local_8);
      FUN_006a5fd0("   deleting aip #%08x\n",uVar1);
      FUN_006947c0(uVar1);
    }
  }
  DAT_00930f24 = 0;
  FUN_006a5fd0("freeing list of pointers to aip\'s\n");
  FUN_0069d280(&DAT_00930f68);
  FUN_006a5fd0("AIPClose ENDS\n");
  FUN_006904f0();
  return;
}

