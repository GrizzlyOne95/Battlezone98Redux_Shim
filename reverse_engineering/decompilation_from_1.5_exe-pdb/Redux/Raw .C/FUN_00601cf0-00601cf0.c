
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00601cf0(int param_1,undefined4 *param_2,char param_3)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_168 [24];
  undefined1 local_150 [12];
  undefined1 local_144 [12];
  undefined1 local_138 [12];
  undefined1 local_12c [12];
  undefined1 local_120 [12];
  undefined1 local_114 [24];
  undefined1 local_fc [12];
  float local_f0;
  float local_ec;
  float local_e8;
  uint local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  char local_cd;
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
  local_cc = param_1;
  puVar2 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
  local_a4 = *puVar2;
  local_9c = puVar2[2];
  local_a0 = 0;
  iVar1 = *(int *)(*(int *)(local_cc + 0x40) + 8);
  puVar2 = (undefined4 *)
           FUN_004e5270(local_114,*(undefined4 *)(iVar1 + *(int *)(local_cc + 0x44) * 8),
                        *(undefined4 *)(iVar1 + 4 + *(int *)(local_cc + 0x44) * 8));
  local_8c = *puVar2;
  local_88 = puVar2[1];
  local_84 = puVar2[2];
  local_cd = *(int *)(local_cc + 0x44) == *(int *)(*(int *)(local_cc + 0x40) + 4) + -1;
  local_e4 = (uint)(byte)local_cd;
  local_5c = local_8c;
  local_58 = local_88;
  local_54 = local_84;
  fVar3 = (float10)FUN_00462010(&local_a4,local_cc + 0x28);
  local_d4 = (float)fVar3;
  if (local_d4 <= 400.0) {
    fVar3 = (float10)FUN_00417910(local_d4);
    local_d4 = (float)fVar3;
  }
  else {
    local_d4 = 20.0;
  }
  puVar2 = (undefined4 *)
           FUN_004401a0(local_fc,local_8c,local_88,local_84,local_a4,local_a0,local_9c);
  local_98 = *puVar2;
  local_10 = puVar2[1];
  local_90 = puVar2[2];
  local_94 = 0;
  local_14 = local_98;
  local_c = local_90;
  fVar3 = (float10)FUN_004428b0(&local_98,&local_98);
  local_e0 = (float)fVar3;
  if (local_e0 <= 0.0) {
    local_d8 = 0.0;
    puVar2 = (undefined4 *)FUN_00440000();
    local_80 = *puVar2;
    local_7c = puVar2[1];
    local_78 = puVar2[2];
    local_50 = local_80;
    local_4c = local_7c;
    local_48 = local_78;
  }
  else {
    fVar3 = (float10)FUN_00417910(local_e0);
    local_d8 = (float)fVar3;
    fVar3 = (float10)FUN_00820570((double)local_e0,local_98,local_94,local_90);
    local_ec = (float)fVar3;
    puVar2 = (undefined4 *)FUN_004462d0(local_144,local_ec);
    local_b0 = *puVar2;
    local_ac = puVar2[1];
    local_a8 = puVar2[2];
    local_dc = local_d4 * _DAT_008e7968;
    if (local_cd != '\0') {
      local_dc = local_dc * _DAT_008e796c;
    }
    local_2c = local_b0;
    local_28 = local_ac;
    local_24 = local_a8;
    puVar2 = (undefined4 *)FUN_004462d0(local_12c,local_dc,local_b0,local_ac,local_a8);
    local_80 = *puVar2;
    local_7c = puVar2[1];
    local_78 = puVar2[2];
    local_38 = local_80;
    local_34 = local_7c;
    local_30 = local_78;
  }
  if (DAT_008e7948 <= local_d8) {
    local_e8 = DAT_008e7948;
  }
  else {
    local_e8 = local_d8;
  }
  FUN_00465320(*(undefined4 *)(local_cc + 0x10),*(undefined4 *)(local_cc + 0x80),local_e8,local_8c,
               local_88,local_84,&local_80,0);
  if (4.0 <= *(float *)(local_cc + 0x98)) {
    puVar2 = (undefined4 *)FUN_005fd5f0();
    local_c8 = *puVar2;
    local_c4 = puVar2[1];
    local_c0 = puVar2[2];
    local_74 = local_c8;
    local_70 = local_c4;
    local_6c = local_c0;
    fVar3 = (float10)FUN_00822d60();
    local_f0 = (float)fVar3;
    puVar2 = (undefined4 *)
             FUN_004401a0(local_120,local_c8,local_c4,local_c0,*(undefined4 *)(local_cc + 0x128),
                          *(undefined4 *)(local_cc + 300),*(undefined4 *)(local_cc + 0x130));
    local_bc = *puVar2;
    local_b8 = puVar2[1];
    local_b4 = puVar2[2];
    puVar2 = (undefined4 *)
             FUN_00439d00(local_138,*(undefined4 *)(local_cc + 0x128),
                          *(undefined4 *)(local_cc + 300),*(undefined4 *)(local_cc + 0x130),
                          local_f0 * 2.0,local_bc,local_b8,local_b4);
    local_68 = *puVar2;
    local_64 = puVar2[1];
    local_60 = puVar2[2];
    *(undefined4 *)(local_cc + 0x128) = local_68;
    *(undefined4 *)(local_cc + 300) = local_64;
    *(undefined4 *)(local_cc + 0x130) = local_60;
    puVar2 = (undefined4 *)
             FUN_00440130(local_150,local_80,local_7c,local_78,*(undefined4 *)(local_cc + 0x128),
                          *(undefined4 *)(local_cc + 300),*(undefined4 *)(local_cc + 0x130));
    local_80 = *puVar2;
    local_7c = puVar2[1];
    local_78 = puVar2[2];
    local_44 = local_80;
    local_40 = local_7c;
    local_3c = local_78;
  }
  if (param_3 == '\0') {
    FUN_004675f0();
  }
  if (local_cd != '\0') {
    puVar2 = (undefined4 *)FUN_004624b0();
    puVar2 = (undefined4 *)
             FUN_00439d00(local_168,local_80,local_7c,local_78,0xbe4ccccd,*puVar2,puVar2[1],
                          puVar2[2]);
    local_80 = *puVar2;
    local_7c = puVar2[1];
    local_78 = puVar2[2];
    local_20 = local_80;
    local_1c = local_7c;
    local_18 = local_78;
  }
  *param_2 = local_80;
  param_2[1] = local_7c;
  param_2[2] = local_78;
  FUN_0083e885();
  return;
}

