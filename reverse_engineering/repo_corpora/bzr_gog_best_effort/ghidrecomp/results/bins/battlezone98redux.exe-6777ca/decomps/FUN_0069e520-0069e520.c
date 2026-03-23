
float10 __fastcall FUN_0069e520(int param_1)

{
  float fVar1;
  uint local_14;
  uint local_10;
  uint local_c;
  
  fVar1 = (float)*(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x88) +
                                  *(int *)(param_1 + 0x40) * 4) + *(int *)(param_1 + 0x44) * 4);
  if (((((*(int *)(param_1 + 0x50) == 0) && (*(float *)(param_1 + 100) == 0.0)) &&
       (*(int *)(param_1 + 0x5c) == 0)) &&
      ((*(float *)(param_1 + 0x60) == 0.0 && (*(int *)(param_1 + 0x68) == 0)))) &&
     ((fVar1 != 1.0 &&
      (*(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x90) + *(int *)(param_1 + 0x40) * 4) +
               *(int *)(param_1 + 0x44) * 4) == 1)))) {
    *(undefined4 *)(param_1 + 0x20) = 0xce6e6b28;
    *(undefined4 *)(param_1 + 4) = 0;
    fVar1 = *(float *)(param_1 + 0x20);
  }
  else {
    if ((*(int *)(*(int *)(param_1 + 0x38) + 0x90) == 0) &&
       (*(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x90) + *(int *)(param_1 + 0x40) * 4)
                + *(int *)(param_1 + 0x44) * 4) == 0)) {
      fVar1 = (float)*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0xc) * fVar1 +
              (float)*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x20);
    }
    else {
      local_c = (uint)(*(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x90) +
                                        *(int *)(param_1 + 0x40) * 4) + *(int *)(param_1 + 0x44) * 4
                               ) == 2);
      local_10 = (uint)(*(int *)(param_1 + 0x14) != 0);
      local_14 = (uint)(*(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x88) +
                                         *(int *)(param_1 + 0x40) * 4) +
                                *(int *)(param_1 + 0x44) * 4) == 1);
      fVar1 = (float)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 8) *
                     *(int *)(param_1 + 0x48)) +
              (float)*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0xc) * fVar1 +
              (float)*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x14) *
              *(float *)(param_1 + 100) +
              (float)*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x18) *
              *(float *)(param_1 + 0x60) +
              (float)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x2c) *
                     *(int *)(param_1 + 0x5c)) +
              (float)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x24) *
                     *(int *)(param_1 + 0x68)) +
              (float)(int)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x20) * local_c) +
              (float)(int)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x1c) * local_10) +
              (float)(int)(*(int *)(*(int *)(*(int *)(param_1 + 0x3c) + 0x60) + 0x28) * local_14);
    }
    *(float *)(param_1 + 0x20) = fVar1;
    fVar1 = *(float *)(param_1 + 0x20);
  }
  return (float10)fVar1;
}

