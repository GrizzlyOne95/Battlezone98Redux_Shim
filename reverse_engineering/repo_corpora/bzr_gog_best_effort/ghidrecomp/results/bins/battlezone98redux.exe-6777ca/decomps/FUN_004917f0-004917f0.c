
void __thiscall FUN_004917f0(int param_1,float param_2)

{
  undefined4 *puVar1;
  float *pfVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined1 local_1e0 [64];
  undefined1 local_1a0 [24];
  undefined1 local_188 [12];
  float local_17c;
  float local_178;
  float local_174;
  int *local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  float local_154;
  float local_150;
  float local_14c;
  float local_148;
  float local_144;
  float local_140;
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  float local_12c;
  int local_128;
  int local_124;
  int *local_120;
  float *local_11c;
  float *local_118;
  float *local_114;
  float local_110;
  int local_10c;
  int local_108;
  undefined4 *local_104;
  float *local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0 [16];
  double local_b0;
  double local_a8;
  double local_a0;
  double local_98;
  double local_90;
  double local_88;
  double local_80;
  double local_78;
  double local_70;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_108 = param_1;
  if (*(int *)(param_1 + 0x802c) != 0) {
    for (local_124 = 0; local_124 < *(int *)(local_108 + 0x8028); local_124 = local_124 + 1) {
      local_120 = (int *)(local_108 + 0x28 + local_124 * 0x20);
      local_10c = *local_120;
      local_104 = (undefined4 *)(local_10c + 0x20);
      puVar1 = (undefined4 *)FUN_00447f60(local_1a0,local_104);
      local_44 = *puVar1;
      local_40 = puVar1[1];
      local_3c = puVar1[2];
      local_38 = puVar1[3];
      local_34 = puVar1[4];
      local_30 = puVar1[5];
      local_100 = (float *)(local_120 + 2);
      local_170 = local_120 + 5;
      local_2c = local_44;
      local_28 = local_40;
      local_24 = local_3c;
      local_20 = local_38;
      local_1c = local_34;
      local_18 = local_30;
      if ((*(uint *)(local_10c + 0x14) & 0x200) == 0) {
        puVar1 = (undefined4 *)
                 FUN_00444d50(local_1e0,local_104,*local_170,local_120[6],local_120[7],param_2);
        puVar6 = local_f0;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar6 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar6 = puVar6 + 1;
        }
        puVar1 = local_f0;
        puVar6 = local_104;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar6 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar6 = puVar6 + 1;
        }
        local_100[1] = local_100[1] - param_2 * 9.8;
        local_110 = param_2;
        iVar3 = FUN_00784620(local_2c,local_28,local_24,local_20,local_1c,local_18,*local_100,
                             local_100[1],local_100[2],&local_110,&local_fc);
        if (iVar3 == 0) {
          *(double *)(local_104 + 10) = (double)(*local_100 * param_2) + *(double *)(local_104 + 10)
          ;
          *(double *)(local_104 + 0xc) =
               (double)(local_100[1] * param_2) + *(double *)(local_104 + 0xc);
          *(double *)(local_104 + 0xe) =
               (double)(local_100[2] * param_2) + *(double *)(local_104 + 0xe);
          if ((*(uint *)(local_10c + 0x14) & 8) != 0) {
            local_118 = (float *)(local_120 + 1);
            *local_118 = *local_118 + param_2;
            while (0.0 < *local_118) {
              *local_118 = *local_118 - *(float *)(local_108 + 0x803c);
              local_80 = *(double *)(local_104 + 10) - (double)(*local_100 * *local_118);
              local_78 = *(double *)(local_104 + 0xc) - (double)(local_100[1] * *local_118);
              local_70 = *(double *)(local_104 + 0xe) - (double)(local_100[2] * *local_118);
              local_144 = *(float *)(local_108 + 0x8048) * *local_100;
              fVar7 = (float10)FUN_004464c0();
              local_148 = (float)fVar7;
              local_68 = local_144 + local_148 * *(float *)(local_108 + 0x8044);
              local_154 = *(float *)(local_108 + 0x8048) * local_100[1];
              fVar7 = (float10)FUN_004464c0();
              local_14c = (float)fVar7;
              local_64 = local_154 + local_14c * *(float *)(local_108 + 0x8044);
              local_168 = *(float *)(local_108 + 0x8048) * local_100[2];
              fVar7 = (float10)FUN_004464c0();
              local_150 = (float)fVar7;
              local_60 = local_168 + local_150 * *(float *)(local_108 + 0x8044);
              FUN_004910c0(*(undefined4 *)(local_108 + 0x802c),&local_80,&local_68,*local_118);
            }
          }
        }
        else {
          *(double *)(local_104 + 10) =
               (double)(*local_100 * local_110) + *(double *)(local_104 + 10);
          *(double *)(local_104 + 0xc) =
               (double)(local_100[1] * local_110) + *(double *)(local_104 + 0xc);
          *(double *)(local_104 + 0xe) =
               (double)(local_100[2] * local_110) + *(double *)(local_104 + 0xe);
          if ((*(uint *)(local_10c + 0x14) & 8) != 0) {
            local_11c = (float *)(local_120 + 1);
            *local_11c = *local_11c + local_110;
            while (0.0 < *local_11c) {
              *local_11c = *local_11c - *(float *)(local_108 + 0x803c);
              local_b0 = *(double *)(local_104 + 10) - (double)(*local_100 * *local_11c);
              local_a8 = *(double *)(local_104 + 0xc) - (double)(local_100[1] * *local_11c);
              local_a0 = *(double *)(local_104 + 0xe) - (double)(local_100[2] * *local_11c);
              local_178 = *(float *)(local_108 + 0x8048) * *local_100;
              fVar7 = (float10)FUN_004464c0();
              local_158 = (float)fVar7;
              local_5c = local_178 + local_158 * *(float *)(local_108 + 0x8044);
              local_138 = *(float *)(local_108 + 0x8048) * local_100[1];
              fVar7 = (float10)FUN_004464c0();
              local_130 = (float)fVar7;
              local_58 = local_138 + local_130 * *(float *)(local_108 + 0x8044);
              local_15c = *(float *)(local_108 + 0x8048) * local_100[2];
              fVar7 = (float10)FUN_004464c0();
              local_140 = (float)fVar7;
              local_54 = local_15c + local_140 * *(float *)(local_108 + 0x8044);
              FUN_004910c0(*(undefined4 *)(local_108 + 0x802c),&local_b0,&local_5c,*local_11c);
            }
          }
          fVar7 = (float10)FUN_004428b0(local_100,&local_fc,local_fc,local_f8,local_f4);
          local_164 = (float)fVar7;
          pfVar2 = (float *)FUN_00459570(local_188,0x3e800000,*local_100,local_100[1],local_100[2],
                                         local_164 * -0.5);
          local_14 = *pfVar2;
          local_10 = pfVar2[1];
          local_c = pfVar2[2];
          *local_100 = local_14;
          local_100[1] = local_10;
          local_100[2] = local_c;
          local_110 = param_2 - local_110;
          *(double *)(local_104 + 10) =
               (double)(*local_100 * local_110) + *(double *)(local_104 + 10);
          *(double *)(local_104 + 0xc) =
               (double)(local_100[1] * local_110) + *(double *)(local_104 + 0xc);
          *(double *)(local_104 + 0xe) =
               (double)(local_100[2] * local_110) + *(double *)(local_104 + 0xe);
          if ((*(uint *)(local_10c + 0x14) & 8) != 0) {
            local_114 = (float *)(local_120 + 1);
            *local_114 = *local_114 + local_110;
            while (0.0 < *local_114) {
              *local_114 = *local_114 - *(float *)(local_108 + 0x803c);
              local_98 = *(double *)(local_104 + 10) - (double)(*local_100 * *local_114);
              local_90 = *(double *)(local_104 + 0xc) - (double)(local_100[1] * *local_114);
              local_88 = *(double *)(local_104 + 0xe) - (double)(local_100[2] * *local_114);
              local_174 = *(float *)(local_108 + 0x8048) * *local_100;
              fVar7 = (float10)FUN_004464c0();
              local_16c = (float)fVar7;
              local_50 = local_174 + local_16c * *(float *)(local_108 + 0x8044);
              local_12c = *(float *)(local_108 + 0x8048) * local_100[1];
              fVar7 = (float10)FUN_004464c0();
              local_17c = (float)fVar7;
              local_4c = local_12c + local_17c * *(float *)(local_108 + 0x8044);
              local_160 = *(float *)(local_108 + 0x8048) * local_100[2];
              fVar7 = (float10)FUN_004464c0();
              local_134 = (float)fVar7;
              local_48 = local_160 + local_134 * *(float *)(local_108 + 0x8044);
              FUN_004910c0(*(undefined4 *)(local_108 + 0x802c),&local_98,&local_50,*local_114);
            }
          }
          fVar7 = (float10)FUN_00453f80(local_100[1]);
          local_13c = (float)fVar7;
          if (local_13c < 0.5) {
            *(uint *)(local_10c + 0x14) = *(uint *)(local_10c + 0x14) | 0x200;
          }
        }
      }
      else {
        if ((*(float *)(local_10c + 0xac) <= 10.0) || (DAT_00917a44 == 0)) {
          if ((*(float *)(local_10c + 0xac) <= 2.0) || (DAT_00917a48 == 0)) {
            if ((0.5 < *(float *)(local_10c + 0xac)) && (DAT_00917a4c != 0)) {
              FUN_004cb7b0(local_104,0);
            }
          }
          else {
            FUN_004cb7b0(local_104,0);
          }
        }
        else {
          FUN_004cb7b0(local_104,0);
        }
        FUN_0062d200(local_10c,"fun3d\\ChunkEffect.cpp");
        local_128 = *(int *)(local_108 + 0x8028) + -1;
        *(int *)(local_108 + 0x8028) = local_128;
        piVar4 = (int *)(local_108 + 0x28 + local_128 * 0x20);
        piVar5 = local_120;
        for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
          *piVar5 = *piVar4;
          piVar4 = piVar4 + 1;
          piVar5 = piVar5 + 1;
        }
        local_124 = local_124 + -1;
      }
    }
  }
  FUN_0083e885();
  return;
}

