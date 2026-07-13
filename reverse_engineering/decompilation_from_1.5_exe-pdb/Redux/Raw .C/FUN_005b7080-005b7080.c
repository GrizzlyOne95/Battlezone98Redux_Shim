
void __fastcall FUN_005b7080(int param_1)

{
  undefined4 *puVar1;
  float10 fVar2;
  
  fVar2 = (float10)FUN_00822da0();
  *(float *)(param_1 + 0x18) = (float)fVar2 + 5.0;
  puVar1 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x2c) + 0x18) + 0xc))();
  *(undefined4 *)(param_1 + 0x1c) = *puVar1;
  *(undefined4 *)(param_1 + 0x20) = puVar1[1];
  *(undefined4 *)(param_1 + 0x24) = puVar1[2];
  return;
}

