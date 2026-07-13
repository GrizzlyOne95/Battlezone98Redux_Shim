
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00618270(undefined4 param_1,int param_2)

{
  int iVar1;
  float10 fVar2;
  
  if ((DAT_008eaaa4 == 0) || (DAT_009183b0 != 0)) {
    param_2 = 1;
  }
  iVar1 = FUN_00572a70(param_1);
  if (((iVar1 != 0) && (DAT_009183f8 == 1)) &&
     (fVar2 = (float10)FUN_00822da0(), _DAT_009183f0 < (float)fVar2)) {
    DAT_009183f8 = 0;
    FUN_00572c00(0);
    iVar1 = FUN_00434160();
    if (iVar1 != 5) {
      return;
    }
  }
  iVar1 = FUN_00616e40(&DAT_02cecee0);
  if (iVar1 != 0) {
    FUN_007d6c70("ERROR, Device_Set_ShutDown has been called");
  }
  FUN_00822ae0();
  if (param_2 == 0) {
    FUN_006210a0();
  }
  if (((DAT_008eaaa4 == 0) && (iVar1 = FUN_00572a70(), iVar1 == 0)) || ((DAT_008fe240 & 0xe) != 0))
  {
    iVar1 = FUN_00572a70();
    if (iVar1 == 0) {
      FUN_00617f50(DAT_008eaaa4);
    }
    else {
      FUN_00618130(1,0);
      FUN_00822ed0(0x14);
    }
  }
  else {
    FUN_00618130(param_2,1);
  }
  return;
}

