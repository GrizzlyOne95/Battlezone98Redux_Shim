
void __fastcall FUN_0045bf90(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  float10 fVar3;
  
  FUN_0049b1f0(param_1);
  if (DAT_0260d10c == (int *)0x0) {
    DAT_0260d10c = (int *)FUN_0045ca50();
  }
  (**(code **)(*DAT_0260d10c + 0x30))();
  (**(code **)(*DAT_0260d10c + 0x34))();
  iVar2 = FUN_00572a70();
  if (iVar2 == 0) {
    iVar2 = FUN_00417c70();
    if (iVar2 != 0) {
      FUN_00417c70();
      iVar2 = FUN_0045bdf0();
      if (iVar2 != 0) {
        return;
      }
    }
    cVar1 = FUN_0045be10();
    if (cVar1 == '\0') {
      fVar3 = (float10)FUN_00822d80(0);
      FUN_0045c0f0((float)fVar3 + 10.0);
    }
  }
  return;
}

