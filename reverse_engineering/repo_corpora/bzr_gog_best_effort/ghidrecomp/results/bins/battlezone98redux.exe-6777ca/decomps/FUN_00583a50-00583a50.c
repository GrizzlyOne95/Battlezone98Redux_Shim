
bool __fastcall FUN_00583a50(int param_1)

{
  undefined4 uVar1;
  float10 extraout_ST0;
  
  uVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 100) + 0x18) + 0xc))();
  uVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 0xc))(uVar1);
  FUN_00462010(uVar1);
  return (float)extraout_ST0 < *(float *)(param_1 + 0x68);
}

