
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004ab380(float param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 *puVar5;
  int *piVar6;
  undefined4 *puVar7;
  bool bVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined8 uVar11;
  undefined1 local_248 [12];
  undefined1 local_23c [12];
  undefined1 local_230 [12];
  undefined1 local_224 [12];
  undefined1 local_218 [36];
  undefined1 local_1f4 [12];
  float local_1e8;
  void *local_1e4;
  int local_1e0;
  undefined4 *local_1dc;
  float local_1d8;
  undefined4 *local_1d4;
  float local_1d0;
  undefined4 *local_1cc;
  float local_1c8;
  undefined4 local_1c4;
  float local_1c0;
  undefined4 local_1bc;
  float local_1b8;
  undefined4 local_1b4;
  void *local_1b0;
  float local_1ac;
  float local_1a8;
  float local_1a4;
  float local_1a0;
  int local_19c;
  float local_198;
  float local_194;
  float local_190;
  int local_18c;
  float local_188;
  float local_184;
  float local_180;
  int local_17c;
  uint local_178;
  int local_174;
  float local_170;
  float local_16c;
  undefined4 *local_168;
  undefined4 *local_164;
  undefined4 *local_160;
  int local_15c;
  int local_158;
  int local_154;
  undefined4 *local_150;
  int *local_14c;
  undefined4 local_148 [10];
  double local_120;
  double local_118;
  double local_110;
  undefined4 local_108 [10];
  double local_e0;
  double local_d8;
  double local_d0;
  int local_c8;
  float local_c4;
  int local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
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
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  int local_38;
  int local_34;
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_004aeb80();
  if ((local_14c[0x88] == 0) && (local_14c[0x3f] == 0)) {
    iVar2 = (**(code **)(local_14c[6] + 0x30))();
    local_14c[0x88] = iVar2;
  }
  else if ((local_14c[0x88] != 0) &&
          ((local_14c[0x3f] != 0 && (*(int *)(local_14c[0x3e] + 0x14) != 0x54554700)))) {
    local_14c[0x88] = 0;
  }
  cVar1 = FUN_004af020();
  if ((((cVar1 == '\0') && (cVar1 = FUN_004af020(), cVar1 == '\0')) &&
      (cVar1 = FUN_004af020(), cVar1 == '\0')) && (cVar1 = FUN_004af020(), cVar1 == '\0')) {
    if (1000.0 < (float)local_14c[0x47]) {
      uVar3 = FUN_004623e0((double)(float)local_14c[0x47]);
      FUN_007d6a70("Unit \"%s\" is moving unusually fast: v_mag=%f",uVar3);
      piVar4 = (int *)FUN_004462d0();
      local_38 = *piVar4;
      local_34 = piVar4[1];
      local_30 = piVar4[2];
      local_14c[0x4b] = local_38;
      local_14c[0x4c] = local_34;
      local_14c[0x4d] = local_30;
      local_14c[0x47] = 0x447a0000;
    }
  }
  else {
    uVar3 = FUN_004623e0();
    FUN_007d6a70("Unit \"%s\" has an invalid velocity",uVar3);
    piVar4 = (int *)FUN_00440000(local_1f4,0,0,0);
    local_14 = *piVar4;
    local_10 = piVar4[1];
    local_c = piVar4[2];
    local_14c[0x4b] = local_14;
    local_14c[0x4c] = local_10;
    local_14c[0x4d] = local_c;
    local_14c[0x47] = 0;
  }
  if ((float)local_14c[0x47] <= 0.0) {
    local_170 = 1e+30;
  }
  else {
    local_170 = 1.0 / (float)local_14c[0x47];
  }
  local_14c[0x48] = (int)local_170;
  piVar4 = (int *)local_14c[0x8c];
  piVar6 = local_14c + 0x45;
  for (iVar2 = 0x12; piVar4 = piVar4 + 1, iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar4 = *piVar6;
    piVar6 = piVar6 + 1;
  }
  local_150 = (undefined4 *)(local_14c[0x3d] + 0x20);
  cVar1 = FUN_004af060(*(undefined8 *)(local_14c[0x3d] + 0x48));
  if (((cVar1 == '\0') && (cVar1 = FUN_004af060(*(undefined8 *)(local_150 + 0xc)), cVar1 == '\0'))
     && (cVar1 = FUN_004af060(*(undefined8 *)(local_150 + 0xe)), cVar1 == '\0')) {
    iVar2 = FUN_0077d560(*(undefined8 *)(local_150 + 10),*(undefined8 *)(local_150 + 0xe));
    if (iVar2 == 0) {
      uVar3 = FUN_004623e0(*(undefined8 *)(local_150 + 10),*(undefined8 *)(local_150 + 0xe));
      FUN_007d6a70("Unit \"%s\" tried to leave the world: x=%f z=%f",uVar3);
      fVar9 = (float10)FUN_0044b310(*(undefined8 *)(local_150 + 10),(double)DAT_02cd912c,
                                    (double)DAT_02cd9124);
      *(double *)(local_150 + 10) = (double)fVar9;
      fVar9 = (float10)FUN_0044b310(*(undefined8 *)(local_150 + 0xe),(double)DAT_02cd9130,
                                    (double)DAT_02cd9128);
      *(double *)(local_150 + 0xe) = (double)fVar9;
      fVar9 = (float10)FUN_007855e0(*(undefined8 *)(local_150 + 10),*(undefined8 *)(local_150 + 0xe)
                                   );
      *(double *)(local_150 + 0xc) = (double)fVar9;
    }
  }
  else {
    uVar3 = FUN_004623e0();
    FUN_007d6a70("Unit \"%s\" has an invalid position",uVar3);
    *(double *)(local_150 + 10) = (double)(DAT_02cd912c + DAT_02cd9124) * 0.5;
    *(double *)(local_150 + 0xe) = (double)(DAT_02cd9130 + DAT_02cd9128) * 0.5;
    fVar9 = (float10)FUN_007855e0(*(undefined8 *)(local_150 + 10),*(undefined8 *)(local_150 + 0xe));
    *(double *)(local_150 + 0xc) = (double)fVar9;
  }
  puVar5 = (undefined4 *)FUN_004621a0(local_218);
  local_68 = *puVar5;
  local_64 = puVar5[1];
  local_60 = puVar5[2];
  local_150[6] = local_68;
  local_150[7] = local_64;
  local_150[8] = local_60;
  puVar5 = (undefined4 *)FUN_004440d0();
  local_50 = *puVar5;
  local_4c = puVar5[1];
  local_48 = puVar5[2];
  *local_150 = local_50;
  local_150[1] = local_4c;
  local_150[2] = local_48;
  puVar5 = (undefined4 *)FUN_004621a0(local_248);
  local_5c = *puVar5;
  local_58 = puVar5[1];
  local_54 = puVar5[2];
  *local_150 = local_5c;
  local_150[1] = local_58;
  local_150[2] = local_54;
  puVar5 = (undefined4 *)FUN_004440d0();
  local_8c = *puVar5;
  local_88 = puVar5[1];
  local_84 = puVar5[2];
  local_150[3] = local_8c;
  local_150[4] = local_88;
  local_150[5] = local_84;
  cVar1 = FUN_004af020();
  if (((cVar1 != '\0') || (cVar1 = FUN_004af020(), cVar1 != '\0')) ||
     (((cVar1 = FUN_004af020(), cVar1 != '\0' ||
       ((((cVar1 = FUN_004af020(), cVar1 != '\0' || (cVar1 = FUN_004af020(), cVar1 != '\0')) ||
         (cVar1 = FUN_004af020(), cVar1 != '\0')) ||
        ((cVar1 = FUN_004af020(), cVar1 != '\0' || (cVar1 = FUN_004af020(), cVar1 != '\0')))))) ||
      (cVar1 = FUN_004af020(), cVar1 != '\0')))) {
    puVar5 = (undefined4 *)FUN_00440000(local_23c,0x3f800000,0);
    local_20 = *puVar5;
    local_1c = puVar5[1];
    local_18 = puVar5[2];
    *local_150 = local_20;
    local_150[1] = local_1c;
    local_150[2] = local_18;
    puVar5 = (undefined4 *)FUN_00440000(local_224,0,0x3f800000);
    local_2c = *puVar5;
    local_28 = puVar5[1];
    local_24 = puVar5[2];
    local_150[3] = local_2c;
    local_150[4] = local_28;
    local_150[5] = local_24;
    puVar5 = (undefined4 *)FUN_00440000(local_230,0,0);
    local_44 = *puVar5;
    local_40 = puVar5[1];
    local_3c = puVar5[2];
    local_150[6] = local_44;
    local_150[7] = local_40;
    local_150[8] = local_3c;
  }
  FUN_004db100();
  FUN_004aaea0();
  cVar1 = FUN_004b9830();
  if (cVar1 == '\0') {
    if (*(char *)((int)local_14c + 0x79) != '\0') {
      FUN_005e1010();
      FUN_005e11b0();
      (**(code **)(local_14c[6] + 0x10))();
      goto LAB_004acba7;
    }
    if ((*(int *)(local_14c[0x8c] + 0xdc) != 0) && (local_14c[0x3b] != 0)) {
      *(undefined4 *)(local_14c[0x8c] + 0xdc) = 0;
      local_14c[0xa2] = 0x3f800000;
      iVar2 = FUN_00572a70();
      if (iVar2 != 0) {
        FUN_00626000();
        local_178 = (uint)(local_14c == DAT_00917afc);
        uVar11 = CONCAT44(local_178,0x45);
        uVar10 = 0;
        uVar3 = (**(code **)(local_14c[6] + 4))();
        FUN_00626470(uVar3,uVar10,uVar11);
      }
      FUN_0043d580();
      if (local_14c[0x68] != 0) {
        for (local_158 = 0; local_158 < 5; local_158 = local_158 + 1) {
          local_174 = FUN_00417f60();
          if (local_174 != 0) {
            FUN_004a77a0(local_158,0);
            FUN_00611590();
          }
        }
        local_1b0 = (void *)local_14c[0x68];
        operator_delete(local_1b0);
        local_14c[0x68] = 0;
      }
      if ((*(uint *)(local_14c[0x3d] + 0x14) & 0x80) == 0) {
        (**(code **)(*local_14c + 0x80))();
      }
      else {
        if (local_14c[0x3f] != 0) {
          local_1cc = (undefined4 *)local_14c[0x3f];
          local_164 = local_1cc;
          if (local_1cc == (undefined4 *)0x0) {
            local_1b4 = 0;
          }
          else {
            local_1b4 = (**(code **)*local_1cc)();
          }
        }
        local_14c[0x3f] = 0;
      }
      local_14c[0x3b] = 0;
      FUN_0062de40(local_14c[0x3d]);
      local_14c[0x81] = 0;
      local_14c[0x80] = 0;
    }
    if ((*(int *)(local_14c[0x8c] + 0xe4) != 0) && (local_14c[0x3b] != 0)) {
      *(undefined4 *)(local_14c[0x8c] + 0xe4) = 0;
      (**(code **)(*local_14c + 0x84))();
    }
    if (*(int *)(local_14c[0x8c] + 0xe8) != 0) {
      *(undefined4 *)(local_14c[0x8c] + 0xe8) = 0;
      (**(code **)(*local_14c + 0x7c))();
    }
    if (*(int *)(local_14c[0x8c] + 0xec) != 0) {
      *(undefined4 *)(local_14c[0x8c] + 0xec) = 0;
      FUN_004aeae0();
    }
  }
  if (local_14c[0x5d] == DAT_00917b00) {
    (**(code **)(*local_14c + 0x5c))();
  }
  iVar2 = FUN_00417f90();
  if (iVar2 < 0) {
    FUN_004723b0();
  }
  if (local_14c[0x68] != 0) {
    (**(code **)(*local_14c + 0x98))();
  }
  if ((*(uint *)(local_14c[0x3d] + 0x14) & 0x200) != 0) {
    if ((*(uint *)(local_14c[0x8c] + 0x114) & 0x8000) == 0) {
      puVar5 = (undefined4 *)(local_14c[0x3d] + 0x20);
      puVar7 = local_108;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar7 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar7 = puVar7 + 1;
      }
      local_e0 = (double)(float)local_14c[0x42];
      local_d8 = (double)(float)local_14c[0x43];
      local_d0 = (double)(float)local_14c[0x44];
      if (*(int *)(local_14c[0x3e] + 0x144) == 0) {
        if (DAT_00917a48 != 0) {
          FUN_004cb7b0(local_108,0);
        }
      }
      else {
        FUN_004cb7b0(local_108,0);
      }
      *(uint *)(local_14c[0x8c] + 0x114) = *(uint *)(local_14c[0x8c] + 0x114) | 0x8000;
      if (local_14c[0x8a] != 2) {
        *(undefined4 *)(local_14c[0x8c] + 0x110) = 0x40a00000;
      }
      FUN_0047c210();
      FUN_0043d580();
      if ((*(uint *)(local_14c[0x3d] + 0x14) & 0x80) == 0) {
        if (local_14c[0x3b] == 0) {
          if (local_14c[0x3f] != 0) {
            local_1d4 = (undefined4 *)local_14c[0x3f];
            local_160 = local_1d4;
            if (local_1d4 == (undefined4 *)0x0) {
              local_1c4 = 0;
            }
            else {
              local_1c4 = (**(code **)*local_1d4)();
            }
          }
          local_14c[0x3f] = 0;
          if (local_14c == DAT_00917afc) {
            iVar2 = FUN_00572a70();
            if (iVar2 != 0) {
              FUN_00572ad0();
            }
            FUN_00621790();
            FUN_0061a000();
            FUN_0061cf30();
            _DAT_009198e4 = 1;
          }
        }
        else {
          (**(code **)(*local_14c + 0x80))();
        }
      }
      else {
        if (local_14c[0x3f] != 0) {
          local_1dc = (undefined4 *)local_14c[0x3f];
          local_168 = local_1dc;
          if (local_1dc == (undefined4 *)0x0) {
            local_1bc = 0;
          }
          else {
            local_1bc = (**(code **)*local_1dc)();
          }
        }
        local_14c[0x3f] = 0;
      }
      if (local_14c[0x68] != 0) {
        for (local_15c = 0; local_15c < 5; local_15c = local_15c + 1) {
          local_17c = FUN_00417f60();
          if (local_17c != 0) {
            FUN_004a77a0(local_15c,0);
            FUN_00611590();
          }
        }
        local_1e4 = (void *)local_14c[0x68];
        operator_delete(local_1e4);
        local_14c[0x68] = 0;
      }
      fVar9 = (float10)FUN_004464c0();
      local_184 = (float)fVar9;
      local_14c[0x4b] = (int)(local_184 * 3.0 + (float)local_14c[0x4b]);
      fVar9 = (float10)FUN_004464c0();
      local_188 = (float)fVar9;
      local_14c[0x4c] = (int)(local_188 * 3.0 + 10.0 + (float)local_14c[0x4c]);
      fVar9 = (float10)FUN_004464c0();
      local_190 = (float)fVar9;
      local_14c[0x4d] = (int)(local_190 * 3.0 + (float)local_14c[0x4d]);
      fVar9 = (float10)FUN_004464c0();
      local_198 = (float)fVar9;
      local_14c[0x4e] = (int)(local_198 * 2.0 + (float)local_14c[0x4e]);
      fVar9 = (float10)FUN_004464c0();
      local_1a0 = (float)fVar9;
      local_14c[0x4f] = (int)(local_1a0 * 0.5 + (float)local_14c[0x4f]);
      fVar9 = (float10)FUN_004464c0();
      local_1d8 = (float)fVar9;
      local_14c[0x50] = (int)(local_1d8 * 2.0 + (float)local_14c[0x50]);
      FUN_00492460();
      puVar5 = (undefined4 *)FUN_0081fd40();
      local_a4 = *puVar5;
      local_a0 = puVar5[1];
      local_9c = puVar5[2];
      local_98 = puVar5[3];
      local_94 = puVar5[4];
      local_90 = puVar5[5];
      local_154 = (int)(*(float *)(local_14c[0x3c] + 0x14) * 10.0);
      local_80 = local_a4;
      local_7c = local_a0;
      local_78 = local_9c;
      local_74 = local_98;
      local_70 = local_94;
      local_6c = local_90;
      while( true ) {
        local_1e0 = local_154;
        if (local_154 == 0) break;
        local_154 = local_154 + -1;
        fVar9 = (float10)FUN_004464c0();
        local_1e8 = (float)fVar9;
        local_b0 = local_1e8 * 20.0 + (float)local_14c[0x4b];
        fVar9 = (float10)FUN_004464c0();
        local_1ac = (float)fVar9;
        local_ac = local_1ac * 15.0 + (float)local_14c[0x4c] + 5.0;
        fVar9 = (float10)FUN_004464c0();
        local_1a8 = (float)fVar9;
        local_a8 = local_1a8 * 20.0 + (float)local_14c[0x4d];
        FUN_0058b650(&local_a4,&local_b0);
      }
      local_154 = (int)*(float *)(local_14c[0x3c] + 0x14);
      while( true ) {
        local_18c = local_154;
        if (local_154 == 0) break;
        local_154 = local_154 + -1;
        fVar9 = (float10)FUN_004464c0();
        local_180 = (float)fVar9;
        local_bc = local_180 * 40.0 + (float)local_14c[0x4b];
        fVar9 = (float10)FUN_004464c0();
        local_194 = (float)fVar9;
        local_b8 = local_194 * 30.0 + (float)local_14c[0x4c] + 10.0;
        fVar9 = (float10)FUN_004464c0();
        local_1b8 = (float)fVar9;
        local_b4 = local_1b8 * 40.0 + (float)local_14c[0x4d];
        FUN_004d10b0(&local_a4,&local_bc);
      }
      local_154 = local_154 + -1;
      iVar2 = FUN_00572a70();
      if (iVar2 == 0) {
        local_154 = (int)*(float *)(local_14c[0x3c] + 0x14);
        while( true ) {
          local_19c = local_154;
          iVar2 = local_154 + -1;
          bVar8 = local_154 == 0;
          local_154 = iVar2;
          if (bVar8) break;
          local_c8 = local_14c[0x4b];
          local_c4 = (float)local_14c[0x4c] + 10.0;
          local_c0 = local_14c[0x4d];
          FUN_004927d0();
        }
      }
    }
    else {
      if (*(float *)(local_14c[0x8c] + 0x110) <= 0.0) {
        (**(code **)(local_14c[6] + 0x14))();
        goto LAB_004acba7;
      }
      *(float *)(local_14c[0x8c] + 0x110) = *(float *)(local_14c[0x8c] + 0x110) - param_1;
      if (*(int *)(local_14c[0x3e] + 0x310) != 0) {
        fVar9 = (float10)FUN_004a7890();
        local_1c0 = (float)fVar9;
        if (local_1c0 * 0.5 + 0.5 < param_1 * 5.0) {
          local_16c = *(float *)(local_14c[0x3c] + 0x14) * 0.7;
          puVar5 = (undefined4 *)(local_14c[0x3d] + 0x20);
          puVar7 = local_148;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar7 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar7 = puVar7 + 1;
          }
          fVar9 = (float10)FUN_004464c0();
          local_1a4 = (float)fVar9;
          local_120 = (double)(local_1a4 * local_16c + (float)local_14c[0x42]);
          fVar9 = (float10)FUN_004464c0();
          local_1c8 = (float)fVar9;
          local_118 = (double)(local_1c8 * local_16c + (float)local_14c[0x43]);
          fVar9 = (float10)FUN_004464c0();
          local_1d0 = (float)fVar9;
          local_110 = (double)(local_1d0 * local_16c + (float)local_14c[0x44]);
          FUN_004cb7b0(local_148,0);
        }
      }
    }
  }
  if ((((local_14c[0x5e] == -1) && (local_14c[0x3f] != 0)) &&
      (4 < *(int *)(local_14c[0x3e] + 0x13c))) && (4 < *(int *)(local_14c[0x3e] + 0x140))) {
    iVar2 = FUN_005e0f90(*(undefined4 *)(local_14c[0x3e] + 0x13c),
                         *(undefined4 *)(local_14c[0x3e] + 0x140));
    local_14c[0x5e] = iVar2;
    if ((local_14c[0x5f] != 0) && (local_14c[0x5e] != -1)) {
      FUN_005e0f50(local_14c[0x5e],local_14c);
    }
  }
LAB_004acba7:
  FUN_0083e885();
  return;
}

