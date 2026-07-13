
void __fastcall FUN_007787d0(int param_1)

{
  float *pfVar1;
  float fVar2;
  undefined4 local_10;
  undefined4 local_c;
  
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
      pfVar1 = (float *)(param_1 + 0x280 + local_c * 0x40 + local_10 * 0x10);
      if (*pfVar1 <= *(float *)(param_1 + 0x380) && *(float *)(param_1 + 0x380) != *pfVar1) {
        *(undefined4 *)(param_1 + 0x380) =
             *(undefined4 *)(param_1 + 0x280 + local_c * 0x40 + local_10 * 0x10);
      }
      fVar2 = *(float *)(param_1 + local_c * 0x40 + 0x288 + local_10 * 0x10);
      if (*(float *)(param_1 + 0x388) <= fVar2 && fVar2 != *(float *)(param_1 + 0x388)) {
        *(undefined4 *)(param_1 + 0x388) =
             *(undefined4 *)(param_1 + local_c * 0x40 + 0x288 + local_10 * 0x10);
      }
      pfVar1 = (float *)(param_1 + local_c * 0x40 + 0x284 + local_10 * 0x10);
      if (*pfVar1 <= *(float *)(param_1 + 900) && *(float *)(param_1 + 900) != *pfVar1) {
        *(undefined4 *)(param_1 + 900) =
             *(undefined4 *)(param_1 + local_c * 0x40 + 0x284 + local_10 * 0x10);
      }
      fVar2 = *(float *)(param_1 + local_c * 0x40 + 0x28c + local_10 * 0x10);
      if (*(float *)(param_1 + 0x38c) <= fVar2 && fVar2 != *(float *)(param_1 + 0x38c)) {
        *(undefined4 *)(param_1 + 0x38c) =
             *(undefined4 *)(param_1 + local_c * 0x40 + 0x28c + local_10 * 0x10);
      }
    }
  }
  return;
}

