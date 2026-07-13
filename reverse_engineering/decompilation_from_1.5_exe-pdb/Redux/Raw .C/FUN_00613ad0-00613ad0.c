
undefined4 __fastcall FUN_00613ad0(int param_1)

{
  undefined4 uVar1;
  float10 extraout_ST0;
  float10 fVar2;
  float10 extraout_ST0_00;
  
  uVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 100) + 0x18) + 0xc))();
  uVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 0xc))(uVar1);
  FUN_00462010(uVar1);
  if ((float)extraout_ST0 < *(float *)(param_1 + 0x68)) {
    fVar2 = (float10)FUN_00822d80();
    FUN_0046d040();
    if ((float)fVar2 - (float)extraout_ST0_00 < 15.0) {
      return 1;
    }
  }
  return 0;
}

