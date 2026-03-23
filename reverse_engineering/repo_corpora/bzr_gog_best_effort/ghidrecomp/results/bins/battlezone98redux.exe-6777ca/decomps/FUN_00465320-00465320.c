
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00465320(int *param_1,int *param_2,float param_3,float param_4,undefined4 param_5,
                 undefined4 param_6,float *param_7,char param_8)

{
  char cVar1;
  float *pfVar2;
  undefined4 *puVar3;
  int *piVar4;
  int iVar5;
  float10 fVar6;
  undefined1 local_160 [12];
  undefined1 local_154 [12];
  undefined1 local_148 [12];
  undefined1 local_13c [12];
  undefined1 local_130 [12];
  undefined1 local_124 [12];
  undefined1 local_118 [12];
  undefined4 local_10c;
  float local_108;
  float local_104;
  float local_100;
  undefined4 local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_e8;
  float local_e4;
  int local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  uint local_cc;
  float local_c8;
  uint local_c4;
  int *local_c0;
  float local_bc;
  char local_b5;
  int *local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  float local_98;
  float local_94;
  float local_90;
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
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  float local_3c;
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
  pfVar2 = (float *)(**(code **)(param_1[6] + 0xc))();
  local_98 = *pfVar2;
  local_94 = pfVar2[1];
  local_90 = pfVar2[2];
  puVar3 = (undefined4 *)FUN_004401a0(local_118,param_4,param_5,param_6);
  local_5c = *puVar3;
  local_58 = puVar3[1];
  local_54 = puVar3[2];
  local_14 = local_5c;
  local_10 = local_58;
  local_c = local_54;
  local_e0 = FUN_00462450();
  local_cc = (uint)(DAT_008e793c == 0);
  local_c4 = local_cc;
  if (param_1 == DAT_00917384) {
    FUN_007d6a70("\n[%f,%f]->[%f,%f].....",(double)local_98,(double)local_90,
                 SUB84((double)param_4,0));
    FUN_007d6a70("Ax: %f Az: %f  ",SUB84((double)*param_7,0));
  }
  FUN_005b28e0((double)local_98,(double)local_90);
LAB_004654bb:
  do {
    cVar1 = FUN_00462710();
    if (cVar1 == '\0') {
      FUN_0083e885();
      return;
    }
    local_b4 = (int *)FUN_00462630();
  } while (((local_b4 == (int *)0x0) || (local_b4 == param_1)) || (local_b4 == param_2));
  fVar6 = (float10)FUN_004624d0();
  local_f4 = (float)fVar6;
  if (5.0 < local_f4) goto code_r0x00465536;
  goto LAB_00465567;
code_r0x00465536:
  FUN_00462590();
  piVar4 = (int *)FUN_005e0f70();
  if ((local_b4 == piVar4) || (iVar5 = FUN_00462450(), iVar5 <= local_e0)) {
LAB_00465567:
    iVar5 = (**(code **)param_1[6])();
    if (((*(int *)(iVar5 + 0x14) != 0x54554700) ||
        (((piVar4 = (int *)FUN_005ed5a0(), local_b4 != piVar4 &&
          (iVar5 = (**(code **)local_b4[6])(), *(int *)(iVar5 + 0x14) != 0x52435943)) &&
         ((iVar5 = (**(code **)local_b4[6])(), *(int *)(iVar5 + 0x14) != 0x41524d52 &&
          (iVar5 = (**(code **)local_b4[6])(), *(int *)(iVar5 + 0x14) != 0x46414354)))))) &&
       ((iVar5 = (**(code **)param_1[6])(), *(int *)(iVar5 + 0x14) != 0x52435943 ||
        (iVar5 = (**(code **)local_b4[6])(), *(int *)(iVar5 + 0x14) != 0x54554700)))) {
      iVar5 = (**(code **)local_b4[6])();
      local_c0 = (int *)(iVar5 + 0x1c);
      if ((*local_c0 != 2) && (((*local_c0 != 10 && (*local_c0 != 7)) && (*local_c0 != 3)))) {
        (**(code **)(local_b4[6] + 4))();
        cVar1 = FUN_004db600();
        if (cVar1 == '\0') {
          (**(code **)(local_b4[6] + 4))();
          cVar1 = FUN_004db560();
          if ((cVar1 != '\0') &&
             (iVar5 = (**(code **)local_b4[6])(), *(int *)(iVar5 + 0x14) == 0x50524f58))
          goto LAB_004654bb;
        }
        else if ((*local_c0 == 4) || (*local_c0 == 1)) goto LAB_004654bb;
        local_fc = (**(code **)(local_b4[6] + 0xc))();
        puVar3 = (undefined4 *)FUN_004401a0(local_130,local_98,local_94,local_90);
        local_b0 = *puVar3;
        local_ac = puVar3[1];
        local_a8 = puVar3[2];
        local_20 = local_b0;
        local_1c = local_ac;
        local_18 = local_a8;
        fVar6 = (float10)FUN_004428b0();
        local_bc = (float)fVar6;
        if (local_bc < param_3 * param_3) {
          local_8c = 0;
          local_88 = 0;
          local_84 = 0;
          fVar6 = (float10)FUN_00462470();
          local_104 = (float)fVar6;
          local_e8 = local_104;
          fVar6 = (float10)FUN_00462470();
          local_f0 = (float)fVar6;
          local_d8 = local_104 + local_f0;
          if (DAT_008e793c != 0) {
            local_c4 = 1;
            local_10c = (**(code **)(local_b4[6] + 0x30))();
            iVar5 = FUN_00417e20();
            if ((iVar5 != 0) && (cVar1 = (**(code **)(*local_b4 + 0x68))(), cVar1 != '\0')) {
              if (DAT_009173d8 == 0) {
                local_c4 = FUN_004647e0();
              }
              else {
                local_c4 = FUN_00464c00(param_1,local_b4,DAT_008e7934);
              }
            }
          }
          if ((DAT_008e7930 != 0) && (local_c4 != 0)) {
            fVar6 = (float10)FUN_00462470();
            local_108 = (float)fVar6;
            local_f8 = local_108;
            fVar6 = (float10)FUN_00462470();
            local_100 = (float)fVar6;
            fVar6 = (float10)FUN_004624d0(param_3);
            puVar3 = (undefined4 *)
                     (**(code **)(local_b4[6] + 0xc))(local_14,local_10,local_c,(float)fVar6);
            puVar3 = (undefined4 *)(**(code **)(param_1[6] + 0xc))(*puVar3,puVar3[1],puVar3[2]);
            FUN_00464f80(*puVar3,puVar3[1],puVar3[2]);
            if (param_8 != '\0') {
              puVar3 = (undefined4 *)(**(code **)(local_b4[6] + 0xc))();
              puVar3 = (undefined4 *)FUN_00440130(local_160,*puVar3,puVar3[1],puVar3[2]);
              local_80 = *puVar3;
              local_7c = puVar3[1];
              local_78 = puVar3[2];
              local_2c = local_80;
              local_28 = local_7c;
              local_24 = local_78;
              (**(code **)(local_b4[6] + 0xc))();
              FUN_004b7150();
            }
          }
          if (((*local_c0 == 6) || (*local_c0 == 1)) &&
             (cVar1 = (**(code **)(*local_b4 + 0x68))(), cVar1 != '\0')) {
            local_c4 = 0;
          }
          if ((DAT_008e7940 != 0) && (local_c4 != 0)) {
            fVar6 = (float10)FUN_00417910();
            local_bc = (float)fVar6 - local_d8;
            if (local_bc < 0.1) {
              local_bc = 0.1;
            }
            local_d0 = 1.0 / local_bc;
            local_c8 = local_d0 - 1.0 / _DAT_008e7958;
            local_dc = local_c8 * local_c8 * _DAT_008e792c;
            puVar3 = (undefined4 *)FUN_004462d0(local_148,local_dc * local_d0);
            local_a4 = *puVar3;
            local_a0 = puVar3[1];
            local_9c = puVar3[2];
            local_38 = local_a4;
            local_34 = local_a0;
            local_30 = local_9c;
            puVar3 = (undefined4 *)FUN_00440130(local_124,local_8c,local_88,local_84);
            local_8c = *puVar3;
            local_88 = puVar3[1];
            local_84 = puVar3[2];
            local_50 = local_8c;
            local_4c = local_88;
            local_48 = local_84;
            if (param_8 != '\0') {
              puVar3 = (undefined4 *)(**(code **)(local_b4[6] + 0xc))();
              puVar3 = (undefined4 *)FUN_00440130(local_13c,*puVar3,puVar3[1],puVar3[2]);
              local_74 = *puVar3;
              local_70 = puVar3[1];
              local_6c = puVar3[2];
              local_68 = local_74;
              local_64 = local_70;
              local_60 = local_6c;
              (**(code **)(local_b4[6] + 0xc))();
              FUN_004b7150();
            }
          }
          local_b5 = '\0';
          fVar6 = (float10)FUN_004624d0();
          local_e4 = (float)fVar6;
          if (local_e4 < 1.0) {
            fVar6 = (float10)FUN_004428b0();
            local_d4 = (float)fVar6;
            if (local_d4 < 0.0) {
              FUN_00464610();
            }
          }
          if (local_b5 == '\0') {
            pfVar2 = (float *)FUN_00440130(local_154,*param_7,param_7[1],param_7[2]);
            local_44 = *pfVar2;
            local_40 = pfVar2[1];
            local_3c = pfVar2[2];
            *param_7 = local_44;
            param_7[1] = local_40;
            param_7[2] = local_3c;
          }
        }
      }
    }
  }
  goto LAB_004654bb;
}

