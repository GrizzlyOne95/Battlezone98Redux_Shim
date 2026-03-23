
void FUN_00452580(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_140 [12];
  undefined1 local_134 [12];
  double local_128;
  double local_120;
  double local_114;
  double local_10c;
  double local_104;
  double local_fc;
  undefined4 local_f4;
  double local_f0;
  undefined4 local_e8;
  int local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  double local_d4;
  int local_cc;
  float local_c8;
  int local_c4;
  float local_c0;
  float local_bc;
  int local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  int local_a8;
  float local_a4;
  int local_a0;
  float local_9c;
  int local_98;
  float local_90;
  int local_8c;
  undefined4 *local_88;
  int local_84;
  float local_80;
  int local_7c;
  int local_78;
  float local_74;
  int local_70;
  int local_6c;
  int local_68;
  float local_64;
  int local_60;
  int local_5c;
  short *local_58;
  short local_54;
  undefined4 local_50;
  undefined4 local_4c;
  uint local_48;
  undefined4 local_2c;
  undefined4 local_28;
  uint local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar2 = FUN_00684ca0();
  if ((iVar2 != 0) && (iVar2 = FUN_004170c0(), iVar2 != 0)) {
    local_dc = *(float *)(param_1 + 0x30) / (*(float *)(param_1 + 0x28) * 0.0025);
    FUN_00447e20();
    while( true ) {
      iVar2 = FUN_00447e70();
      FUN_00447e50();
      iVar3 = FUN_00447e70();
      if (iVar2 == iVar3) break;
      local_e4 = FUN_00447e70();
      local_5c = local_e4;
      FUN_00447e90();
      if (*(char *)(local_5c + 0x1c) != '\0') {
        fVar5 = (float10)FUN_00447ed0();
        local_bc = (float)fVar5;
        fVar5 = (float10)FUN_004497c0();
        local_64 = (float)fVar5;
        puVar4 = (undefined4 *)
                 FUN_006897e0(local_134,param_1,*(undefined8 *)(local_5c + 0x48),
                              *(undefined8 *)(local_5c + 0x50),*(undefined8 *)(local_5c + 0x58));
        local_20 = *puVar4;
        local_1c = puVar4[1];
        local_18 = (float)puVar4[2];
        local_14 = local_20;
        local_10 = local_1c;
        local_c = local_18;
        iVar2 = FUN_006895d0();
        if ((iVar2 < 1) && (local_c <= local_64 * local_dc)) {
          local_e8 = FUN_00449690();
          local_d4 = *(double *)(local_5c + 0x48) - (double)local_64;
          local_104 = (double)local_64 + *(double *)(local_5c + 0x48);
          local_f0 = *(double *)(local_5c + 0x58) - (double)local_64;
          local_fc = (double)local_64 + *(double *)(local_5c + 0x58);
          local_10c = local_d4 * 0.2;
          floor(local_10c);
          local_84 = FUN_0083f040();
          local_114 = local_f0 * 0.2;
          floor(local_114);
          local_7c = FUN_0083f040();
          local_120 = local_104 * 0.2;
          floor(local_120);
          local_6c = FUN_0083f040();
          local_128 = local_fc * 0.2;
          floor(local_128);
          local_68 = FUN_0083f040();
          local_6c = local_6c + 1;
          local_68 = local_68 + 1;
          local_98 = local_6c - local_84;
          local_b8 = local_68 - local_7c;
          local_c4 = (local_98 + 1) * (local_b8 + 1);
          local_cc = local_98 * local_b8 * 6;
          FUN_006855e0(local_60 + 0x144,local_c - local_64);
          local_f4 = FUN_00685670(local_c4,local_cc);
          local_88 = (undefined4 *)FUN_006856a0();
          local_58 = (short *)FUN_006856c0();
          local_9c = DAT_02cc50e0;
          local_c8 = (float)local_84 * DAT_02cc50e0;
          local_b4 = DAT_02cc50e0;
          local_c0 = (float)local_7c * DAT_02cc50e0;
          local_80 = 1.0 / (float)(local_104 - local_d4);
          local_e0 = (float)((double)local_c8 - local_d4) * local_80 + 0.0;
          local_74 = 1.0 / (float)(local_fc - local_f0);
          local_d8 = (float)((double)local_c0 - local_f0) * local_74 + 0.0;
          local_80 = local_80 * DAT_02cc50e0;
          local_74 = local_74 * DAT_02cc50e0;
          local_b0 = local_d8;
          local_90 = local_c0;
          for (local_78 = local_7c; local_78 <= local_68; local_78 = local_78 + 1) {
            local_a4 = local_c8;
            local_ac = local_e0;
            for (local_70 = local_84; local_70 <= local_6c; local_70 = local_70 + 1) {
              iVar2 = FUN_0077d640(local_70,local_78,(double)local_90);
              puVar4 = (undefined4 *)
                       FUN_006897e0(local_140,param_1,(double)local_a4,
                                    (double)((float)iVar2 * 0.1 + *(float *)(local_60 + 0x17c)));
              local_50 = *puVar4;
              local_4c = puVar4[1];
              local_48 = puVar4[2];
              local_2c = local_50;
              local_28 = local_4c;
              local_24 = local_48;
              puVar4 = (undefined4 *)
                       FUN_00446360(local_50,local_4c,local_48 ^ 0x80000000,local_e8,local_ac,
                                    local_b0);
              *local_88 = *puVar4;
              local_88[1] = puVar4[1];
              local_88[2] = puVar4[2];
              local_88[3] = puVar4[3];
              local_88[4] = puVar4[4];
              local_88[5] = puVar4[5];
              local_88 = local_88 + 6;
              local_a4 = local_a4 + local_9c;
              local_ac = local_ac + local_80;
            }
            local_90 = local_90 + local_b4;
            local_b0 = local_b0 + local_74;
          }
          local_54 = (short)local_f4;
          local_8c = local_98 + 1;
          for (local_a8 = local_7c; local_a8 < local_68; local_a8 = local_a8 + 1) {
            for (local_a0 = local_84; local_a0 < local_6c; local_a0 = local_a0 + 1) {
              *local_58 = local_54;
              sVar1 = (short)local_8c;
              local_58[1] = local_54 + 1 + sVar1;
              local_58[2] = local_54 + 1;
              local_58[3] = local_54 + sVar1;
              local_58[4] = local_54 + 1 + sVar1;
              local_58[5] = local_54;
              local_58 = local_58 + 6;
              local_54 = local_54 + 1;
            }
            local_54 = local_54 + 1;
          }
          FUN_006856e0();
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

