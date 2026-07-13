
void FUN_006004a0(void)

{
  int iVar1;
  float *pfVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_250 [12];
  undefined1 local_244 [12];
  undefined1 local_238 [36];
  undefined1 local_214 [36];
  undefined1 local_1f0 [24];
  undefined1 local_1d8 [24];
  undefined1 local_1c0 [28];
  int local_1a4;
  int local_1a0;
  undefined4 local_19c;
  undefined4 local_198;
  float local_194;
  float local_190;
  int local_18c;
  undefined4 local_188;
  float local_184;
  int local_180;
  int *local_17c;
  int local_178;
  int local_174;
  int local_170;
  undefined4 local_16c;
  undefined4 local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
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
  float local_64;
  float local_60;
  float local_5c;
  char local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  sprintf(local_58," UnitTask: %s");
  FUN_004b70f0();
  iVar1 = (*(code *)**(undefined4 **)(*(int *)(local_170 + 0x10) + 0x18))();
  if (*(int *)(iVar1 + 0x14) == 0x54555252) {
    FUN_00417910();
    (**(code **)(*(int *)(*(int *)(local_170 + 0x10) + 0x18) + 0xc))();
    FUN_004b71f0();
  }
  local_17c = DAT_00917554;
  local_19c = 0x18;
  pfVar2 = (float *)(**(code **)(*(int *)(*(int *)(local_170 + 0x10) + 0x18) + 0xc))();
  local_64 = *pfVar2;
  local_60 = pfVar2[1];
  local_5c = pfVar2[2];
  (**(code **)(*local_17c + 0x24))();
  iVar1 = FUN_00492d40();
  if (iVar1 != 0) {
    pfVar2 = (float *)FUN_00492d40();
    local_64 = local_64 + *pfVar2;
    (**(code **)(*local_17c + 0x24))(local_64);
    local_1a0 = local_1a4 - local_18c;
    FUN_0068ad00(DAT_00917580,local_18c,local_198,local_1a0);
  }
  puVar3 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_170 + 0x10) + 0x18) + 0xc))();
  puVar3 = (undefined4 *)FUN_00440130(local_214,*puVar3,puVar3[1],puVar3[2]);
  local_10c = *puVar3;
  local_108 = puVar3[1];
  local_104 = puVar3[2];
  local_e8 = local_10c;
  local_e4 = local_108;
  local_e0 = local_104;
  (**(code **)(*(int *)(*(int *)(local_170 + 0x10) + 0x18) + 0xc))();
  FUN_004b7150();
  fVar4 = (float10)FUN_00462470();
  local_190 = (float)fVar4;
  local_184 = local_190 + 10.0;
  FUN_00462490();
  puVar3 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_170 + 0x10) + 0x18) + 0xc))(local_184)
  ;
  puVar3 = (undefined4 *)FUN_00439d00(local_244,*puVar3,puVar3[1],puVar3[2]);
  local_d0 = *puVar3;
  local_cc = puVar3[1];
  local_c8 = puVar3[2];
  local_70 = local_d0;
  local_6c = local_cc;
  local_68 = local_c8;
  (**(code **)(*(int *)(*(int *)(local_170 + 0x10) + 0x18) + 0xc))();
  FUN_004b7150();
  puVar3 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_170 + 0x10) + 0x18) + 0xc))(local_184)
  ;
  puVar3 = (undefined4 *)FUN_00439d00(local_250,*puVar3,puVar3[1],puVar3[2]);
  local_ac = *puVar3;
  local_a8 = puVar3[1];
  local_a4 = puVar3[2];
  local_70 = local_ac;
  local_6c = local_a8;
  local_68 = local_a4;
  (**(code **)(*(int *)(*(int *)(local_170 + 0x10) + 0x18) + 0xc))();
  FUN_004b7150();
  local_180 = *(int *)(local_170 + 8);
  if (local_180 == 2) {
    if (*(int *)(local_170 + 0x40) != 0) {
      puVar3 = (undefined4 *)FUN_004e5270();
      local_c4 = *puVar3;
      local_c0 = puVar3[1];
      local_bc = puVar3[2];
      local_88 = local_c4;
      local_84 = local_c0;
      local_80 = local_bc;
      (**(code **)(*(int *)(*(int *)(local_170 + 0x10) + 0x18) + 0xc))();
      FUN_004b7150();
      local_178 = *(int *)(local_170 + 0x44);
      while (local_178 = local_178 + 1, local_178 < *(int *)(*(int *)(local_170 + 0x40) + 4)) {
        puVar3 = (undefined4 *)FUN_004e5270();
        local_124 = *puVar3;
        local_120 = puVar3[1];
        local_11c = puVar3[2];
        puVar3 = (undefined4 *)FUN_004e5270();
        local_118 = *puVar3;
        local_114 = puVar3[1];
        local_110 = puVar3[2];
        FUN_004b7150();
      }
      FUN_00465320(*(undefined4 *)(local_170 + 0x10),*(undefined4 *)(local_170 + 0x80),DAT_008e7948,
                   local_88,local_84);
    }
  }
  else if (local_180 == 3) {
    sprintf(local_58," Stuck State: %s");
    FUN_004b70f0();
    sprintf(local_58," Next Stuck (%f)");
    FUN_004b70f0();
  }
  else if ((local_180 == 4) && (local_174 = FUN_00462630(), local_174 != 0)) {
    (**(code **)(*(int *)(*(int *)(local_170 + 0x10) + 0x18) + 0xc))();
    (**(code **)(*(int *)(local_174 + 0x18) + 0xc))();
    FUN_00462010();
    fVar4 = (float10)FUN_00417910();
    local_194 = (float)fVar4;
    local_188 = FUN_0045c4d0();
    puVar3 = (undefined4 *)FUN_004560b0();
    local_154 = *puVar3;
    local_150 = puVar3[1];
    local_14c = puVar3[2];
    puVar3 = (undefined4 *)FUN_00439d80();
    local_160 = *puVar3;
    local_15c = puVar3[1];
    local_158 = puVar3[2];
    puVar3 = (undefined4 *)
             FUN_00459570(local_1c0,*(undefined4 *)(local_170 + 0x110),local_160,local_15c,local_158
                          ,*(undefined4 *)(local_170 + 0x114));
    local_16c = *puVar3;
    local_168 = puVar3[1];
    local_164 = puVar3[2];
    local_94 = local_16c;
    local_90 = local_168;
    local_8c = local_164;
    puVar3 = (undefined4 *)(**(code **)(*(int *)(local_174 + 0x18) + 0xc))();
    puVar3 = (undefined4 *)FUN_00440130(local_1d8,*puVar3,puVar3[1],puVar3[2]);
    local_148 = *puVar3;
    local_144 = puVar3[1];
    local_140 = puVar3[2];
    local_dc = local_148;
    local_d8 = local_144;
    local_d4 = local_140;
    (**(code **)(*(int *)(*(int *)(local_170 + 0x10) + 0x18) + 0xc))();
    FUN_004b7150();
    (**(code **)(*(int *)(*(int *)(local_170 + 0x10) + 0x18) + 0xc))();
    puVar3 = (undefined4 *)FUN_004401a0(local_1f0,local_148,local_144,local_140);
    local_a0 = *puVar3;
    local_9c = puVar3[1];
    local_98 = puVar3[2];
    local_7c = local_a0;
    local_78 = local_9c;
    local_74 = local_98;
    FUN_0045c4d0();
    puVar3 = (undefined4 *)FUN_00440300();
    local_f4 = *puVar3;
    local_f0 = puVar3[1];
    local_ec = puVar3[2];
    local_7c = local_f4;
    local_78 = local_f0;
    local_74 = local_ec;
    puVar3 = (undefined4 *)FUN_004621a0();
    local_130 = *puVar3;
    local_12c = puVar3[1];
    local_128 = puVar3[2];
    local_b8 = local_130;
    local_b4 = local_12c;
    local_b0 = local_128;
    sprintf(local_58," Follow Dist (%.2f)");
    FUN_004b70f0();
    FUN_00462490();
    puVar3 = (undefined4 *)(**(code **)(*(int *)(local_174 + 0x18) + 0xc))(0x41a00000);
    puVar3 = (undefined4 *)FUN_00439d00(local_238,*puVar3,puVar3[1],puVar3[2]);
    local_100 = *puVar3;
    local_fc = puVar3[1];
    local_f8 = puVar3[2];
    (**(code **)(*(int *)(local_174 + 0x18) + 0xc))();
    FUN_004b7150();
  }
  FUN_0083e885();
  return;
}

