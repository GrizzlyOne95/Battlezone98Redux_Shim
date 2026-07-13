
void FUN_00697290(undefined4 *param_1)

{
  int iVar1;
  float10 fVar2;
  int local_c;
  int local_8;
  
  for (local_8 = 0; local_8 < *(int *)(DAT_00920f04 + 0x80); local_8 = local_8 + 1) {
    for (local_c = 0; local_c < *(int *)(DAT_00920f04 + 0x84); local_c = local_c + 1) {
      iVar1 = *(int *)(*(int *)(param_1[0x20] + local_8 * 4) + local_c * 4);
      fVar2 = (float10)FUN_00822d80();
      if (120.0 < (float)fVar2 - *(float *)(iVar1 + 0x7c)) {
        FUN_00696e40(*param_1,local_c,local_8,0);
      }
    }
  }
  return;
}

