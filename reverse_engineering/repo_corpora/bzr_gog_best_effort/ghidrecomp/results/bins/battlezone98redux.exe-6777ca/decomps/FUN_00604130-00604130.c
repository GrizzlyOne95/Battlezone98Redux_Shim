
void FUN_00604130(char param_1)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  float *pfVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  float10 fVar7;
  float fVar8;
  undefined1 local_288 [64];
  undefined1 local_248 [12];
  undefined1 local_23c [12];
  undefined1 local_230 [12];
  undefined1 local_224 [12];
  undefined1 local_218 [12];
  undefined1 local_20c [12];
  undefined1 local_200 [12];
  float local_1f4;
  float local_1f0;
  float local_1ec;
  float local_1e8;
  float local_1e4;
  float local_1e0;
  float local_1dc;
  float local_1d8;
  float local_1d4;
  float local_1d0;
  float local_1cc;
  float local_1c8;
  float local_1c4;
  float local_1c0;
  float local_1bc;
  float local_1b8;
  float local_1b4;
  float local_1b0;
  float local_1ac;
  float local_1a8;
  float local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  float local_190;
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  int local_16c;
  float local_168;
  undefined4 local_164;
  float local_160;
  float local_15c;
  float local_158;
  float local_154;
  float local_150;
  int local_14c;
  uint local_148;
  float local_144;
  float local_140;
  float local_13c;
  int local_138;
  float local_134;
  float *local_130;
  float local_12c;
  float local_128;
  int local_124;
  float local_120;
  float *local_11c;
  uint local_118;
  uint local_114;
  int local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8 [16];
  undefined4 local_a8 [16];
  undefined1 local_68 [12];
  undefined4 local_5c;
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
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_124 = FUN_00417ca0();
  if (local_124 == 0) {
    FUN_007d6a70();
    goto LAB_00605253;
  }
  if (*(int *)(local_110 + 0xb4) == 0) {
    FUN_007d6a70();
    goto LAB_00605253;
  }
  if (*(int *)(local_110 + 0x18) == 0) {
    local_120 = 0.0;
  }
  else {
    fVar7 = (float10)FUN_00462470();
    local_1e4 = (float)fVar7;
    local_17c = local_1e4;
    fVar7 = (float10)FUN_00820570((double)(*(float *)(local_110 + 0xd4) + 0.0001));
    local_184 = (float)fVar7;
    local_120 = local_17c * local_184;
    local_174 = local_184;
  }
  local_114 = *(uint *)(*(int *)(*(int *)(local_110 + 0xb4) + 8) + 0xc);
  if (local_114 < 0x52444555) {
    if (local_114 != 0x52444554) {
      if (local_114 < 0x494d474d) {
        if (local_114 != 0x494d474c) {
          if (local_114 != 0x43485247) {
            if (local_114 == 0x44495350) {
              if (param_1 != '\0') {
                (**(code **)(**(int **)(local_110 + 0xb4) + 8))();
              }
              goto LAB_00605253;
            }
            goto LAB_00604766;
          }
          goto LAB_006048d2;
        }
      }
      else {
        if (local_114 == 0x49524546) goto LAB_00605253;
        if (local_114 != 0x4c4e4348) goto LAB_00604766;
      }
LAB_00604720:
      if (param_1 == '\0') goto LAB_00605253;
      fVar7 = (float10)FUN_0044fb20(local_120,
                                    *(undefined4 *)(*(int *)(*(int *)(local_110 + 0xb4) + 8) + 0x8c)
                                   );
      local_120 = (float)fVar7;
      goto LAB_00604766;
    }
    cVar2 = FUN_004757d0();
    if (cVar2 == '\0') {
      if (param_1 == '\0') goto LAB_00605253;
    }
    else {
      local_138 = FUN_004757f0();
      if (local_138 != 0) {
        puVar5 = (undefined4 *)FUN_00439de0(local_200,*(int *)(local_138 + 0x14) + 0x20);
        local_100 = *puVar5;
        local_fc = puVar5[1];
        local_f8 = puVar5[2];
        fVar7 = (float10)FUN_00822d60(*(undefined4 *)(local_138 + 0x30),
                                      *(undefined4 *)(local_138 + 0x34),
                                      *(undefined4 *)(local_138 + 0x38));
        puVar5 = (undefined4 *)FUN_00439d00(local_20c,local_100,local_fc,local_f8,(float)fVar7);
        local_f4 = *puVar5;
        local_f0 = puVar5[1];
        local_ec = puVar5[2];
        local_14c = *(int *)(*(int *)(local_138 + 0xc) + 0x3c);
        local_14 = local_f4;
        local_10 = local_f0;
        local_c = local_ec;
        if ((local_14c != 0) && (0.0 < *(float *)(local_14c + 0x50))) {
          iVar3 = FUN_00462400();
          local_18c = *(float *)(local_14c + 0x50) + *(float *)(iVar3 + 0xc);
          iVar3 = FUN_00462400();
          local_154 = local_18c + *(float *)(iVar3 + 0xc);
          puVar5 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_110 + 0x10) + 0x18) + 0xc))();
          fVar7 = (float10)FUN_004620b0(local_f4,local_f0,local_ec,*puVar5,puVar5[1],puVar5[2]);
          local_194 = (float)fVar7;
          if (local_194 < local_154 * local_154) goto LAB_00605253;
        }
        puVar5 = (undefined4 *)
                 FUN_004624b0(*(undefined4 *)(local_138 + 0x30),*(undefined4 *)(local_138 + 0x34),
                              *(undefined4 *)(local_138 + 0x38));
        puVar5 = (undefined4 *)FUN_004401a0(local_224,*puVar5,puVar5[1],puVar5[2]);
        local_50 = *puVar5;
        local_4c = puVar5[1];
        local_48 = puVar5[2];
        local_2c = local_50;
        local_28 = local_4c;
        local_24 = local_48;
        puVar5 = (undefined4 *)
                 (**(code **)(*(int *)(*(int *)(local_110 + 0x18) + 0x18) + 0xc))
                           (local_f4,local_f0,local_ec);
        puVar5 = (undefined4 *)FUN_004401a0(local_23c,*puVar5,puVar5[1],puVar5[2]);
        local_5c = *puVar5;
        local_58 = puVar5[1];
        local_54 = puVar5[2];
        local_20 = local_5c;
        local_1c = local_58;
        local_18 = local_54;
        fVar7 = (float10)FUN_004428b0(&local_50,&local_5c);
        local_19c = (float)fVar7;
        if (0.0 < local_19c) {
          (**(code **)(**(int **)(local_110 + 0xb4) + 8))();
          goto LAB_00605253;
        }
      }
    }
  }
  else {
    if (local_114 < 0x54484d4d) {
      if (local_114 == 0x54484d4c) goto LAB_00604720;
      if (local_114 == 0x52444d50) goto LAB_00605253;
      if (local_114 == 0x5244524c) {
        if ((param_1 == '\0') ||
           ((*(int *)(*(int *)(*(int *)(local_110 + 0xb4) + 0xc) + 0x14) == 0x544f5250 &&
            (*(float *)(local_110 + 0xd4) <= *(float *)(local_110 + 0x9c) &&
             *(float *)(local_110 + 0x9c) != *(float *)(local_110 + 0xd4))))) goto LAB_00605253;
        fVar7 = (float10)FUN_0044fb20(local_120,
                                      *(undefined4 *)
                                       (*(int *)(*(int *)(local_110 + 0xb4) + 8) + 0x8c));
        local_120 = (float)fVar7;
        goto LAB_006048d2;
      }
    }
    else if (local_114 == 0x54525850) goto LAB_00605253;
LAB_00604766:
    if (param_1 == '\0') goto LAB_00605253;
    fVar8 = *(float *)(local_110 + 0x9c) * *(float *)(local_110 + 0x10c);
    if (*(float *)(local_110 + 0xd4) <= fVar8 && fVar8 != *(float *)(local_110 + 0xd4)) {
      fVar7 = (float10)FUN_00822d60();
      local_1a4 = (float)fVar7;
      *(float *)(local_110 + 0x10c) = *(float *)(local_110 + 0x10c) - local_1a4 * 0.1;
      iVar3 = FUN_00462530();
      if (*(int *)(local_110 + 0x14) == iVar3) {
        fVar7 = (float10)FUN_00822da0();
        local_1b4 = (float)fVar7;
        local_1ac = local_1b4;
        fVar7 = (float10)FUN_0046d040();
        local_1bc = (float)fVar7;
        if ((local_1b4 - local_1bc < 1.0) && (*(int *)(*(int *)(local_110 + 0x10) + 0x98) != 0)) {
          local_1ec = *(float *)(*(int *)(*(int *)(local_110 + 0x10) + 0x98) + 0x58) * 0.01;
          fVar7 = (float10)FUN_00822d60();
          local_1f4 = (float)fVar7;
          *(float *)(local_110 + 0x10c) = *(float *)(local_110 + 0x10c) - local_1ec * local_1f4;
        }
      }
      goto LAB_00605253;
    }
    *(undefined4 *)(local_110 + 0x10c) = 0x3f800000;
  }
LAB_006048d2:
  if (0.0 < *(float *)(local_110 + 0xe0)) {
    fVar7 = (float10)FUN_00453f80();
    local_1c8 = (float)fVar7;
    if (local_1c8 < *(float *)(local_110 + 0xf4) + local_120) {
      fVar7 = (float10)FUN_00453f80();
      local_1d4 = (float)fVar7;
      if (local_1d4 < local_120 * 0.5 + *(float *)(local_110 + 0xf8)) {
        FUN_0049f450();
        local_148 = FUN_00462510();
        if (-1 < *(int *)(local_110 + 0xbc)) {
          local_148 = ~(1 << ((byte)*(undefined4 *)(local_110 + 0xbc) & 0x1f)) & local_148;
        }
        FUN_004d9880();
        local_118 = *(uint *)(*(int *)(*(int *)(local_110 + 0xb4) + 8) + 0xc);
        if (local_118 < 0x504f5053) {
          if (local_118 != 0x504f5052) {
            if (local_118 < 0x4c4e4349) {
              if (local_118 != 0x4c4e4348) {
                if (local_118 == 0x43485247) {
                  cVar2 = FUN_005fce20();
                  if (cVar2 == '\0') {
                    if (param_1 == '\0') {
                      (**(code **)(**(int **)(local_110 + 0xb4) + 8))();
                    }
                    cVar2 = FUN_005fcd90();
                    if (cVar2 == '\0') {
                      FUN_00511fc0();
                    }
                    else {
                      bVar1 = Concurrency::details::SchedulerProxy::ShouldReceiveNotifications
                                        (*(SchedulerProxy **)(local_110 + 0xb4));
                      if (!bVar1) {
                        local_130 = (float *)FUN_005fcd70();
                        fVar7 = (float10)FUN_0046d080();
                        local_144 = (float)fVar7;
                        local_158 = 0.0;
                        local_140 = local_130[8];
                        if (local_140 != 0.0) {
                          local_13c = local_130[1];
                          if (0 < *(int *)((int)local_140 + 0x4c)) {
                            iVar3 = FUN_00417c80();
                            local_13c = (float)FUN_0046b550(local_13c,
                                                            iVar3 / *(int *)((int)local_140 + 0x4c))
                            ;
                          }
                          local_168 = (float)(int)local_13c;
                          fVar7 = (float10)FUN_005fce50(*(undefined4 *)(local_110 + 0x18),local_140)
                          ;
                          local_1c0 = (float)fVar7;
                          local_1d0 = local_168 * local_1c0;
                          local_15c = (float)(int)local_13c * (float)*(int *)((int)local_140 + 0x4c)
                          ;
                          fVar7 = (float10)FUN_005fce00();
                          local_170 = (float)fVar7;
                          local_1dc = local_170 + (float)((int)local_13c + -1) * local_130[2];
                          fVar7 = (float10)FUN_0044fb20(0x38d1b717,local_1dc);
                          local_178 = (float)fVar7;
                          local_188 = local_144 / local_178;
                          local_180 = 1.0 - local_144;
                          fVar7 = (float10)FUN_0044fb20(0x38d1b717,local_15c);
                          local_1e0 = (float)fVar7;
                          local_158 = (local_188 + local_180 / local_1e0) * local_1d0;
                        }
                        local_150 = 0.0;
                        local_11c = local_130;
                        while( true ) {
                          local_11c = local_11c + 0xb;
                          pfVar4 = (float *)FUN_004626f0();
                          if (pfVar4 < local_11c) break;
                          local_128 = 0.0;
                          local_134 = local_11c[8];
                          if (local_134 != 0.0) {
                            local_12c = local_11c[1];
                            if (0 < *(int *)((int)local_134 + 0x4c)) {
                              iVar3 = FUN_00417c80();
                              local_12c = (float)FUN_0046b550(local_12c,
                                                              iVar3 / *(int *)((int)local_134 + 0x4c
                                                                              ));
                            }
                            local_190 = (float)(int)local_12c;
                            fVar7 = (float10)FUN_005fce50(*(undefined4 *)(local_110 + 0x18));
                            local_1f0 = (float)fVar7;
                            local_1b0 = local_190 * local_1f0;
                            local_1a0 = (float)(int)local_12c *
                                        (float)*(int *)((int)local_134 + 0x4c);
                            local_198 = (float)((int)local_12c + -1) * local_11c[2] + *local_11c;
                            fVar7 = (float10)FUN_0044fb20(0x38d1b717);
                            local_1d8 = (float)fVar7;
                            local_1c4 = local_144 / local_1d8;
                            local_1e8 = 1.0 - local_144;
                            fVar7 = (float10)FUN_0044fb20(0x38d1b717);
                            local_1a8 = (float)fVar7;
                            local_128 = (local_1c4 + local_1e8 / local_1a8) * local_1b0;
                            fVar7 = (float10)FUN_00822d80();
                            local_1cc = (float)fVar7;
                            local_1b8 = local_1cc * 3.0 +
                                        (float)(((int)local_11c - (int)local_130) / 0x2c) * 2.73;
                            FUN_00462450();
                            fVar7 = (float10)FUN_00822970();
                            local_160 = (float)fVar7;
                            local_128 = (local_160 * 0.1 + 1.0) * local_128;
                            if (local_150 < local_128) {
                              local_150 = local_128;
                            }
                          }
                        }
                        if (local_158 < local_150) {
                          FUN_00511fc0();
                        }
                      }
                    }
                  }
                  goto LAB_00605253;
                }
                if (local_118 != 0x494d474c) goto LAB_00605033;
              }
              goto LAB_00604a98;
            }
            if (local_118 != 0x4d4f5254) {
LAB_00605033:
              (**(code **)(*(int *)(*(int *)(local_110 + 0x18) + 0x18) + 0x30))();
              iVar3 = FUN_0062e000();
              if (iVar3 != 0) {
                (**(code **)(*(int *)(*(int *)(local_110 + 0x18) + 0x18) + 0x30))();
                iVar3 = FUN_00417e20();
                if ((iVar3 == 0) ||
                   (cVar2 = (**(code **)(**(int **)(local_110 + 0x18) + 0x6c))(), cVar2 != '\0'))
                goto LAB_00605201;
              }
              puVar5 = (undefined4 *)
                       FUN_0081fe60(local_288,*(int *)(*(int *)(local_110 + 0xb4) + 0x10) + 0x20,
                                    *(int *)(local_110 + 0xb4) + 0x28);
              puVar6 = local_e8;
              for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
                *puVar6 = *puVar5;
                puVar5 = puVar5 + 1;
                puVar6 = puVar6 + 1;
              }
              puVar5 = local_e8;
              puVar6 = local_a8;
              for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
                *puVar6 = *puVar5;
                puVar5 = puVar5 + 1;
                puVar6 = puVar6 + 1;
              }
              local_164 = *(undefined4 *)(local_110 + 0xa4);
              puVar5 = (undefined4 *)FUN_004560b0(local_218,local_a8);
              local_10c = *puVar5;
              local_108 = puVar5[1];
              local_104 = puVar5[2];
              puVar5 = (undefined4 *)
                       FUN_004462d0(local_248,*(undefined4 *)(local_110 + 0xa8),local_10c,local_108,
                                    local_104);
              local_44 = *puVar5;
              local_40 = puVar5[1];
              local_3c = puVar5[2];
              puVar5 = (undefined4 *)FUN_00439de0(local_230,local_a8);
              local_38 = *puVar5;
              local_34 = puVar5[1];
              local_30 = puVar5[2];
              cVar2 = FUN_00480a30(&local_38,&local_44,&local_164,local_68,
                                   *(undefined4 *)(local_110 + 0x18),0);
              if (cVar2 == '\0') goto LAB_00605253;
            }
          }
        }
        else if (local_118 != 0x52444554) {
          if ((local_118 != 0x5244524c) && (local_118 != 0x54484d4c)) goto LAB_00605033;
LAB_00604a98:
          cVar2 = FUN_005fcd40();
          if (cVar2 == '\0') {
            FUN_00511fc0();
          }
          goto LAB_00605253;
        }
LAB_00605201:
        FUN_00511fc0();
        goto LAB_00605253;
      }
    }
  }
  local_16c = *(int *)(*(int *)(*(int *)(local_110 + 0xb4) + 8) + 0xc);
  if (local_16c == 0x43485247) {
    (**(code **)(**(int **)(local_110 + 0xb4) + 8))();
  }
LAB_00605253:
  FUN_0083e885();
  return;
}

