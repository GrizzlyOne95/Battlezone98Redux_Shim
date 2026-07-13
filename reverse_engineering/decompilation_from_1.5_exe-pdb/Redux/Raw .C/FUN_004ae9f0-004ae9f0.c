
void __fastcall FUN_004ae9f0(int param_1)

{
  undefined4 uVar1;
  float10 fVar2;
  
  if ((*(int *)(param_1 + 0x298) != 0) && (*(int *)(param_1 + 0x298) != 3)) {
    if (*(int *)(param_1 + 0x298) == 2) {
      fVar2 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x29c) = (float)fVar2;
      *(float *)(param_1 + 0x2a0) = *(float *)(param_1 + 0x29c) + *(float *)(param_1 + 0x294);
    }
    else {
      fVar2 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x2a0) = (float)fVar2 + ((float)fVar2 - *(float *)(param_1 + 0x29c));
      *(float *)(param_1 + 0x29c) = *(float *)(param_1 + 0x2a0) - *(float *)(param_1 + 0x294);
    }
    *(undefined4 *)(param_1 + 0x298) = 3;
    uVar1 = (**(code **)(*(int *)(param_1 + 0x18) + 0x30))(0);
    FUN_004376c0("cloakoff.wav",uVar1);
  }
  return;
}

