
void __fastcall FUN_00618060(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined4 uVar4;
  
  iVar1 = FUN_00451de0(param_1);
  if (iVar1 == 0) {
    FUN_0062bc80();
    if (0 < DAT_00920c58) {
      FUN_0062b6b0();
    }
    FUN_0062cc50();
    FUN_0062bdb0();
    if (DAT_008eaad0 != (code *)0x0) {
      (*DAT_008eaad0)();
    }
    FUN_004dfad0();
    FUN_005c5920();
    FUN_004dfbf0();
    fVar3 = (float10)FUN_00822d60();
    FUN_004d4580((float)fVar3);
    FUN_004b6ef0();
  }
  else {
    iVar1 = FUN_0062c840();
    if (iVar1 != 0) {
      puVar2 = (undefined4 *)FUN_0062c840();
      uVar4 = *puVar2;
      FUN_004df7b0(uVar4);
      FUN_004deec0(uVar4);
    }
    FUN_0062bd00();
    FUN_0062cc50();
    if (DAT_008eaad0 != (code *)0x0) {
      (*DAT_008eaad0)();
    }
    FUN_004dfad0();
    FUN_005c5920();
    FUN_004dfd70();
    fVar3 = (float10)FUN_00822d60();
    FUN_005ba150((float)fVar3);
    FUN_004b6ef0();
  }
  return;
}

