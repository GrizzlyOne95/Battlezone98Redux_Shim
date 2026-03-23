
void __fastcall FUN_005e2810(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  float *pfVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined1 local_1fc [64];
  undefined1 local_1bc [44];
  undefined1 local_190 [24];
  float local_178;
  undefined4 *local_174;
  float local_170;
  float local_16c;
  int local_168;
  float local_164;
  float local_160;
  float local_15c;
  int local_158;
  float local_154;
  int local_150;
  int local_14c;
  float local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138 [16];
  undefined4 local_f8 [16];
  undefined4 local_b8 [16];
  undefined4 local_78 [10];
  undefined8 local_50;
  undefined8 local_40;
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
  local_14c = param_1;
  local_168 = FUN_004da060(*(undefined4 *)(param_1 + 0xf0));
  if (local_168 == 0) {
    puVar2 = (undefined4 *)(*(int *)(local_14c + 0x14) + 0x20);
    puVar7 = local_78;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar7 = puVar7 + 1;
    }
  }
  else {
    puVar2 = (undefined4 *)FUN_00439de0();
    local_144 = *puVar2;
    local_140 = puVar2[1];
    local_13c = puVar2[2];
    local_2c = local_144;
    local_28 = local_140;
    local_24 = local_13c;
    puVar2 = (undefined4 *)
             (**(code **)(*(int *)(local_168 + 0x18) + 0xc))(local_144,local_140,local_13c);
    puVar2 = (undefined4 *)FUN_004401a0(local_190,*puVar2,puVar2[1],puVar2[2]);
    local_38 = *puVar2;
    local_34 = puVar2[1];
    local_30 = puVar2[2];
    local_20 = local_38;
    local_1c = local_34;
    local_18 = local_30;
    puVar2 = (undefined4 *)FUN_0081fa10(local_1fc,&local_144,&local_38);
    puVar7 = local_f8;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar7 = puVar7 + 1;
    }
    puVar2 = local_f8;
    puVar7 = local_78;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar7 = puVar7 + 1;
    }
  }
  puVar2 = (undefined4 *)FUN_008203f0();
  puVar7 = local_138;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar7 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar7 = puVar7 + 1;
  }
  puVar2 = local_138;
  puVar7 = local_b8;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar7 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar7 = puVar7 + 1;
  }
  local_158 = 0;
  local_16c = 0.0;
  local_154 = *(float *)(*(int *)(local_14c + 0xc) + 0x50) *
              *(float *)(*(int *)(local_14c + 0xc) + 0x54);
  local_178 = local_154 * local_154;
  FUN_005b28e0(local_50,local_40,(double)local_154,local_1bc);
  while (cVar1 = FUN_00462710(&local_174), cVar1 != '\0') {
    local_150 = FUN_004da060(*local_174);
    if ((local_150 != 0) && (uVar3 = FUN_0045c4b0(), (uVar3 & 0x400) == 0)) {
      pfVar4 = (float *)(**(code **)(*(int *)(local_150 + 0x18) + 0xc))();
      local_14 = *pfVar4;
      local_10 = pfVar4[1];
      local_c = pfVar4[2];
      FUN_00820180();
      if ((0.0 <= local_c) && (local_c <= local_154)) {
        iVar6 = FUN_00462400();
        local_15c = *(float *)(iVar6 + 0xc) * 0.75;
        local_15c = local_15c * local_15c;
        local_170 = local_14 * local_14 + local_10 * local_10;
        local_164 = local_c * local_c;
        local_160 = local_164 + local_170;
        if ((local_170 <= local_15c) || (local_160 * *(float *)(local_14c + 0xf8) <= local_164)) {
          local_148 = (local_164 / local_160) * (local_164 / local_160);
          local_148 = local_148 * local_148;
          local_148 = local_148 * local_148;
          local_148 = local_148 * local_148;
          local_148 = local_148 * local_148;
          iVar6 = (*(code *)**(undefined4 **)(local_150 + 0x18))();
          local_148 = ((*(float *)(iVar6 + 0xe0) * local_178) / local_160) * local_148;
          if (local_16c < local_148) {
            local_158 = local_150;
            local_16c = local_148;
          }
        }
      }
    }
  }
  if (local_158 == 0) {
    *(undefined4 *)(local_14c + 0xf0) = 0;
  }
  else {
    uVar5 = FUN_00462380();
    *(undefined4 *)(local_14c + 0xf0) = uVar5;
  }
  FUN_0083e885();
  return;
}

