
undefined4 __fastcall FUN_005f7500(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  float10 fVar3;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  
  fVar3 = (float10)FUN_00822d80();
  FUN_0046d040();
  if ((float)fVar3 - (float)extraout_ST0 < 15.0) {
LAB_005f75a3:
    uVar2 = 1;
  }
  else {
    cVar1 = (**(code **)(**(int **)(param_1 + 0x34) + 0x68))();
    if (cVar1 != '\0') {
      uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x60) + 0x18) + 0xc))();
      uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 0xc))(uVar2);
      FUN_00462010(uVar2);
      if ((float)extraout_ST0_00 < *(float *)(param_1 + 0x6c)) goto LAB_005f75a3;
    }
    uVar2 = FUN_005f7470();
  }
  return uVar2;
}

