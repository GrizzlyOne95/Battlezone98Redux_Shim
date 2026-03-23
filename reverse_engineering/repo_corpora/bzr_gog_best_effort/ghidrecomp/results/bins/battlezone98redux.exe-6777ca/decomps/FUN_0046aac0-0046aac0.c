
void FUN_0046aac0(void)

{
  undefined4 uVar1;
  int local_8;
  
  DAT_0260d114 = (DAT_02ce99a0 - DAT_02ce99c0) * (DAT_02ce99c4 - DAT_02cd9984);
  DAT_0260d178 = (void *)FUN_0083d92c(DAT_0260d114);
  memset(DAT_0260d178,0,DAT_0260d114);
  DAT_0260d17c = (void *)FUN_0083d92c(DAT_0260d114);
  memset(DAT_0260d17c,0,DAT_0260d114);
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    uVar1 = FUN_0083d92c(DAT_0260d114);
    *(undefined4 *)(&DAT_0260d118 + local_8 * 4) = uVar1;
    memset(*(void **)(&DAT_0260d118 + local_8 * 4),0,DAT_0260d114);
  }
  DAT_0260d180 = (void *)FUN_0083d92c(-(uint)((int)((ulonglong)DAT_0260d114 * 2 >> 0x20) != 0) |
                                      (uint)((ulonglong)DAT_0260d114 * 2));
  memset(DAT_0260d180,0,DAT_0260d114 << 1);
  FUN_00469d90(DAT_0260d114);
  return;
}

