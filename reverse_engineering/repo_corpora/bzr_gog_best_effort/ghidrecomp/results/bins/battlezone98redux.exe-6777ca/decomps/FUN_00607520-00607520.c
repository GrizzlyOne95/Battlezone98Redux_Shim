
void FUN_00607520(void)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_190 [60];
  undefined1 local_154 [12];
  undefined1 local_148 [12];
  undefined1 local_13c [12];
  undefined1 local_130 [24];
  undefined1 local_118 [12];
  undefined1 local_10c [24];
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float *local_dc;
  int local_d8;
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
  puVar1 = (undefined4 *)FUN_004462d0();
  local_8c = *puVar1;
  local_88 = puVar1[1];
  local_84 = puVar1[2];
  FUN_00607110();
  (**(code **)(*(int *)(*(int *)(local_d8 + 0x18) + 0x18) + 0xc))();
  puVar1 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_d8 + 0x10) + 0x18) + 0xc))();
  puVar1 = (undefined4 *)FUN_004401a0(local_154,*puVar1);
  local_98 = *puVar1;
  local_94 = puVar1[1];
  local_90 = puVar1[2];
  local_74 = local_98;
  local_70 = local_94;
  local_6c = local_90;
  if (2.0 <= *(float *)(local_d8 + 0x98)) {
    FUN_005fdf60();
    puVar1 = (undefined4 *)FUN_00440000();
    local_a4 = *puVar1;
    local_a0 = puVar1[1];
    local_9c = puVar1[2];
    local_50 = local_a4;
    local_4c = local_a0;
    local_48 = local_9c;
    if (*(int *)(local_d8 + 0x18) != 0) {
      puVar1 = (undefined4 *)FUN_005fd330();
      local_d4 = *puVar1;
      local_d0 = puVar1[1];
      local_cc = puVar1[2];
      puVar1 = (undefined4 *)FUN_00440130(local_13c,local_a4);
      local_a4 = *puVar1;
      local_a0 = puVar1[1];
      local_9c = puVar1[2];
      local_44 = local_a4;
      local_40 = local_a0;
      local_3c = local_9c;
    }
    if (4.0 <= *(float *)(local_d8 + 0x98)) {
      puVar1 = (undefined4 *)FUN_005fd5f0();
      local_c8 = *puVar1;
      local_c4 = puVar1[1];
      local_c0 = puVar1[2];
      puVar1 = (undefined4 *)FUN_00440130(local_10c,local_a4);
      local_a4 = *puVar1;
      local_a0 = puVar1[1];
      local_9c = puVar1[2];
      local_68 = local_a4;
      local_64 = local_a0;
      local_60 = local_9c;
    }
    fVar2 = (float10)FUN_00822d60();
    local_f0 = (float)fVar2;
    puVar1 = (undefined4 *)FUN_004401a0(local_118,local_a4);
    local_b0 = *puVar1;
    local_ac = puVar1[1];
    local_a8 = puVar1[2];
    puVar1 = (undefined4 *)
             FUN_00439d00(local_130,*(undefined4 *)(local_d8 + 0x128),
                          *(undefined4 *)(local_d8 + 300));
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    *(undefined4 *)(local_d8 + 0x128) = local_20;
    *(undefined4 *)(local_d8 + 300) = local_1c;
    *(undefined4 *)(local_d8 + 0x130) = local_18;
    puVar1 = (undefined4 *)FUN_00440130(local_148,local_98);
    local_98 = *puVar1;
    local_94 = puVar1[1];
    local_90 = puVar1[2];
    local_2c = local_98;
    local_28 = local_94;
    local_24 = local_90;
  }
  puVar1 = (undefined4 *)FUN_004621a0();
  local_bc = *puVar1;
  local_b8 = puVar1[1];
  local_b4 = puVar1[2];
  local_38 = local_bc;
  local_34 = local_b8;
  local_30 = local_b4;
  puVar1 = (undefined4 *)FUN_004462d0();
  local_98 = *puVar1;
  local_94 = puVar1[1];
  local_90 = puVar1[2];
  local_80 = local_98;
  local_7c = local_94;
  local_78 = local_90;
  puVar1 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_d8 + 0x10) + 0x18) + 0xc))();
  puVar1 = (undefined4 *)FUN_00440130(local_190,*puVar1);
  local_5c = *puVar1;
  local_58 = puVar1[1];
  local_54 = puVar1[2];
  local_14 = local_5c;
  local_10 = local_58;
  local_c = local_54;
  FUN_00465320(*(undefined4 *)(local_d8 + 0x10),*(undefined4 *)(local_d8 + 0x80),0x42200000);
  FUN_004675f0();
  local_dc = (float *)(*(int *)(*(int *)(local_d8 + 0x10) + 0x230) + 0xc4);
  FUN_00606f70();
  if (local_dc[3] == 1.0) {
    local_dc[4] = 1.4013e-45;
  }
  if (*(float *)(local_d8 + 0x98) <= 4.0 && *(float *)(local_d8 + 0x98) != 4.0) {
    fVar2 = (float10)FUN_00822d80();
    local_e8 = (float)fVar2;
    local_e4 = local_e8 * 0.5;
    local_e0 = 0.3 - *(float *)(local_d8 + 0x98) * 0.075;
    fVar2 = (float10)FUN_00822970();
    local_ec = (float)fVar2;
    fVar2 = (float10)FUN_00447ed0();
    local_dc[1] = (float)fVar2;
    fVar2 = (float10)FUN_00822970();
    local_f4 = (float)fVar2;
    fVar2 = (float10)FUN_00447ed0();
    *local_dc = (float)fVar2;
  }
  FUN_0083e885();
  return;
}

