
void FUN_005d2300(int param_1)

{
  float *pfVar1;
  float10 fVar2;
  float10 fVar3;
  
  pfVar1 = (float *)FUN_005111d0(0);
  DAT_009182d0 = *pfVar1;
  DAT_009182d4 = pfVar1[1];
  pfVar1 = (float *)FUN_005111d0(1);
  DAT_009182c8 = *pfVar1;
  DAT_009182cc = pfVar1[1];
  fVar2 = (float10)FUN_00453f80(DAT_009182c8 - DAT_009182d0);
  fVar3 = (float10)FUN_00453f80(DAT_009182cc - DAT_009182d4);
  if ((float)fVar2 * (float)fVar3 <= 10000.0) {
    *(undefined4 *)(param_1 + 0x10) = 0x10;
    DAT_009182e4 = param_1;
    FUN_005d23e0();
    FUN_005d2400();
    FUN_005d2650();
    FUN_005d23f0();
  }
  return;
}

