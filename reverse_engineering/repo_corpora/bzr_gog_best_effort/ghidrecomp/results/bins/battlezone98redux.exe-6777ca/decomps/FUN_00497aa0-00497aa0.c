
void FUN_00497aa0(void)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  float10 fVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined1 local_224 [12];
  undefined1 local_218 [32];
  undefined8 local_1f8;
  undefined8 local_1f0;
  undefined8 local_1e8;
  undefined8 local_1e0;
  undefined8 local_1d8;
  undefined8 local_1d0;
  undefined8 local_1c8;
  undefined8 local_1c0;
  undefined8 local_1b8;
  undefined8 local_1b0;
  undefined8 local_1a8;
  undefined8 local_1a0;
  float local_194;
  float local_188;
  uint local_184;
  undefined4 local_180;
  float local_174;
  float local_16c;
  undefined8 local_164;
  float local_154;
  float local_150;
  int local_14c;
  float local_148;
  undefined8 local_144;
  int local_13c;
  undefined8 local_138;
  float local_130;
  undefined8 local_12c;
  undefined8 local_124;
  undefined8 local_11c;
  undefined4 local_114;
  undefined4 local_110;
  float local_10c;
  undefined4 local_108;
  uint local_104;
  uint local_100;
  int local_fc;
  int *local_f8;
  undefined8 local_f4;
  int local_ec;
  undefined4 local_e8;
  float local_e4;
  uint local_e0;
  int local_dc;
  int local_d8;
  float local_d4;
  int local_d0;
  int local_cc;
  int local_c8;
  int local_c4;
  float local_c0;
  undefined4 local_bc;
  int local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  char local_aa;
  char local_a9;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  ulong local_98;
  int local_94;
  int local_90;
  char local_8a;
  char local_89;
  undefined8 local_88;
  char local_7e;
  char local_7d;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
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
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_a8 = FUN_00417c70();
  if (local_a8 != 0) {
    local_14c = FUN_00462610();
    FUN_00422170();
    puVar2 = (undefined4 *)FID_conflict_begin();
    local_bc = *puVar2;
    while( true ) {
      FID_conflict_end();
      cVar1 = FID_conflict_operator__();
      if (cVar1 == '\0') break;
      piVar3 = (int *)FUN_00421ec0();
      local_90 = *piVar3;
      if (local_90 == local_a8) {
        iVar4 = FUN_004978d0();
        if (iVar4 != 0) goto LAB_00497b73;
      }
      else {
LAB_00497b73:
        local_a9 = FUN_004db510();
        if (local_a9 == '\0') {
LAB_00497bb4:
          local_108 = 0;
        }
        else {
          cVar1 = FUN_00492d20();
          if (cVar1 == '\0') goto LAB_00497bb4;
          local_108 = 1;
        }
        local_7e = (char)local_108;
        local_89 = FUN_0046fbf0();
        local_7d = local_90 == local_14c;
        local_100 = (uint)(byte)local_7d;
        fVar6 = (float10)FUN_00822da0();
        local_194 = (float)fVar6;
        local_174 = local_194;
        fVar6 = (float10)FUN_00497890();
        local_150 = (float)fVar6;
        local_8a = local_194 < local_150 + 2.0;
        local_e0 = (uint)(byte)local_8a;
        FUN_004978b0();
        local_94 = FUN_0081cb40();
        puVar2 = (undefined4 *)(**(code **)(*(int *)(local_90 + 0x18) + 0xc))();
        local_70 = *puVar2;
        local_6c = puVar2[1];
        local_68 = puVar2[2];
        lVar7 = FUN_00497780();
        local_164 = lVar7;
        local_88 = lVar7;
        local_98 = FUN_00492ce0();
        local_a4 = (*(int *)(DAT_00917580 + 8) + 1 + *(int *)(DAT_00917580 + 0x10)) / 2;
        local_a0 = (*(int *)(DAT_00917580 + 0xc) + 1 + *(int *)(DAT_00917580 + 0x14)) / 2;
        local_b0 = 0;
        uVar5 = local_a4 - (int)local_88 >> 0x1f;
        iVar4 = (*(int *)(DAT_00917580 + 0x10) - *(int *)(DAT_00917580 + 8)) + 1;
        if (((int)((local_a4 - (int)local_88 ^ uVar5) - uVar5) <
             (int)(iVar4 + (iVar4 >> 0x1f & 7U)) >> 3) &&
           (uVar5 = local_a0 - local_88._4_4_ >> 0x1f,
           iVar4 = (*(int *)(DAT_00917580 + 0x14) - *(int *)(DAT_00917580 + 0xc)) + 1,
           (int)((local_a0 - local_88._4_4_ ^ uVar5) - uVar5) <
           (int)(iVar4 + (iVar4 >> 0x1f & 3U)) >> 2)) {
          local_110 = 1;
        }
        else {
          local_110 = 0;
        }
        local_aa = (char)local_110;
        lVar7 = local_88;
        if ((((local_89 == '\0') && (local_7d == '\0')) && (local_7e == '\0')) && (local_8a == '\0')
           ) {
          if (((local_10c < 0.0) || ((int)local_88 < 0)) ||
             ((*(int *)(DAT_00917580 + 0x10) < (int)local_88 ||
              ((local_88 < 0 || (*(int *)(DAT_00917580 + 0x14) < local_88._4_4_)))))) {
            local_b0 = 1;
          }
        }
        else {
          if (local_88._4_4_ < *(int *)(DAT_00917580 + 0xc)) {
            local_b0 = 2;
            lVar7 = CONCAT44(*(undefined4 *)(DAT_00917580 + 0xc),
                             (((int)local_88 - local_a4) * local_a0) / (local_a0 - local_88._4_4_) +
                             local_a4);
          }
          else if (*(int *)(DAT_00917580 + 0x14) < local_88._4_4_) {
            local_b0 = 3;
            lVar7 = CONCAT44(*(undefined4 *)(DAT_00917580 + 0x14),
                             (((int)local_88 - local_a4) * local_a0) / (local_88._4_4_ - local_a0) +
                             local_a4);
          }
          local_88._4_4_ = (int)((ulonglong)lVar7 >> 0x20);
          local_88._0_4_ = (int)lVar7;
          if ((int)local_88 < *(int *)(DAT_00917580 + 8)) {
            local_b0 = 4;
            lVar7 = (ulonglong)
                    (uint)(((local_88._4_4_ - local_a0) * local_a4) / (local_a4 - (int)local_88) +
                          local_a0) << 0x20;
          }
          else if (*(int *)(DAT_00917580 + 0x10) < (int)local_88) {
            local_b0 = 5;
            lVar7 = CONCAT44(((local_88._4_4_ - local_a0) * local_a4) / ((int)local_88 - local_a4) +
                             local_a0,*(undefined4 *)(DAT_00917580 + 0x10));
          }
        }
        local_e8 = local_b0;
        local_88 = lVar7;
        switch(local_b0) {
        case 0:
          iVar4 = FUN_00462400();
          local_c0 = *(float *)(iVar4 + 0xc);
          local_fc = (int)(local_10c * local_c0);
          iVar4 = FUN_004978d0();
          if ((iVar4 != 0) && (0.0 < *(float *)(local_90 + 0xe8))) {
            iVar4 = FUN_008445c0();
            local_104 = iVar4 << 0x18 | local_98 & 0xffffff;
            local_180 = FUN_0047fed0();
            puVar2 = (undefined4 *)FUN_00462490();
            local_7c = *puVar2;
            local_78 = puVar2[1];
            local_74 = puVar2[2];
            puVar2 = (undefined4 *)FUN_00439d00(local_218,local_70,local_6c,local_68,local_c0);
            local_58 = *puVar2;
            local_54 = puVar2[1];
            local_50 = puVar2[2];
            local_40 = local_58;
            local_3c = local_54;
            local_38 = local_50;
            puVar2 = (undefined4 *)FUN_00439d00(local_224,local_70,local_6c,local_68,local_c0 + 5.0)
            ;
            local_4c = *puVar2;
            local_48 = puVar2[1];
            local_44 = puVar2[2];
            local_34 = local_4c;
            local_30 = local_48;
            local_2c = local_44;
            uVar8 = FUN_00497780();
            local_144 = uVar8;
            local_124 = uVar8;
            uVar8 = FUN_00497780();
            local_188 = DAT_00920ef4;
            DAT_00920ef4 = DAT_00920ef4 + 1.0;
            local_138 = uVar8;
            local_12c = uVar8;
            FUN_0068af40(DAT_00917580,local_144,(int)uVar8);
            FUN_0068ad00(DAT_00917580,local_88,local_fc);
            DAT_00920ef4 = local_188;
          }
          if ((((local_7d != '\0') || (local_89 != '\0')) || (local_7e != '\0')) ||
             (local_8a != '\0')) {
            std::_Init_atomic_counter(DAT_0091552c,local_98);
            FUN_00417990();
            if (local_7e != '\0') {
              FUN_0068c560(DAT_00917580,*(undefined4 *)(local_9c + 0xc),(int)local_88);
            }
            if ((local_7d != '\0') || (local_8a != '\0')) {
              FUN_0068c560(DAT_00917580,*(undefined4 *)(local_9c + 0x10),(int)local_88);
            }
            if (local_89 != '\0') {
              FUN_0068c560(DAT_00917580,*(undefined4 *)(local_9c + 8),(int)local_88);
            }
            local_ec = 0;
            if ((((local_7d != '\0') || (local_7e != '\0')) || (local_89 != '\0')) &&
               (local_94 != 0)) {
              FUN_00689ab0(DAT_0091552c);
              uVar8 = FUN_00689eb0();
              local_1b0 = uVar8;
              FUN_00689d10(DAT_0091552c,DAT_00917580);
              local_ec = (int)local_e4;
            }
            if ((((local_7d != '\0') || (local_7e != '\0')) || (local_89 != '\0')) ||
               (local_8a != '\0')) {
              cVar1 = FUN_00571c40();
              if (cVar1 != '\0') {
                iVar4 = (**(code **)(*(int *)(local_90 + 0x18) + 4))();
                if (0 < iVar4) {
                  iVar4 = (**(code **)(*(int *)(local_90 + 0x18) + 4))();
                  local_cc = *(int *)(&DAT_009180e8 + iVar4 * 4);
                  if (local_cc != 0) {
                    FUN_0041f870();
                    FUN_00689ab0(DAT_0091552c);
                    FUN_0041f870();
                    FUN_00689d10(DAT_0091552c,DAT_00917580);
                  }
                }
              }
            }
            puVar2 = (undefined4 *)(**(code **)(*(int *)(local_a8 + 0x18) + 0xc))();
            FUN_004976f0(*puVar2,puVar2[1],puVar2[2]);
            local_114 = FUN_0083f040();
            sprintf(local_18,"%dm");
            if (((local_89 != '\0') && (local_aa != '\0')) ||
               ((local_7d != '\0' || (local_7e != '\0')))) {
              uVar8 = FUN_00689eb0();
              local_1c8 = uVar8;
              uVar8 = FUN_00689eb0();
              local_154 = (float)uVar8 * 32.0;
              local_1f0 = uVar8;
              fVar6 = (float10)FUN_00689cb0(DAT_0091552c);
              local_130 = (float)fVar6;
              FUN_00689d10(DAT_0091552c,DAT_00917580);
            }
            if (((local_7d != '\0') || (local_7e != '\0')) || (local_8a != '\0')) {
              fVar6 = (float10)FUN_004624f0();
              local_16c = (float)fVar6;
              if (0.0 < local_16c) {
                (**(code **)(*(int *)(local_90 + 0x18) + 0x1c))();
                fVar6 = (float10)FUN_00447ed0();
                local_d4 = (float)fVar6;
                if (0.25 <= local_d4) {
                  if (0.5 <= local_d4) {
                    local_b4 = *(undefined4 *)(local_9c + 0x24);
                  }
                  else {
                    local_b4 = *(undefined4 *)(local_9c + 0x28);
                  }
                }
                else {
                  local_b4 = *(undefined4 *)(local_9c + 0x2c);
                }
                uVar8 = FUN_00689eb0();
                local_1c0 = uVar8;
                iVar4 = FUN_0068f090();
                local_dc = (int)((float)iVar4 * (float)local_1c0);
                uVar8 = FUN_00689eb0();
                local_1e0 = uVar8;
                iVar4 = FUN_0068f0c0();
                local_d8 = (int)((float)iVar4 * local_1e0._4_4_);
                uVar8 = FUN_00689eb0();
                local_c8 = ((int)local_88 - (int)((float)uVar8 * 37.0)) - local_dc;
                local_c4 = local_88._4_4_ - local_d8 / 2;
                local_13c = (int)((1.0 - local_d4) * (float)local_d8);
                local_28 = *(undefined4 *)(DAT_00917580 + 8);
                local_24 = *(undefined4 *)(DAT_00917580 + 0xc);
                local_20 = *(undefined4 *)(DAT_00917580 + 0x10);
                local_1c = *(undefined4 *)(DAT_00917580 + 0x14);
                *(int *)(DAT_00917580 + 8) = local_c8;
                *(int *)(DAT_00917580 + 0xc) = local_c4 + local_13c;
                *(int *)(DAT_00917580 + 0x10) = local_c8 + -1 + local_dc;
                *(int *)(DAT_00917580 + 0x14) = local_c4 + local_d8;
                local_1d0 = uVar8;
                iVar4 = FUN_0068f360();
                if (-1 < iVar4) {
                  FUN_0068c560(DAT_00917580,local_b4,local_c8 - *(int *)(DAT_00917580 + 8));
                }
                iVar4 = DAT_00917580;
                *(undefined4 *)(DAT_00917580 + 8) = local_28;
                *(undefined4 *)(iVar4 + 0xc) = local_24;
                *(undefined4 *)(iVar4 + 0x10) = local_20;
                *(undefined4 *)(iVar4 + 0x14) = local_1c;
              }
            }
          }
          if (((*(uint *)(DAT_0094672c + 0x30) & 0x20) != 0) && (local_7d != '\0')) {
            local_d0 = FUN_00417ca0();
            if (local_d0 != 0) {
              local_184 = FUN_00417f90();
              for (local_b8 = 0; local_b8 < 5; local_b8 = local_b8 + 1) {
                if ((1 << ((byte)local_b8 & 0x1f) & local_184) != 0) {
                  local_f8 = (int *)FUN_00417f60();
                  (**(code **)(*local_f8 + 0x2c))();
                  uVar8 = FUN_00497780();
                  local_11c = uVar8;
                  local_f4 = uVar8;
                  if (1.0 < local_148) {
                    uVar8 = FUN_00689eb0();
                    local_1a8 = uVar8;
                    FUN_0068aed0(DAT_00917580,local_f4);
                    uVar8 = FUN_00689eb0();
                    local_1b8 = uVar8;
                    FUN_0068aed0(DAT_00917580,local_f4);
                  }
                }
              }
            }
          }
          break;
        case 2:
          FUN_00417990();
          FUN_0068c560(DAT_00917580,*(undefined4 *)(local_9c + 0x14),(int)local_88);
          if (local_94 != 0) {
            FUN_00689ab0(DAT_0091552c);
            std::_Init_atomic_counter(DAT_0091552c,local_98);
            uVar8 = FUN_00689eb0();
            local_1a0 = uVar8;
            FUN_00689d10(DAT_0091552c,DAT_00917580);
          }
          break;
        case 3:
          FUN_00417990();
          FUN_0068c560(DAT_00917580,*(undefined4 *)(local_9c + 0x20),(int)local_88);
          if (local_94 != 0) {
            FUN_00689ab0(DAT_0091552c);
            std::_Init_atomic_counter(DAT_0091552c,local_98);
            uVar8 = FUN_00689eb0();
            local_1d8 = uVar8;
            FUN_00689d10(DAT_0091552c,DAT_00917580);
          }
          break;
        case 4:
          FUN_00417990();
          FUN_0068c560(DAT_00917580,*(undefined4 *)(local_9c + 0x18),(int)local_88);
          if (local_94 != 0) {
            FUN_00689ab0(DAT_0091552c);
            std::_Init_atomic_counter(DAT_0091552c,local_98);
            uVar8 = FUN_00689eb0();
            local_1e8 = uVar8;
            FUN_00689d10(DAT_0091552c,DAT_00917580);
          }
          break;
        case 5:
          FUN_00417990();
          FUN_0068c560(DAT_00917580,*(undefined4 *)(local_9c + 0x1c),(int)local_88);
          if (local_94 != 0) {
            FUN_00689ab0(DAT_0091552c);
            std::_Init_atomic_counter(DAT_0091552c,local_98);
            uVar8 = FUN_00689eb0();
            local_1f8 = uVar8;
            FUN_00689d10(DAT_0091552c,DAT_00917580);
          }
        }
      }
      FUN_0046b260();
    }
  }
  FUN_0083e885();
  return;
}

