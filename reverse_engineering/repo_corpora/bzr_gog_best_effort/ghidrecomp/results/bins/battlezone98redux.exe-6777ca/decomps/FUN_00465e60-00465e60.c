
void FUN_00465e60(undefined4 *param_1,int param_2,float param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_114 [24];
  undefined1 local_fc [24];
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  int local_c8;
  int local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90 [16];
  float local_50;
  undefined4 local_4c;
  float local_48;
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
  local_c4 = (**(code **)(*(int *)(param_2 + 0x18) + 0x30))();
  local_c8 = 0;
  iVar1 = FUN_0062df80();
  if (iVar1 == 0) {
    puVar2 = (undefined4 *)(**(code **)(*(int *)(param_2 + 0x18) + 0xc))();
    *param_1 = *puVar2;
    param_1[1] = puVar2[1];
    param_1[2] = puVar2[2];
  }
  else {
    local_c8 = FUN_0045c4f0();
    local_b8 = *(float *)(local_c8 + 0x2c);
    puVar2 = (undefined4 *)(local_c4 + 0x20);
    puVar3 = local_90;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar2 = (undefined4 *)FUN_00439de0();
    local_9c = *puVar2;
    local_98 = puVar2[1];
    local_94 = puVar2[2];
    local_38 = local_9c;
    local_34 = local_98;
    local_30 = local_94;
    puVar2 = (undefined4 *)FUN_004624b0();
    local_b4 = *puVar2;
    local_b0 = puVar2[1];
    local_ac = puVar2[2];
    fVar4 = (float10)FUN_004624d0();
    local_dc = (float)fVar4;
    fVar4 = (float10)FUN_00453f80();
    local_e0 = (float)fVar4;
    if (0.05 <= local_e0) {
      if (local_b8 <= 0.0) {
        local_d0 = 1.0;
      }
      else {
        local_d0 = -1.0;
      }
      local_c0 = local_d0;
      fVar4 = (float10)FUN_00453f80();
      local_d4 = (float)fVar4;
      local_bc = local_dc / local_d4;
      local_cc = local_c0 * local_b8 * param_3 - local_c0 * 3.1415927 * 0.5;
      fVar4 = (float10)FUN_004178f0();
      local_d8 = (float)fVar4;
      local_50 = local_d8 * local_bc;
      local_4c = 0;
      fVar4 = (float10)FUN_004178b0();
      local_e4 = (float)fVar4;
      local_48 = local_e4 * local_bc;
      puVar2 = (undefined4 *)FUN_00439d80();
      local_a8 = *puVar2;
      local_28 = puVar2[1];
      local_a0 = puVar2[2];
      local_a4 = 0;
      local_2c = local_a8;
      local_24 = local_a0;
      puVar2 = (undefined4 *)FUN_00439d00(local_fc,local_9c,local_98,local_94,local_c0 * local_bc);
      local_9c = *puVar2;
      local_98 = puVar2[1];
      local_94 = puVar2[2];
      local_44 = local_9c;
      local_40 = local_98;
      local_3c = local_94;
      FUN_00462160();
      FUN_00820180(&local_14);
    }
    else {
      puVar2 = (undefined4 *)FUN_00439d00(local_114,local_9c,local_98,local_94,param_3);
      local_20 = *puVar2;
      local_1c = puVar2[1];
      local_18 = puVar2[2];
      local_14 = local_20;
      local_10 = local_1c;
      local_c = local_18;
    }
    *param_1 = local_14;
    param_1[1] = local_10;
    param_1[2] = local_c;
  }
  FUN_0083e885();
  return;
}

