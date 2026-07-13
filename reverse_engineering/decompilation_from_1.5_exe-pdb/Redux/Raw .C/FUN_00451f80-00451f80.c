
void __thiscall FUN_00451f80(undefined4 param_1,int param_2)

{
  float fVar1;
  int iVar2;
  float10 fVar3;
  
  iVar2 = FUN_00439e60(param_1);
  if (param_2 == iVar2) {
    iVar2 = FUN_00451de0();
    if (iVar2 == 0) {
      fVar3 = (float10)FUN_00822d60();
      fVar1 = (float)fVar3;
      if (0.0 < fVar1) {
        FUN_004519a0(fVar1);
      }
      FUN_0044e7f0(fVar1);
    }
  }
  iVar2 = FUN_00684ca0(0);
  if (iVar2 != 0) {
    FUN_0044e880(param_2);
  }
  return;
}

