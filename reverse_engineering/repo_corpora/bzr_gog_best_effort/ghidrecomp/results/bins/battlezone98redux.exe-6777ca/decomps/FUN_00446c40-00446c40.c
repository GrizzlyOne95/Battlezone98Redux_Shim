
void FUN_00446c40(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  float *pfVar4;
  float *pfVar5;
  float10 fVar6;
  undefined1 local_160 [16];
  int local_150;
  float local_14c;
  undefined4 local_148;
  int local_144;
  float local_140;
  int local_13c;
  uint local_138;
  int local_130;
  uint local_12c;
  float local_128;
  int local_124;
  undefined4 local_120;
  int local_11c;
  uint local_118;
  int local_114;
  undefined4 *local_110;
  float local_10c;
  short local_108;
  short *local_104;
  float local_100 [4];
  float local_f0;
  float local_ec;
  double local_d8;
  double local_d0;
  double local_c8;
  float local_c0 [40];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00684ca0();
  if (iVar1 != 0) {
    fVar6 = (float10)FUN_00822da0();
    local_14c = (float)fVar6;
    fVar6 = (float10)FUN_00446290(local_14c * *(float *)(local_114 + 400));
    local_128 = (float)fVar6;
    FUN_00447e20();
    while( true ) {
      iVar1 = FUN_00447e70();
      FUN_00447e50();
      iVar2 = FUN_00447e70();
      if (iVar1 == iVar2) break;
      local_150 = FUN_00447e70();
      local_124 = local_150;
      FUN_00447e90();
      local_118 = *(uint *)(local_124 + 0x74);
      if (1 < local_118) {
        local_130 = *(int *)(*(int *)(local_124 + 0x70) + -4 + local_118 * 4);
        puVar3 = (undefined4 *)
                 FUN_006897e0(local_160,param_1,*(undefined8 *)(local_130 + 0x28),
                              *(undefined8 *)(local_130 + 0x30),*(undefined8 *)(local_130 + 0x38));
        local_20 = *puVar3;
        local_1c = puVar3[1];
        local_18 = puVar3[2];
        local_14 = local_20;
        local_10 = local_1c;
        local_c = local_18;
        FUN_006855e0(local_114 + 0x144,local_18);
        local_144 = local_118 << 2;
        local_13c = (local_118 - 1) * 0xc;
        local_148 = FUN_00685670(local_144,local_13c);
        local_110 = (undefined4 *)FUN_006856a0();
        local_104 = (short *)FUN_006856c0();
        fVar6 = (float10)FUN_00447ed0();
        local_140 = (float)fVar6;
        fVar6 = (float10)FUN_004497c0();
        local_10c = (float)fVar6;
        local_120 = FUN_00449690();
        for (local_12c = 0; local_12c < local_118; local_12c = local_12c + 1) {
          local_11c = *(int *)(*(int *)(local_124 + 0x70) + local_12c * 4);
          pfVar4 = (float *)FUN_0081fe60();
          pfVar5 = local_c0;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *pfVar5 = *pfVar4;
            pfVar4 = pfVar4 + 1;
            pfVar5 = pfVar5 + 1;
          }
          pfVar4 = local_c0;
          pfVar5 = local_100;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *pfVar5 = *pfVar4;
            pfVar4 = pfVar4 + 1;
            pfVar5 = pfVar5 + 1;
          }
          puVar3 = (undefined4 *)
                   FUN_00446360((float)((double)(local_10c * local_100[3]) + local_d8),
                                (float)((double)(local_10c * local_f0) + local_d0),
                                -(float)((double)(local_10c * local_ec) + local_c8),local_120,
                                local_128 + *(float *)(local_11c + 0x40),0);
          *local_110 = *puVar3;
          local_110[1] = puVar3[1];
          local_110[2] = puVar3[2];
          local_110[3] = puVar3[3];
          local_110[4] = puVar3[4];
          local_110[5] = puVar3[5];
          local_110 = local_110 + 6;
          puVar3 = (undefined4 *)
                   FUN_00446360((float)(local_d8 - (double)(local_10c * local_100[3])),
                                (float)(local_d0 - (double)(local_10c * local_f0)),
                                -(float)(local_c8 - (double)(local_10c * local_ec)),local_120,
                                local_128 + *(float *)(local_11c + 0x40),0x3f800000);
          *local_110 = *puVar3;
          local_110[1] = puVar3[1];
          local_110[2] = puVar3[2];
          local_110[3] = puVar3[3];
          local_110[4] = puVar3[4];
          local_110[5] = puVar3[5];
          local_110 = local_110 + 6;
          puVar3 = (undefined4 *)
                   FUN_00446360((float)((double)(local_10c * local_100[0]) + local_d8),
                                (float)((double)(local_10c * local_100[1]) + local_d0),
                                -(float)((double)(local_10c * local_100[2]) + local_c8),local_120,
                                local_128 + *(float *)(local_11c + 0x40) + 0.5,0);
          *local_110 = *puVar3;
          local_110[1] = puVar3[1];
          local_110[2] = puVar3[2];
          local_110[3] = puVar3[3];
          local_110[4] = puVar3[4];
          local_110[5] = puVar3[5];
          local_110 = local_110 + 6;
          puVar3 = (undefined4 *)
                   FUN_00446360((float)(local_d8 - (double)(local_10c * local_100[0])),
                                (float)(local_d0 - (double)(local_10c * local_100[1])),
                                -(float)(local_c8 - (double)(local_10c * local_100[2])),local_120,
                                local_128 + *(float *)(local_11c + 0x40) + 0.5,0x3f800000);
          *local_110 = *puVar3;
          local_110[1] = puVar3[1];
          local_110[2] = puVar3[2];
          local_110[3] = puVar3[3];
          local_110[4] = puVar3[4];
          local_110[5] = puVar3[5];
          local_110 = local_110 + 6;
        }
        local_108 = (short)local_148;
        for (local_138 = 0; local_138 < local_118 - 1; local_138 = local_138 + 1) {
          *local_104 = local_108;
          local_104[1] = local_108 + 1;
          local_104[2] = local_108 + 4;
          local_104[3] = local_108 + 5;
          local_104[4] = local_108 + 4;
          local_104[5] = local_108 + 1;
          local_104[6] = local_108 + 2;
          local_104[7] = local_108 + 3;
          local_104[8] = local_108 + 6;
          local_104[9] = local_108 + 7;
          local_104[10] = local_108 + 6;
          local_104[0xb] = local_108 + 3;
          local_104 = local_104 + 0xc;
          local_108 = local_108 + 4;
        }
        FUN_006856e0();
      }
    }
  }
  FUN_0083e885();
  return;
}

