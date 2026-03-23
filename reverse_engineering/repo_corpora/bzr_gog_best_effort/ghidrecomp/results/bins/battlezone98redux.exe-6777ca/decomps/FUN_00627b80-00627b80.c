
void FUN_00627b80(void)

{
  ulong *puVar1;
  int iVar2;
  float10 fVar3;
  int local_28;
  int local_24;
  float local_1c;
  float local_18;
  int local_c;
  int local_8;
  
  iVar2 = FUN_00684ca0(0);
  puVar1 = DAT_0091552c;
  if (((iVar2 != 0) && (DAT_02a17494 != 0)) && (DAT_008eaab0 != 0)) {
    iVar2 = FUN_004344a0();
    if (iVar2 == 2) {
      local_28 = 0x154;
      local_24 = 0x50;
    }
    else {
      local_28 = 0xf0;
      local_24 = 0x3c;
    }
    if (*(char *)(DAT_0094672c + 0x26) == '\0') {
      fVar3 = (float10)FUN_00461fd0((float)DAT_02cecee0 * 0.00052083336 * 2.0 + 0.5);
      local_18 = (float)fVar3;
      fVar3 = (float10)FUN_00461fd0((float)DAT_02cecee4 * 0.0009259259 * 2.0 + 0.5);
      local_1c = (float)fVar3;
    }
    else {
      local_18 = (float)*(byte *)(DAT_0094672c + 0x26);
      local_1c = (float)*(byte *)(DAT_0094672c + 0x26);
    }
    local_c = (int)((float)local_24 * local_1c);
    FUN_00689970(5,&DAT_008ec75c);
    FUN_00627b10(puVar1,&DAT_02cecee0,(int)((float)local_28 * local_18),local_c,&DAT_00920c08,
                 DAT_0091755c);
    fVar3 = (float10)FUN_00689a70(puVar1);
    FUN_0043d650((float)fVar3);
    iVar2 = FUN_0083f040();
    for (local_8 = 0; local_8 < DAT_00920178; local_8 = local_8 + 1) {
      local_c = local_c + iVar2;
      std::_Init_atomic_counter(puVar1,(&DAT_00920b88)[local_8]);
      FUN_00627b10(puVar1,&DAT_02cecee0,(int)((float)local_28 * local_18),local_c,
                   &DAT_00920188 + local_8 * 0x50,(&DAT_00920b88)[local_8]);
    }
  }
  return;
}

