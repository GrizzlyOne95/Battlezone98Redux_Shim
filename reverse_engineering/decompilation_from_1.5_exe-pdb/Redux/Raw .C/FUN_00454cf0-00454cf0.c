
void FUN_00454cf0(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  float *pfVar4;
  undefined4 *puVar5;
  float *pfVar6;
  float10 fVar7;
  undefined1 local_23c [64];
  undefined1 local_1fc [16];
  undefined4 local_1ec;
  float local_1e8;
  int local_1e4;
  int local_1e0;
  undefined4 local_1dc;
  int local_1d8;
  float local_1d4;
  uint local_1cc;
  int local_1c8;
  float local_1c4;
  uint local_1c0;
  int local_1bc;
  float local_1b8 [4];
  float local_1a8;
  float local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  double local_190;
  double local_188;
  double local_180;
  undefined4 local_178 [16];
  undefined4 local_138 [16];
  undefined4 local_f8 [16];
  undefined4 local_b8 [16];
  float local_78 [22];
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00684ca0();
  if ((iVar1 != 0) && (iVar1 = FUN_004170c0(), iVar1 != 0)) {
    local_1e8 = *(float *)(param_1 + 0x30) / (*(float *)(param_1 + 0x28) * 0.0025);
    FUN_00447e20();
    while( true ) {
      iVar1 = FUN_00447e70();
      FUN_00447e50();
      iVar2 = FUN_00447e70();
      if (iVar1 == iVar2) break;
      local_1e4 = FUN_00447e70();
      local_1c8 = local_1e4;
      FUN_00447e90();
      if (*(char *)(local_1c8 + 0x1c) != '\0') {
        fVar7 = (float10)FUN_00447ed0();
        local_1d4 = (float)fVar7;
        fVar7 = (float10)FUN_004497c0();
        local_1c4 = (float)fVar7;
        puVar3 = (undefined4 *)
                 FUN_006897e0(local_1fc,param_1,*(undefined8 *)(local_1c8 + 0x48),
                              *(undefined8 *)(local_1c8 + 0x50),*(undefined8 *)(local_1c8 + 0x58));
        local_20 = *puVar3;
        local_1c = puVar3[1];
        local_18 = (float)puVar3[2];
        local_14 = local_20;
        local_10 = local_1c;
        local_c = local_18;
        iVar1 = FUN_006895d0();
        if ((iVar1 < 1) && (local_18 <= local_1c4 * local_1e8)) {
          local_1dc = FUN_00449690();
          FUN_006855e0(local_1bc + 0x144,local_18 - local_1c4);
          local_1ec = FUN_00685670(*(undefined4 *)(local_1bc + 0x180),
                                   *(undefined4 *)(local_1bc + 0x188));
          local_1d8 = FUN_006856a0();
          local_1e0 = FUN_006856c0();
          puVar3 = (undefined4 *)
                   FUN_0081ee70(local_23c,*(undefined4 *)(local_1c8 + 0x70),
                                *(undefined4 *)(local_1c8 + 0x74),*(undefined4 *)(local_1c8 + 0x78),
                                0,0,0);
          puVar5 = local_138;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar3 = local_138;
          puVar5 = local_f8;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar3 = (undefined4 *)FUN_0081fe60();
          puVar5 = local_b8;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar3 = local_b8;
          puVar5 = local_178;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          pfVar4 = (float *)FUN_0081fe60();
          pfVar6 = local_78;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *pfVar6 = *pfVar4;
            pfVar4 = pfVar4 + 1;
            pfVar6 = pfVar6 + 1;
          }
          pfVar4 = local_78;
          pfVar6 = local_1b8;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *pfVar6 = *pfVar4;
            pfVar4 = pfVar4 + 1;
            pfVar6 = pfVar6 + 1;
          }
          local_1b8[0] = local_1b8[0] * local_1c4;
          local_1b8[1] = local_1b8[1] * local_1c4;
          local_1b8[2] = local_1b8[2] * local_1c4;
          local_1b8[3] = local_1b8[3] * local_1c4;
          local_1a8 = local_1a8 * local_1c4;
          local_1a4 = local_1a4 * local_1c4;
          local_1a0 = local_1a0 * local_1c4;
          local_19c = local_19c * local_1c4;
          local_198 = local_198 * local_1c4;
          for (local_1c0 = 0; local_1c0 < *(uint *)(local_1bc + 0x180); local_1c0 = local_1c0 + 1) {
            puVar3 = (undefined4 *)
                     FUN_00446360((float)((double)(*(float *)(*(int *)(local_1bc + 0x17c) +
                                                             local_1c0 * 0x18) * local_1b8[0] +
                                                   *(float *)(*(int *)(local_1bc + 0x17c) + 4 +
                                                             local_1c0 * 0x18) * local_1b8[3] +
                                                  *(float *)(*(int *)(local_1bc + 0x17c) + 8 +
                                                            local_1c0 * 0x18) * local_1a0) +
                                         local_190),
                                  (float)((double)(*(float *)(*(int *)(local_1bc + 0x17c) +
                                                             local_1c0 * 0x18) * local_1b8[1] +
                                                   *(float *)(*(int *)(local_1bc + 0x17c) + 4 +
                                                             local_1c0 * 0x18) * local_1a8 +
                                                  *(float *)(*(int *)(local_1bc + 0x17c) + 8 +
                                                            local_1c0 * 0x18) * local_19c) +
                                         local_188),
                                  -(float)((double)(*(float *)(*(int *)(local_1bc + 0x17c) +
                                                              local_1c0 * 0x18) * local_1b8[2] +
                                                    *(float *)(*(int *)(local_1bc + 0x17c) + 4 +
                                                              local_1c0 * 0x18) * local_1a4 +
                                                   *(float *)(*(int *)(local_1bc + 0x17c) + 8 +
                                                             local_1c0 * 0x18) * local_198) +
                                          local_180),local_1dc,
                                  *(undefined4 *)
                                   (*(int *)(local_1bc + 0x17c) + 0x10 + local_1c0 * 0x18),
                                  *(undefined4 *)
                                   (*(int *)(local_1bc + 0x17c) + 0x14 + local_1c0 * 0x18));
            puVar5 = (undefined4 *)(local_1c0 * 0x18 + local_1d8);
            *puVar5 = *puVar3;
            puVar5[1] = puVar3[1];
            puVar5[2] = puVar3[2];
            puVar5[3] = puVar3[3];
            puVar5[4] = puVar3[4];
            puVar5[5] = puVar3[5];
          }
          for (local_1cc = 0; local_1cc < *(uint *)(local_1bc + 0x188); local_1cc = local_1cc + 1) {
            *(short *)(local_1e0 + local_1cc * 2) =
                 *(short *)(*(int *)(local_1bc + 0x184) + local_1cc * 2) + (short)local_1ec;
          }
          FUN_006856e0();
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

