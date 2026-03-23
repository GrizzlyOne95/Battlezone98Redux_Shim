
/* WARNING: Removing unreachable block (ram,0x0045a59b) */

void FUN_0045a060(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  float10 fVar3;
  undefined8 uVar4;
  undefined1 local_14c [12];
  undefined1 local_140 [12];
  undefined4 local_134;
  undefined8 local_130;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float *local_114;
  undefined8 local_110;
  float local_108;
  undefined4 local_104;
  undefined4 local_100;
  int local_fc;
  uint local_f8;
  undefined4 local_f4;
  float local_ec;
  float local_e8;
  int local_e4;
  uint local_e0;
  undefined4 *local_dc;
  short *local_d8;
  float local_d4;
  float local_d0;
  undefined4 local_cc;
  float local_c8;
  float local_c4;
  undefined4 local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_f8 = get();
  if (local_f8 != 0) {
    local_120 = *(float *)(param_1 + 0x30) / (*(float *)(param_1 + 0x28) * 0.0025);
    local_114 = (float *)FUN_0045ba30();
    local_b0 = *local_114;
    local_ac = local_114[1];
    local_a8 = local_114[2];
    local_a4 = *local_114;
    local_a0 = local_114[1];
    local_9c = local_114[2];
    for (local_e0 = 1; local_e0 < local_f8; local_e0 = local_e0 + 1) {
      local_f4 = FUN_0045ba30();
      fVar3 = (float10)FUN_00456080();
      local_b0 = (float)fVar3;
      fVar3 = (float10)FUN_0044fb20();
      local_a4 = (float)fVar3;
      fVar3 = (float10)FUN_00456080();
      local_ac = (float)fVar3;
      fVar3 = (float10)FUN_0044fb20();
      local_a0 = (float)fVar3;
      fVar3 = (float10)FUN_00456080();
      local_a8 = (float)fVar3;
      fVar3 = (float10)FUN_0044fb20();
      local_9c = (float)fVar3;
    }
    puVar1 = (undefined4 *)FUN_00459570(local_140,0x3f000000,local_a4,local_a0,local_9c,0x3f000000);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
    puVar1 = (undefined4 *)FUN_00459570(local_14c,0x3f000000,local_a4,local_a0,local_9c,0xbf000000);
    local_38 = *puVar1;
    local_34 = puVar1[1];
    local_30 = puVar1[2];
    local_2c = local_38;
    local_28 = local_34;
    local_24 = local_30;
    fVar3 = (float10)FUN_004428b0();
    local_11c = (float)fVar3;
    local_e8 = local_11c + 1.1754944e-38;
    fVar3 = (float10)FUN_00820570();
    local_128 = (float)fVar3;
    local_e8 = local_128 * local_e8;
    local_124 = local_128;
    fVar3 = (float10)FUN_0044fb20();
    local_118 = (float)fVar3;
    local_e8 = local_118 + local_e8;
    FUN_00820180(&local_14);
    iVar2 = FUN_006895d0();
    if (iVar2 < 1) {
      FUN_006855e0();
      local_e4 = FUN_00685670();
      local_dc = (undefined4 *)FUN_006856a0();
      local_d8 = (short *)FUN_006856c0();
      local_134 = 2;
      local_fc = 0;
      for (local_e0 = 0; local_e0 < local_f8; local_e0 = local_e0 + 1) {
        local_104 = FUN_0045ba30();
        fVar3 = (float10)FUN_00447ed0();
        local_108 = (float)fVar3;
        fVar3 = (float10)FUN_004497c0();
        local_ec = (float)fVar3;
        FUN_00820180(&local_bc);
        if (local_b4 <= local_ec * local_120) {
          local_100 = FUN_00449690();
          uVar4 = FUN_008205a0();
          local_c4 = (float)((ulonglong)uVar4 >> 0x20);
          local_d4 = local_ec * local_c4;
          local_d0 = local_ec * (float)uVar4;
          local_cc = 0;
          local_c8 = -local_ec * (float)uVar4;
          local_c4 = local_ec * local_c4;
          local_c0 = 0;
          local_fc = local_fc + 1;
          local_130 = uVar4;
          local_110 = uVar4;
          puVar1 = (undefined4 *)
                   FUN_00446360((local_bc - local_d4) + local_c8,(local_b8 - local_d0) + local_c4,
                                -local_b4);
          *local_dc = *puVar1;
          local_dc[1] = puVar1[1];
          local_dc[2] = puVar1[2];
          local_dc[3] = puVar1[3];
          local_dc[4] = puVar1[4];
          local_dc[5] = puVar1[5];
          local_dc = local_dc + 6;
          puVar1 = (undefined4 *)
                   FUN_00446360(local_bc + local_d4 + local_c8,local_b8 + local_d0 + local_c4,
                                -local_b4);
          *local_dc = *puVar1;
          local_dc[1] = puVar1[1];
          local_dc[2] = puVar1[2];
          local_dc[3] = puVar1[3];
          local_dc[4] = puVar1[4];
          local_dc[5] = puVar1[5];
          local_dc = local_dc + 6;
          puVar1 = (undefined4 *)
                   FUN_00446360((local_bc + local_d4) - local_c8,(local_b8 + local_d0) - local_c4,
                                -local_b4);
          *local_dc = *puVar1;
          local_dc[1] = puVar1[1];
          local_dc[2] = puVar1[2];
          local_dc[3] = puVar1[3];
          local_dc[4] = puVar1[4];
          local_dc[5] = puVar1[5];
          local_dc = local_dc + 6;
          puVar1 = (undefined4 *)
                   FUN_00446360((local_bc - local_d4) - local_c8,(local_b8 - local_d0) - local_c4,
                                -local_b4);
          *local_dc = *puVar1;
          local_dc[1] = puVar1[1];
          local_dc[2] = puVar1[2];
          local_dc[3] = puVar1[3];
          local_dc[4] = puVar1[4];
          local_dc[5] = puVar1[5];
          local_dc = local_dc + 6;
          *local_d8 = (short)local_e4;
          local_d8[1] = (short)local_e4 + 2;
          local_d8[2] = (short)local_e4 + 1;
          local_d8[3] = (short)local_e4;
          local_d8[4] = (short)local_e4 + 3;
          local_d8[5] = (short)local_e4 + 2;
          local_d8 = local_d8 + 6;
          local_e4 = local_e4 + 4;
        }
      }
      FUN_006856a0();
      FUN_006856c0();
      FUN_006856e0();
    }
  }
  FUN_0083e885();
  return;
}

