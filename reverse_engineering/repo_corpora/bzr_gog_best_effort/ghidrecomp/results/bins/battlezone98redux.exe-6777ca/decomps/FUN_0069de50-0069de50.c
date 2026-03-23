
void __fastcall FUN_0069de50(int param_1)

{
  undefined4 uVar1;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  int local_10;
  int local_c;
  
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  local_18 = (uint)(*(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x88) +
                                     *(int *)(param_1 + 0x40) * 4) + *(int *)(param_1 + 0x44) * 4)
                   == 1);
  if ((((((*(int *)(param_1 + 0x50) != 0) || (*(int *)(param_1 + 0x5c) != 0)) ||
        (*(float *)(param_1 + 100) != 0.0)) ||
       ((*(float *)(param_1 + 0x60) != 0.0 || (*(int *)(param_1 + 0x6c) != 0)))) ||
      ((*(int *)(param_1 + 0x5c) != 0 || ((local_18 != 0 || (*(int *)(param_1 + 0x68) != 0)))))) ||
     (*(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x90) + *(int *)(param_1 + 0x40) * 4) +
              *(int *)(param_1 + 0x44) * 4) != 1)) {
    local_10 = *(int *)(param_1 + 0x6c);
    local_c = *(int *)(param_1 + 0x70);
    if (99 < local_10) {
      local_10 = local_10 + -100;
    }
    if (99 < local_c) {
      local_c = local_c + -100;
    }
    local_1c = (uint)(0.0 < *(float *)(param_1 + 100));
    local_20 = (uint)(0.0 < *(float *)(param_1 + 0x60));
    local_24 = (uint)(0 < *(int *)(param_1 + 0x5c));
    local_28 = (uint)(*(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x90) +
                                       *(int *)(param_1 + 0x40) * 4) + *(int *)(param_1 + 0x44) * 4)
                     == 2);
    *(int *)(param_1 + 0xc) =
         (int)((double)*(int *)(param_1 + 0x54) *
               *(double *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x40) +
               (double)(int)(local_1c * *(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x60))
               + (double)(int)(local_20 * *(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x60)
                              ) +
               (double)(int)(local_24 * *(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x74))
               + (double)(int)(local_18 * *(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x5c)
                              ) +
               (double)(int)(local_28 * *(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x6c))
              + (double)local_c);
    local_2c = (uint)(0.0 < *(float *)(param_1 + 100));
    local_30 = (uint)(0.0 < *(float *)(param_1 + 0x60));
    local_34 = (uint)(0 < *(int *)(param_1 + 0x5c));
    local_38 = (uint)(*(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x90) +
                                       *(int *)(param_1 + 0x40) * 4) + *(int *)(param_1 + 0x44) * 4)
                     == 2);
    ceil((double)*(int *)(param_1 + 0x54) *
         *(double *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x48) +
         (double)(int)(local_2c * *(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 100)) +
         (double)(int)(local_30 * *(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 100)) +
         (double)(int)(local_34 * *(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x70)) +
         (double)(int)(local_18 * *(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x58)) +
         (double)(int)(local_38 * *(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x68)) +
         (double)local_10);
    uVar1 = FUN_0083f040();
    *(undefined4 *)(param_1 + 0x10) = uVar1;
    if (*(int *)(param_1 + 4) == 4) {
      *(undefined4 *)(param_1 + 0x10) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x68);
      *(undefined4 *)(param_1 + 0xc) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x6c);
    }
  }
  return;
}

