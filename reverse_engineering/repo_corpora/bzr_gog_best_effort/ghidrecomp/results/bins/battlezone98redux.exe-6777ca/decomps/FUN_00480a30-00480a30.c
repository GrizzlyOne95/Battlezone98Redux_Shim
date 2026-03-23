
void FUN_00480a30(undefined4 *param_1,undefined4 *param_2,float *param_3,undefined4 *param_4,
                 int param_5,float param_6)

{
  undefined4 *puVar1;
  float *pfVar2;
  int iVar3;
  float10 fVar4;
  undefined1 local_104 [24];
  undefined1 local_ec [12];
  undefined1 local_e0 [12];
  undefined1 local_d4 [12];
  undefined1 local_c8 [12];
  undefined1 local_bc [4];
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  int local_a0;
  float local_9c;
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
  float local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_a0 = (**(code **)(*(int *)(param_5 + 0x18) + 0x2c))();
  puVar1 = (undefined4 *)(**(code **)(*(int *)(param_5 + 0x18) + 0xc))();
  pfVar2 = (float *)FUN_004401a0(local_ec,*param_1,param_1[1],param_1[2],*puVar1,puVar1[1],puVar1[2]
                                );
  local_98 = *pfVar2;
  local_94 = pfVar2[1];
  local_90 = pfVar2[2];
  local_14 = local_98;
  local_10 = local_94;
  local_c = local_90;
  puVar1 = (undefined4 *)FUN_004624b0();
  pfVar2 = (float *)FUN_004401a0(local_c8,*param_2,param_2[1],param_2[2],*puVar1,puVar1[1],puVar1[2]
                                );
  local_8c = *pfVar2;
  local_88 = pfVar2[1];
  local_84 = pfVar2[2];
  local_20 = local_8c;
  local_1c = local_88;
  local_18 = local_84;
  if (*(int *)(local_a0 + 0x24) == 3) {
    puVar1 = (undefined4 *)FUN_004801a0(local_104,param_1,*param_3,param_2);
    local_80 = *puVar1;
    local_7c = puVar1[1];
    local_78 = puVar1[2];
    local_74 = puVar1[3];
    local_70 = puVar1[4];
    local_6c = puVar1[5];
    local_5c = local_80;
    local_58 = local_7c;
    local_54 = local_78;
    local_50 = local_74;
    local_4c = local_70;
    local_48 = local_6c;
    iVar3 = FUN_00442fd0(&local_80,local_a0);
    if (iVar3 != 0) {
      local_44 = *param_1;
      local_40 = param_1[1];
      local_3c = param_1[2];
      local_38 = local_8c;
      local_34 = local_88;
      local_30 = local_84;
      FUN_00445380(local_44,local_40,local_3c,local_8c,local_88,local_84,local_a0,*param_3,local_bc,
                   param_3,param_4,param_6,0);
    }
  }
  else {
    local_a8 = local_98 * local_8c + local_94 * local_88 + local_90 * local_84;
    if (local_a8 < 0.0) {
      local_b8 = local_98 * local_98 + local_94 * local_94 + local_90 * local_90;
      local_ac = local_8c * local_8c + local_88 * local_88 + local_84 * local_84;
      local_9c = *(float *)(local_a0 + 0x14);
      if (*(int *)(local_a0 + 0x24) != 3) {
        local_9c = local_9c * 0.75;
      }
      local_9c = local_9c + param_6;
      local_b0 = local_a8 * local_a8 - (local_b8 - local_9c * local_9c) * local_ac;
      if (0.0 <= local_b0) {
        fVar4 = (float10)FUN_00417910(local_b0);
        local_b4 = (float)fVar4;
        local_a4 = -(local_b4 + local_a8);
        if (local_a4 < *param_3 * local_ac) {
          local_a4 = local_a4 / local_ac;
          *param_3 = local_a4;
          puVar1 = (undefined4 *)
                   FUN_00439d00(local_d4,local_98,local_94,local_90,local_a4,local_8c,local_88,
                                local_84);
          local_2c = *puVar1;
          local_28 = puVar1[1];
          local_24 = puVar1[2];
          *param_4 = local_2c;
          param_4[1] = local_28;
          param_4[2] = local_24;
          puVar1 = (undefined4 *)FUN_004621a0(local_e0,param_4);
          local_68 = *puVar1;
          local_64 = puVar1[1];
          local_60 = puVar1[2];
          *param_4 = local_68;
          param_4[1] = local_64;
          param_4[2] = local_60;
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

