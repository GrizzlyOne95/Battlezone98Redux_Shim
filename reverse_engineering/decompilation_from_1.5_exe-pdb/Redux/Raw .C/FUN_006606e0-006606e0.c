
void __fastcall FUN_006606e0(int param_1)

{
  float fVar1;
  float10 fVar2;
  float10 fVar3;
  
  if ((*(int *)(param_1 + 0x244) != 0) && (*(int *)(param_1 + 0x244) != 3)) {
    if (*(int *)(param_1 + 0x244) == 1) {
      fVar2 = (float10)FUN_00822d80();
      fVar1 = *(float *)(param_1 + 0x240);
      fVar3 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x23c) = (float)fVar3 - (fVar1 - (float)fVar2);
      *(float *)(param_1 + 0x240) = *(float *)(param_1 + 0x23c) + *(float *)(param_1 + 0x238);
      *(undefined4 *)(param_1 + 0x244) = 3;
    }
    else {
      fVar2 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x23c) = (float)fVar2;
      *(float *)(param_1 + 0x240) = *(float *)(param_1 + 0x23c) + *(float *)(param_1 + 0x238);
      *(undefined4 *)(param_1 + 0x244) = 3;
    }
  }
  return;
}

