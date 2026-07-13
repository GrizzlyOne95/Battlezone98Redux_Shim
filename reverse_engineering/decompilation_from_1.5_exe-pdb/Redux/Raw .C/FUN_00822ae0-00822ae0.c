
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00822ae0(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  float local_18;
  
  while (iVar2 = FUN_00822e60(), DAT_02cc1b20 == iVar2) {
    FUN_00822ed0(1);
  }
  iVar2 = FUN_00822e60();
  DAT_02cc1b24 = DAT_02cc1b24 + 1;
  if ((DAT_02cc1b1c == 0) || (iVar3 = FUN_00572a70(), iVar3 != 0)) {
    DAT_00946794 = iVar2 - DAT_02cc1b20;
  }
  else {
    DAT_00946794 = 0;
  }
  iVar3 = FUN_00572a70();
  uVar1 = DAT_00946794;
  if (iVar3 == 0) {
    DAT_02cc1b28 = DAT_02cc1b28 + DAT_00946794;
  }
  else if (DAT_008fe244 == 0) {
    DAT_02cc1b28 = (iVar2 - _DAT_00946798) - DAT_0094678c;
  }
  else {
    DAT_02cc1b28 = (iVar2 + _DAT_00946798) - DAT_0094678c;
  }
  DAT_02cc1b30 = DAT_02cc1b30 + DAT_00946794;
  DAT_0094679c = DAT_00946794;
  if (200 < DAT_00946794) {
    DAT_00946794 = 200;
  }
  _DAT_02cc1b2c =
       (float)((double)DAT_02cc1b28 + (double)(&DAT_008a2fd0)[-(DAT_02cc1b28 >> 0x1f)]) * 0.001;
  DAT_00946790 = (float)((double)(int)DAT_00946794 +
                        (double)(&DAT_008a2fd0)[-((int)DAT_00946794 >> 0x1f)]) * 0.001;
  _DAT_00946788 =
       (float)((double)(int)uVar1 + (double)(&DAT_008a2fd0)[-((int)uVar1 >> 0x1f)]) * 0.001;
  if (DAT_00946790 == 0.0) {
    local_18 = (float)*(double *)_HUGE_exref;
  }
  else {
    local_18 = 1.0 / DAT_00946790;
  }
  _DAT_02cc1b34 = local_18;
  _DAT_02cc1b3c =
       (float)((double)DAT_02cc1b30 + (double)(&DAT_008a2fd0)[-(DAT_02cc1b30 >> 0x1f)]) * 0.001;
  if (DAT_00946794 != 0) {
    DAT_02cc1b20 = iVar2;
  }
  return;
}

