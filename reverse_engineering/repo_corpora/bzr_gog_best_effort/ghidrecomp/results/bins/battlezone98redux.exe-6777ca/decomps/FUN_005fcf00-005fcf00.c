
void FUN_005fcf00(undefined4 *param_1,int param_2,undefined4 *param_3,int param_4)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_ec [12];
  undefined1 local_e0 [12];
  undefined1 local_d4 [12];
  undefined1 local_c8 [12];
  undefined1 local_bc [24];
  undefined1 local_a4 [12];
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
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
  (**(code **)(*(int *)(param_2 + 0x18) + 0xc))();
  puVar1 = (undefined4 *)FUN_004401a0(local_a4,*param_3,param_3[1],param_3[2]);
  local_74 = *puVar1;
  local_70 = puVar1[1];
  local_6c = puVar1[2];
  local_20 = local_74;
  local_1c = local_70;
  local_18 = local_6c;
  fVar2 = (float10)FUN_004428b0();
  local_98 = (float)fVar2;
  local_84 = local_98 + 0.0001;
  if (local_84 <= 0.0) {
    local_88 = 0.0;
    puVar1 = (undefined4 *)FUN_00440000();
    local_68 = *puVar1;
    local_64 = puVar1[1];
    local_60 = puVar1[2];
    local_44 = local_68;
    local_40 = local_64;
    local_3c = local_60;
  }
  else {
    fVar2 = (float10)FUN_00417910();
    local_88 = (float)fVar2;
    fVar2 = (float10)FUN_00820570((double)local_84);
    local_90 = (float)fVar2;
    puVar1 = (undefined4 *)FUN_004462d0(local_e0,local_90);
    local_80 = *puVar1;
    local_7c = puVar1[1];
    local_78 = puVar1[2];
    local_8c = local_88 * 1.0;
    local_38 = local_80;
    local_34 = local_7c;
    local_30 = local_78;
    puVar1 = (undefined4 *)FUN_004462d0(local_c8,local_8c);
    local_68 = *puVar1;
    local_64 = puVar1[1];
    local_60 = puVar1[2];
    local_14 = local_68;
    local_10 = local_64;
    local_c = local_60;
  }
  if (param_4 != 0) {
    (**(code **)(*(int *)(param_4 + 0x18) + 0xc))();
    puVar1 = (undefined4 *)(**(code **)(*(int *)(param_2 + 0x18) + 0xc))();
    puVar1 = (undefined4 *)FUN_004401a0(local_bc,*puVar1,puVar1[1],puVar1[2]);
    local_74 = *puVar1;
    local_70 = puVar1[1];
    local_6c = puVar1[2];
    local_5c = local_74;
    local_58 = local_70;
    local_54 = local_6c;
    fVar2 = (float10)FUN_004428b0();
    local_84 = (float)fVar2;
    if ((0.0 < local_84) && (local_84 < 2500.0)) {
      fVar2 = (float10)FUN_00820570((double)local_84);
      local_94 = (float)fVar2;
      puVar1 = (undefined4 *)FUN_004462d0(local_d4,local_94);
      local_80 = *puVar1;
      local_7c = puVar1[1];
      local_78 = puVar1[2];
      local_8c = 1.0 / (local_84 * 5e-05);
      local_50 = local_80;
      local_4c = local_7c;
      local_48 = local_78;
      puVar1 = (undefined4 *)FUN_00439d00(local_ec,local_68,local_64,local_60,local_8c);
      local_68 = *puVar1;
      local_64 = puVar1[1];
      local_60 = puVar1[2];
      local_2c = local_68;
      local_28 = local_64;
      local_24 = local_60;
    }
  }
  FUN_004675f0();
  *param_1 = local_68;
  param_1[1] = local_64;
  param_1[2] = local_60;
  FUN_0083e885();
  return;
}

