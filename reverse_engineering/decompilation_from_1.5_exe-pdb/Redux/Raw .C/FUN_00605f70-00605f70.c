
void __fastcall FUN_00605f70(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  float10 fVar3;
  undefined1 local_19c [24];
  undefined1 local_184 [24];
  undefined1 local_16c [12];
  undefined1 local_160 [12];
  undefined1 local_154 [24];
  undefined1 local_13c [48];
  float local_10c;
  float local_108;
  undefined4 local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  undefined4 local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float *local_d0;
  int local_cc;
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
  local_d0 = (float *)(*(int *)(*(int *)(param_1 + 0x10) + 0x230) + 0xc4);
  local_cc = param_1;
  local_104 = FUN_0045c4d0();
  puVar1 = (undefined4 *)FUN_004462d0();
  local_80 = *puVar1;
  local_7c = puVar1[1];
  local_78 = puVar1[2];
  FUN_00607110();
  puVar1 = (undefined4 *)FUN_00440210();
  local_bc = *puVar1;
  local_b8 = puVar1[1];
  local_b4 = puVar1[2];
  local_50 = local_bc;
  local_4c = local_b8;
  local_48 = local_b4;
  if (*(int *)(local_cc + 0x18) == 0) {
    local_e0 = 0;
  }
  else {
    iVar2 = FUN_00462400();
    local_e0 = *(undefined4 *)(iVar2 + 0xc);
  }
  FUN_00417910();
  FUN_00417910();
  FUN_00462400();
  fVar3 = (float10)FUN_00447ed0();
  local_10c = (float)fVar3;
  fVar3 = (float10)FUN_00417910();
  local_e4 = (float)fVar3;
  local_d4 = local_e4 - local_10c;
  if (*(float *)(local_cc + 0xd4) <= *(float *)(local_cc + 0x9c) &&
      *(float *)(local_cc + 0x9c) != *(float *)(local_cc + 0xd4)) {
    local_d4 = local_d4 - (1.0 - *(float *)(local_cc + 0xd4) / *(float *)(local_cc + 0x9c)) * 40.0;
  }
  puVar1 = (undefined4 *)FUN_004462d0();
  local_98 = *puVar1;
  local_94 = puVar1[1];
  local_90 = puVar1[2];
  local_20 = local_98;
  local_1c = local_94;
  local_18 = local_90;
  if (2.0 <= *(float *)(local_cc + 0x98)) {
    fVar3 = (float10)FUN_00822d80();
    local_108 = (float)fVar3;
    local_f0 = local_108;
    fVar3 = (float10)FUN_0046d040();
    local_100 = (float)fVar3;
    if (local_f0 - local_100 < 10.0) {
      FUN_005fdf60();
    }
  }
  if (3.0 <= *(float *)(local_cc + 0x98)) {
    puVar1 = (undefined4 *)FUN_00440000();
    local_8c = *puVar1;
    local_88 = puVar1[1];
    local_84 = puVar1[2];
    local_2c = local_8c;
    local_28 = local_88;
    local_24 = local_84;
    if (*(int *)(local_cc + 0x18) != 0) {
      puVar1 = (undefined4 *)FUN_005fd330();
      local_a4 = *puVar1;
      local_a0 = puVar1[1];
      local_9c = puVar1[2];
      puVar1 = (undefined4 *)FUN_00440130(local_160,local_8c);
      local_8c = *puVar1;
      local_88 = puVar1[1];
      local_84 = puVar1[2];
      local_44 = local_8c;
      local_40 = local_88;
      local_3c = local_84;
    }
    if (4.0 <= *(float *)(local_cc + 0x98)) {
      puVar1 = (undefined4 *)FUN_005fd5f0();
      local_c8 = *puVar1;
      local_c4 = puVar1[1];
      local_c0 = puVar1[2];
      puVar1 = (undefined4 *)FUN_00440130(local_13c,local_8c);
      local_8c = *puVar1;
      local_88 = puVar1[1];
      local_84 = puVar1[2];
      local_5c = local_8c;
      local_58 = local_88;
      local_54 = local_84;
    }
    fVar3 = (float10)FUN_00822d60();
    local_f8 = (float)fVar3;
    puVar1 = (undefined4 *)FUN_004401a0(local_154,local_8c);
    local_b0 = *puVar1;
    local_ac = puVar1[1];
    local_a8 = puVar1[2];
    puVar1 = (undefined4 *)
             FUN_00439d00(local_16c,*(undefined4 *)(local_cc + 0x128),
                          *(undefined4 *)(local_cc + 300));
    local_74 = *puVar1;
    local_70 = puVar1[1];
    local_6c = puVar1[2];
    *(undefined4 *)(local_cc + 0x128) = local_74;
    *(undefined4 *)(local_cc + 300) = local_70;
    *(undefined4 *)(local_cc + 0x130) = local_6c;
    puVar1 = (undefined4 *)FUN_00440130(local_184,local_98);
    local_98 = *puVar1;
    local_94 = puVar1[1];
    local_90 = puVar1[2];
    local_68 = local_98;
    local_64 = local_94;
    local_60 = local_90;
  }
  puVar1 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_cc + 0x10) + 0x18) + 0xc))();
  puVar1 = (undefined4 *)FUN_00440130(local_19c,*puVar1);
  local_38 = *puVar1;
  local_34 = puVar1[1];
  local_30 = puVar1[2];
  local_14 = local_38;
  local_10 = local_34;
  local_c = local_30;
  FUN_00465320(*(undefined4 *)(local_cc + 0x10),*(undefined4 *)(local_cc + 0x80),0x42200000);
  FUN_004675f0();
  FUN_00606f70();
  fVar3 = (float10)FUN_0045c420();
  local_e8 = (float)fVar3;
  if (local_e8 < 1.0) {
    local_d0[3] = 0.0;
    local_d0[2] = 0.0;
  }
  if (local_d0[3] == 1.0) {
    local_d0[4] = 1.4013e-45;
  }
  if (*(float *)(local_cc + 0x98) <= 4.0 && *(float *)(local_cc + 0x98) != 4.0) {
    fVar3 = (float10)FUN_00822d80();
    local_ec = (float)fVar3;
    local_d8 = local_ec * 0.5;
    local_dc = 0.2 - *(float *)(local_cc + 0x98) * 0.05;
    fVar3 = (float10)FUN_00822970();
    local_f4 = (float)fVar3;
    fVar3 = (float10)FUN_00447ed0();
    local_d0[1] = (float)fVar3;
    fVar3 = (float10)FUN_00822970();
    local_fc = (float)fVar3;
    fVar3 = (float10)FUN_00447ed0();
    *local_d0 = (float)fVar3;
  }
  FUN_0083e885();
  return;
}

