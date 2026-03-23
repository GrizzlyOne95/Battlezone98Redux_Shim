
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00492ec0(int param_1)

{
  float fVar1;
  float fVar2;
  undefined8 uVar3;
  
  uVar3 = FUN_00689eb0();
  fVar2 = (float)((ulonglong)uVar3 >> 0x20);
  fVar1 = (float)uVar3;
  _DAT_009173c0 = (int)((DAT_008e7754 * fVar1) / 2.0);
  DAT_008e7924 = (DAT_02cecee0 * DAT_009173c4) / 2 + (int)((DAT_008e7918 * fVar1) / 2.0);
  DAT_008e7928 = param_1 - (int)((DAT_008e77b4 * fVar2) / 2.0);
  DAT_008e77a8 = (DAT_02cecee0 * DAT_009173c4) / 2 + (int)((DAT_009782a0 * fVar1) / 2.0);
  DAT_008e77ac = DAT_02cecee4 - (int)((DAT_008e77b0 * 325.0 * fVar2) / 2.0);
  return;
}

