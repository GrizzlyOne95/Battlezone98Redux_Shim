
void FUN_005fd5f0(undefined4 *param_1,int param_2,int param_3,int *param_4)

{
  char cVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_19c [12];
  undefined1 local_190 [12];
  undefined1 local_184 [12];
  undefined1 local_178 [12];
  undefined1 local_16c [24];
  undefined1 local_154 [24];
  undefined1 local_13c [16];
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_10c;
  undefined4 local_108;
  float local_104;
  float local_100;
  int local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  int local_e8;
  float local_e0;
  float local_dc;
  int local_d8;
  float local_d4;
  int local_d0;
  float local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
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
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_ec = 20.0;
  local_108 = FUN_0045c4d0();
  local_d8 = 0;
  local_f8 = 0.0;
  local_8c = 0;
  local_88 = 0;
  local_84 = 0;
  FUN_0042d8c0();
  do {
    FID_conflict_begin();
    cVar1 = FUN_00420f10();
    if (cVar1 == '\0') {
      if (local_d8 != 0) {
        fVar5 = (float10)FUN_004428b0();
        local_100 = (float)fVar5;
        if (local_ec * local_ec < local_100) {
          fVar5 = (float10)FUN_00820570((double)local_100);
          local_120 = (float)fVar5;
          local_118 = local_120;
          puVar3 = (undefined4 *)FUN_004462d0(local_19c,local_120 * local_ec);
          local_8c = *puVar3;
          local_88 = puVar3[1];
          local_84 = puVar3[2];
          local_20 = local_8c;
          local_1c = local_88;
          local_18 = local_84;
        }
      }
      if (param_4 != (int *)0x0) {
        *param_4 = local_d8;
      }
      *param_1 = local_8c;
      param_1[1] = local_88;
      param_1[2] = local_84;
      FUN_0083e885();
      return;
    }
    piVar2 = (int *)FUN_0042de50();
    local_d0 = *piVar2;
    if (*(int *)(*(int *)(local_d0 + 0xc) + 0xc) != 0x534e4950) {
      puVar3 = (undefined4 *)FUN_00439de0();
      local_bc = *puVar3;
      local_b8 = puVar3[1];
      local_b4 = puVar3[2];
      local_44 = local_bc;
      local_40 = local_b8;
      local_3c = local_b4;
      (**(code **)(*(int *)(param_2 + 0x18) + 0xc))();
      puVar3 = (undefined4 *)FUN_004401a0(local_178,local_bc,local_b8);
      local_98 = *puVar3;
      local_94 = puVar3[1];
      local_90 = puVar3[2];
      local_50 = local_98;
      local_4c = local_94;
      local_48 = local_90;
      fVar5 = (float10)FUN_004428b0();
      local_12c = (float)fVar5;
      if (local_12c <= 40000.0) {
        if (local_d0 == param_3) {
          if (local_d8 == 0) {
            local_d8 = param_3;
          }
LAB_005fd88d:
          local_fc = FUN_00583e30();
          FUN_004624b0();
          puVar3 = (undefined4 *)
                   FUN_004401a0(local_190,*(undefined4 *)(local_fc + 0x18),
                                *(undefined4 *)(local_fc + 0x1c));
          local_a4 = *puVar3;
          local_a0 = puVar3[1];
          local_9c = puVar3[2];
          local_80 = local_a4;
          local_7c = local_a0;
          local_78 = local_9c;
          fVar5 = (float10)FUN_004428b0();
          local_f4 = (float)fVar5;
          if (0.0001 <= local_f4) {
            fVar5 = (float10)FUN_004428b0();
            local_11c = (float)fVar5;
            local_cc = -local_11c / local_f4;
            puVar3 = (undefined4 *)FUN_00439d00(local_13c,local_98,local_94,local_90);
            local_b0 = *puVar3;
            local_ac = puVar3[1];
            local_a8 = puVar3[2];
            local_5c = local_b0;
            local_58 = local_ac;
            local_54 = local_a8;
            FUN_004428b0();
            fVar5 = (float10)FUN_00417910();
            local_d4 = (float)fVar5;
            puVar3 = (undefined4 *)FUN_004462d0(local_154);
            local_c8 = *puVar3;
            local_c4 = puVar3[1];
            local_c0 = puVar3[2];
            local_38 = local_c8;
            local_34 = local_c4;
            local_30 = local_c0;
            iVar4 = FUN_00462400();
            local_dc = *(float *)(iVar4 + 0xc) + *(float *)(*(int *)(local_d0 + 0x14) + 0xac);
            local_e0 = 0.0;
            local_e8 = *(int *)(*(int *)(local_d0 + 0xc) + 0xc);
            if ((((local_e8 == 0x494d474d) || (local_e8 == 0x54484d4d)) || (local_e8 == 0x4d53534c))
               && (iVar4 = FUN_0056a4c0(), iVar4 == param_2)) {
              if (local_cc <= 0.0) {
                local_cc = 0.0;
              }
              if (local_cc < 3.0) {
                fVar5 = (float10)FUN_00456080();
                local_e0 = (float)fVar5;
                if ((local_cc < 1.0) && (local_dc < local_d4)) {
                  local_124 = local_cc - 1.0;
                  fVar5 = (float10)FUN_00456080(0x3f800000);
                  local_104 = (float)fVar5;
                  puVar3 = (undefined4 *)FUN_00439d00(local_16c,local_8c,local_88,local_84);
                  local_8c = *puVar3;
                  local_88 = puVar3[1];
                  local_84 = puVar3[2];
                  local_2c = local_8c;
                  local_28 = local_88;
                  local_24 = local_84;
                }
              }
            }
            else {
              if (local_cc <= 0.0) goto LAB_005fd67b;
              fVar5 = (float10)FUN_00453f80();
              local_128 = (float)fVar5;
              if (local_128 < local_dc * 2.5) {
                fVar5 = (float10)FUN_00456080();
                local_e0 = (float)fVar5;
              }
            }
            if (local_e0 != 0.0) {
              fVar5 = (float10)FUN_005fce50();
              local_110 = (float)fVar5;
              local_f0 = local_110 / (local_cc + 1.0);
              if (local_f8 < local_f0) {
                local_d8 = local_d0;
                local_f8 = local_f0;
              }
              puVar3 = (undefined4 *)FUN_00439d00(local_184,local_8c,local_88,local_84);
              local_8c = *puVar3;
              local_88 = puVar3[1];
              local_84 = puVar3[2];
              local_74 = local_8c;
              local_70 = local_88;
              local_6c = local_84;
            }
          }
        }
        else {
          puVar3 = (undefined4 *)FUN_00445260();
          local_68 = *puVar3;
          local_64 = puVar3[1];
          local_60 = (float)puVar3[2];
          local_14 = local_68;
          local_10 = local_64;
          local_c = local_60;
          fVar5 = (float10)FUN_00453f80();
          local_10c = (float)fVar5;
          if (local_10c <= local_c) {
            fVar5 = (float10)FUN_00453f80();
            local_114 = (float)fVar5;
            if (local_114 * 1.5 <= local_c) goto LAB_005fd88d;
          }
        }
      }
    }
LAB_005fd67b:
    FUN_0042da80();
  } while( true );
}

