
void FUN_0068f7b0(void)

{
  int local_8;
  
  FUN_006a5fd0("AI::DR_AI_Init Begins");
  DAT_00930f08 = 1;
  DAT_00920f04 = FUN_006a8d40((int)(DAT_008eda24 + 0xf + (DAT_008eda24 + 0xf >> 0x1f & 0xfU)) >> 4,
                              (int)(DAT_008eda20 + 0xf + (DAT_008eda20 + 0xf >> 0x1f & 0xfU)) >> 4,
                              0x10);
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    FUN_006a5fd0("aicontrol[%d] = %d\n",local_8,(&DAT_02ce9b18)[local_8 * 0x1e0]);
  }
  FUN_00692fb0();
  FUN_006949b0();
  FUN_00698c40(*(undefined4 *)(DAT_00920f04 + 0x80),*(undefined4 *)(DAT_00920f04 + 0x84));
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    *(undefined4 *)(&DAT_00930f28 + local_8 * 4) = 0;
  }
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    if ((&DAT_02ce9b18)[local_8 * 0x1e0] != '\0') {
      FUN_0068f6c0(local_8);
    }
  }
  FUN_006a5fd0("AI   All AI Teams created and units added\n");
  FUN_006a5fd0("AI::DR_AI_Init Ends");
  return;
}

