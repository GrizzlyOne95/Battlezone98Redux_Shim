
void FUN_005bd060(float param_1)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  float10 fVar4;
  undefined1 local_110 [64];
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  int local_b0;
  float local_ac [16];
  double local_6c;
  double local_64;
  double local_5c;
  float local_54;
  float local_50;
  float local_4c;
  float local_48 [4];
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00480470(param_1);
  if ((*(uint *)(*(int *)(local_b0 + 0x14) + 0x14) & 8) != 0) {
    if (*(float *)(local_b0 + 0x78) <= param_1 && param_1 != *(float *)(local_b0 + 0x78)) {
      param_1 = *(float *)(local_b0 + 0x78);
    }
    if (*(int *)(local_b0 + 0xec) != 0) {
      local_bc = *(float *)(*(int *)(local_b0 + 0xc) + 0x7c);
      *(float *)(local_b0 + 0xe8) = *(float *)(local_b0 + 0xe8) + param_1;
      while (0.0 < *(float *)(local_b0 + 0xe8)) {
        pfVar1 = (float *)FUN_00444d50(local_110,*(int *)(local_b0 + 0x14) + 0x20,
                                       *(undefined4 *)(local_b0 + 0x3c),
                                       *(undefined4 *)(local_b0 + 0x40),
                                       *(undefined4 *)(local_b0 + 0x44),
                                       *(uint *)(local_b0 + 0xe8) ^ 0x80000000);
        pfVar3 = local_ac;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *pfVar3 = *pfVar1;
          pfVar1 = pfVar1 + 1;
          pfVar3 = pfVar3 + 1;
        }
        pfVar1 = local_ac;
        pfVar3 = local_48;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *pfVar3 = *pfVar1;
          pfVar1 = pfVar1 + 1;
          pfVar3 = pfVar3 + 1;
        }
        local_20 = local_20 - (double)(*(float *)(local_b0 + 0x30) * *(float *)(local_b0 + 0xe8));
        local_18 = local_18 - (double)(*(float *)(local_b0 + 0x34) * *(float *)(local_b0 + 0xe8));
        local_10 = local_10 - (double)(*(float *)(local_b0 + 0x38) * *(float *)(local_b0 + 0xe8));
        local_6c = (double)((*(float *)(*(int *)(local_b0 + 0x14) + 0xb8) - local_bc) * local_30) +
                   local_20;
        local_64 = (double)((*(float *)(*(int *)(local_b0 + 0x14) + 0xb8) - local_bc) * local_2c) +
                   local_18;
        local_5c = (double)((*(float *)(*(int *)(local_b0 + 0x14) + 0xb8) - local_bc) * local_28) +
                   local_10;
        local_c0 = *(float *)(*(int *)(local_b0 + 0xc) + 0x9c);
        iVar2 = *(int *)(local_b0 + 0xc);
        fVar4 = (float10)FUN_004464c0();
        local_c8 = (float)fVar4;
        local_b8 = local_c8 * *(float *)(iVar2 + 0x94);
        iVar2 = *(int *)(local_b0 + 0xc);
        fVar4 = (float10)FUN_004464c0();
        local_d0 = (float)fVar4;
        local_b4 = local_d0 * *(float *)(iVar2 + 0x94);
        iVar2 = *(int *)(local_b0 + 0xc);
        fVar4 = (float10)FUN_004464c0();
        local_cc = (float)fVar4;
        local_c4 = local_cc * *(float *)(iVar2 + 0x98);
        local_54 = local_c0 * *(float *)(local_b0 + 0x30) + local_b8 * local_48[0] +
                   local_b4 * local_48[3] + local_c4 * local_30;
        local_50 = local_c0 * *(float *)(local_b0 + 0x34) + local_b8 * local_48[1] +
                   local_b4 * local_38 + local_c4 * local_2c;
        local_4c = local_c0 * *(float *)(local_b0 + 0x38) + local_b8 * local_48[2] +
                   local_b4 * local_34 + local_c4 * local_28;
        FUN_004910c0(*(undefined4 *)(local_b0 + 0xec),&local_6c,&local_54,
                     *(undefined4 *)(local_b0 + 0xe8));
        *(float *)(local_b0 + 0xe8) =
             *(float *)(local_b0 + 0xe8) - *(float *)(*(int *)(local_b0 + 0xc) + 0xa4);
      }
    }
  }
  FUN_0083e885();
  return;
}

