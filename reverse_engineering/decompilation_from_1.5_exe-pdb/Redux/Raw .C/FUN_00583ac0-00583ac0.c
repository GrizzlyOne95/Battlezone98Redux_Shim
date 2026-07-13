
undefined4 __fastcall FUN_00583ac0(int param_1)

{
  undefined4 uVar1;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  
  if (*(int *)(param_1 + 0x60) != 0) {
    uVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x60) + 0x18) + 0xc))();
    uVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 0xc))(uVar1);
    FUN_00462010(uVar1);
    if ((float)extraout_ST0 < *(float *)(param_1 + 0x6c)) {
      uVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 100) + 0x18) + 0xc))();
      uVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 0xc))(uVar1);
      FUN_00462010(uVar1);
      if ((float)extraout_ST0_00 < *(float *)(param_1 + 0x68)) {
        return 1;
      }
    }
  }
  return 0;
}

