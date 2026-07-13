
void __fastcall FUN_00617fa0(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  float10 fVar3;
  
  iVar1 = FUN_00451de0(param_1);
  if (iVar1 == 0) {
    piVar2 = (int *)FUN_004435f0();
    while (piVar2 != (int *)0x0) {
      FUN_00820180(piVar2 + 6,piVar2 + 2,1,*piVar2 + 0x20);
      piVar2 = (int *)FUN_00443650();
    }
    fVar3 = (float10)FUN_00822d60();
    FUN_006111e0((float)fVar3);
    fVar3 = (float10)FUN_00822d60();
    FUN_00583f30((float)fVar3);
    fVar3 = (float10)FUN_00822d60();
    FUN_00611270((float)fVar3);
    iVar1 = FUN_00572a70();
    if (iVar1 != 0) {
      iVar1 = FUN_0056f960();
      if (iVar1 != 0) {
        FUN_005841b0();
      }
    }
    fVar3 = (float10)FUN_00822d60();
    FUN_005840e0((float)fVar3);
  }
  else {
    iVar1 = FUN_00572a70();
    if (iVar1 != 0) {
      FUN_0056f960();
    }
  }
  return;
}

