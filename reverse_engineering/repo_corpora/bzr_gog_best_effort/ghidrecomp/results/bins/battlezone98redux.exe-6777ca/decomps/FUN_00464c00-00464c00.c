
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00464c00(int param_1,int param_2,float param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6)

{
  undefined4 *puVar1;
  uint *puVar2;
  float10 fVar3;
  undefined1 local_d0 [12];
  undefined1 local_c4 [12];
  undefined1 local_b8 [12];
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
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
  uint local_38 [3];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar3 = (float10)FUN_00462470();
  local_a4 = (float)fVar3;
  local_98 = local_a4;
  fVar3 = (float10)FUN_00462470();
  local_94 = (float)fVar3;
  local_a8 = (local_a4 + local_94) * _DAT_008e7938;
  fVar3 = (float10)FUN_004624d0();
  local_80 = (float)fVar3;
  puVar1 = (undefined4 *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  local_68 = *puVar1;
  local_64 = puVar1[1];
  local_60 = puVar1[2];
  puVar1 = (undefined4 *)(**(code **)(*(int *)(param_2 + 0x18) + 0xc))();
  local_74 = *puVar1;
  local_70 = puVar1[1];
  local_6c = puVar1[2];
  puVar2 = (uint *)FUN_004401a0(local_b8,param_4,param_5,param_6,local_68,local_64,local_60);
  local_20 = *puVar2;
  local_1c = puVar2[1];
  local_38[0] = puVar2[2];
  local_38[1] = 0;
  local_38[2] = local_20 ^ 0x80000000;
  local_70 = 0;
  local_64 = 0;
  local_18 = local_38[0];
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_38[0];
  puVar1 = (undefined4 *)FUN_004401a0(local_c4,local_68,0,local_60,local_74,0,local_6c);
  local_5c = *puVar1;
  local_58 = puVar1[1];
  local_54 = puVar1[2];
  local_50 = local_5c;
  local_4c = local_58;
  local_48 = local_54;
  puVar1 = (undefined4 *)
           FUN_004401a0(local_d0,local_74,local_70,local_6c,local_68,local_64,local_60);
  local_44 = *puVar1;
  local_40 = puVar1[1];
  local_3c = puVar1[2];
  local_28 = 0;
  local_2c = local_44;
  local_24 = local_3c;
  fVar3 = (float10)FUN_004428b0(local_38,local_38);
  fVar3 = (float10)FUN_00417910((float)fVar3);
  local_84 = (float)fVar3;
  if (0.0001 <= local_84) {
    fVar3 = (float10)FUN_004428b0(local_38,&local_2c);
    local_ac = (float)fVar3;
    local_8c = local_ac / local_84;
    fVar3 = (float10)FUN_004428b0(&local_14,&local_14);
    fVar3 = (float10)FUN_00417910((float)fVar3);
    local_78 = (float)fVar3;
    fVar3 = (float10)FUN_004428b0(&local_14,&local_2c);
    local_9c = (float)fVar3;
    local_7c = local_9c / local_78;
    local_90 = DAT_008e794c * local_a8;
    fVar3 = (float10)FUN_00453f80(local_8c);
    local_88 = (float)fVar3;
    if ((((local_88 <= local_90) && (0.0 < local_7c)) && (local_7c <= param_3 * local_80)) &&
       (0.0 < local_80)) {
      fVar3 = (float10)FUN_004428b0(&local_5c,&local_5c);
      local_a0 = (float)fVar3;
    }
  }
  FUN_0083e885();
  return;
}

