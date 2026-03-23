
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_008210f0(void)

{
  float10 fVar1;
  undefined4 local_20;
  undefined4 local_18;
  
  DAT_02cc1b0c = 0;
  fVar1 = (float10)FUN_00689a20(DAT_0091552c,0x57);
  local_18 = (undefined4)(longlong)ROUND(fVar1);
  DAT_02cc1b18 = local_18;
  fVar1 = (float10)FUN_00689a70(DAT_0091552c);
  local_20 = (int)(longlong)ROUND(fVar1);
  DAT_02cc1b08 = local_20;
  if (local_20 == 0) {
    DAT_02cc1b08 = 1;
  }
  _DAT_02cc1b10 = 0;
  _DAT_02cc1b14 = 0;
  return;
}

