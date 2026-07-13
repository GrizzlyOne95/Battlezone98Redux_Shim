
void __fastcall FUN_004c64f0(int param_1)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = FUN_004c7010();
  if (iVar1 != 0) {
    iVar1 = FUN_0049f100();
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0xd4) = 0;
    }
    else {
      if (*(int *)(param_1 + 0xd4) == 0) {
        *(undefined4 *)(param_1 + 0xd4) = 1;
      }
      if ((*(int *)(param_1 + 0xd4) == 4) && (DAT_00919850 == '\0')) {
        *(undefined4 *)(param_1 + 0xd4) = 1;
      }
      iVar1 = FUN_0049f100();
      if (iVar1 == 0) {
        if (*(int *)(param_1 + 0xd4) == 2) {
          *(undefined4 *)(param_1 + 0xd4) = 1;
        }
      }
      else if ((*(int *)(param_1 + 0xd4) == 1) && (DAT_00919850 == '\0')) {
        *(undefined4 *)(param_1 + 0xd4) = 2;
      }
      else if ((*(int *)(param_1 + 0xd4) == 2) && (DAT_00919850 != '\0')) {
        *(undefined4 *)(param_1 + 0xd4) = 4;
      }
      if (*(int *)(param_1 + 0xd4) == 4) {
        *(float *)(param_1 + 0x48) =
             ((float)(DAT_009175a0 - *(int *)(param_1 + 0x70)) * *(float *)(param_1 + 0xb0)) /
             (float)*(int *)(param_1 + 0x80) + *(float *)(param_1 + 0x98);
        *(float *)(param_1 + 0x50) =
             ((float)(*(int *)(param_1 + 0x7c) - DAT_009175a4) * *(float *)(param_1 + 0xb8)) /
             (float)*(int *)(param_1 + 0x84) + *(float *)(param_1 + 0xa0);
        fVar2 = (float10)FUN_007855e0((double)*(float *)(param_1 + 0x48),
                                      (double)*(float *)(param_1 + 0x50));
        *(float *)(param_1 + 0x4c) = (float)fVar2;
      }
      *(undefined ***)(param_1 + 0x14) = &PTR_s_edit_arw_008e81e0;
    }
  }
  FUN_0083e885();
  return;
}

