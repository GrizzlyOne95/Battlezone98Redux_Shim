
void FUN_006219b0(void)

{
  int iVar1;
  float10 fVar2;
  int local_c;
  int local_8;
  
  memset(&DAT_02a14610,0,0x2c00);
  for (local_8 = 0; local_8 < 0xb; local_8 = local_8 + 1) {
    for (local_c = 1; local_c < 0x71; local_c = local_c + 1) {
      fVar2 = (float10)FUN_004178d0((float)local_c * 0.008928572,(float)(10 - local_8) * 0.25 + 1.0)
      ;
      iVar1 = (int)((float)fVar2 * 65536.0 + 0.5);
      *(int *)(&DAT_02a14610 + (0x70 - local_c) * 4 + local_8 * 0x400) = -iVar1;
      *(int *)(&DAT_02a14610 + (local_c + 0x8f) * 4 + local_8 * 0x400) = iVar1;
    }
  }
  for (local_8 = 0; local_8 < 0x20; local_8 = local_8 + 1) {
    sprintf(&DAT_02a17210 + local_8 * 0xb,"Button %d",local_8 + 1);
    sprintf(&DAT_02a144b0 + local_8 * 0xb,"Button%d",local_8 + 1);
  }
  DAT_008ec244 = 0;
  return;
}

