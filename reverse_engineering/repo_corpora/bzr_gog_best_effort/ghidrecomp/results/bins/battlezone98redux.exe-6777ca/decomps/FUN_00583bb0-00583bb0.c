
undefined4 __fastcall FUN_00583bb0(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  float10 fVar3;
  float10 fVar4;
  
  piVar1 = (int *)(param_1 + 0x60);
  if ((*piVar1 != 0) && (*(int *)(param_1 + 100) != *piVar1)) {
    uVar2 = (**(code **)(*(int *)(*piVar1 + 0x18) + 0xc))();
    uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 0xc))(uVar2);
    fVar3 = (float10)FUN_00462010(uVar2);
    if (*(float *)(param_1 + 0x70) <= (float)fVar3 && (float)fVar3 != *(float *)(param_1 + 0x70)) {
      fVar3 = (float10)FUN_00822d80();
      fVar4 = (float10)FUN_0046d040();
      if ((float)fVar3 - (float)fVar4 < *(float *)(param_1 + 0x74)) {
        return 1;
      }
    }
  }
  return 0;
}

