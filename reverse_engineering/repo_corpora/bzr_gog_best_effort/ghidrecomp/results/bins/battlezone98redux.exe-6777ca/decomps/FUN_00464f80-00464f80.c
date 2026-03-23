
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00464f80(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,float param_7,undefined4 param_8,
                 float param_9,float param_10,float param_11,undefined4 *param_12,float param_13,
                 int param_14)

{
  undefined4 *puVar1;
  float *pfVar2;
  float10 fVar3;
  undefined1 local_b8 [12];
  undefined1 local_ac [24];
  undefined1 local_94 [12];
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  float local_3c;
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
  local_58 = 0.0;
  local_5c = param_9;
  local_54 = -param_7;
  param_5 = 0;
  param_2 = 0;
  puVar1 = (undefined4 *)FUN_004401a0(local_94,param_1,0,param_3);
  local_50 = *puVar1;
  local_4c = puVar1[1];
  local_48 = puVar1[2];
  local_14 = local_50;
  local_10 = local_4c;
  local_c = local_48;
  puVar1 = (undefined4 *)FUN_004401a0(local_ac,param_4,param_5,param_6);
  local_38 = *puVar1;
  local_28 = puVar1[1];
  local_30 = puVar1[2];
  local_34 = 0;
  local_2c = local_38;
  local_24 = local_30;
  FUN_004428b0();
  fVar3 = (float10)FUN_00417910();
  local_70 = (float)fVar3;
  if (0.0001 <= local_70) {
    fVar3 = (float10)FUN_004428b0();
    local_84 = (float)fVar3;
    local_68 = local_84 / local_70;
    fVar3 = (float10)FUN_004428b0();
    local_80 = (float)fVar3;
    local_78 = local_80;
    FUN_004428b0();
    fVar3 = (float10)FUN_00417910();
    local_7c = (float)fVar3;
    local_6c = local_78 / local_7c;
    local_64 = DAT_008e794c * param_13;
    fVar3 = (float10)FUN_00453f80();
    local_88 = (float)fVar3;
    if ((((local_88 <= local_64) && (0.0 < local_6c)) && (local_6c <= DAT_008e7934 * param_10)) &&
       (0.0 < param_10)) {
      fVar3 = (float10)FUN_004428b0();
      local_74 = (float)fVar3;
      if (local_68 <= 0.0) {
        local_60 = local_64 + local_68;
      }
      else {
        local_60 = -(local_64 - local_68);
      }
      local_60 = local_60 / local_64;
      local_60 = local_60 * _DAT_008e7950;
      pfVar2 = (float *)FUN_004621a0();
      local_5c = *pfVar2;
      local_58 = pfVar2[1];
      local_54 = pfVar2[2];
      local_44 = local_5c;
      local_40 = local_58;
      local_3c = local_54;
      if (local_74 <= param_11 * param_11) {
        puVar1 = (undefined4 *)FUN_00439d00(local_b8,*param_12,param_12[1],param_12[2],local_60);
        local_20 = *puVar1;
        local_1c = puVar1[1];
        local_18 = puVar1[2];
        *param_12 = local_20;
        param_12[1] = local_1c;
        param_12[2] = local_18;
      }
      if (param_14 != 0) {
        FUN_007d6a70(" Lx: %f Lz: %f\n",(double)(local_60 * local_5c));
      }
    }
  }
  FUN_0083e885();
  return;
}

