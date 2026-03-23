
void FUN_00443370(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 float param_13,float param_14,float *param_15,undefined4 *param_16)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_84 [12];
  undefined1 local_78 [12];
  undefined1 local_6c [12];
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
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
  iVar1 = FUN_00442850(param_4,param_5,param_6);
  if ((iVar1 == 0) || (iVar1 = FUN_00442850(param_10,param_11,param_12), iVar1 == 0)) {
    local_50 = param_4;
    local_4c = param_5;
    local_48 = param_6;
    local_44 = param_10;
    local_40 = param_11;
    local_3c = param_12;
    local_2c = param_1;
    local_28 = param_2;
    local_24 = param_3;
    local_38 = param_7;
    local_34 = param_8;
    local_30 = param_9;
    puVar2 = (undefined4 *)FUN_004401a0(local_6c,param_7,param_8,param_9,param_1,param_2,param_3);
    local_14 = *puVar2;
    local_10 = puVar2[1];
    local_c = puVar2[2];
    puVar2 = (undefined4 *)
             FUN_004401a0(local_78,local_50,local_4c,local_48,local_44,local_40,local_3c);
    local_20 = *puVar2;
    local_1c = puVar2[1];
    local_18 = puVar2[2];
    fVar3 = (float10)FUN_004428b0(&local_20,&local_20);
    local_58 = (float)fVar3;
    if (0.0001 <= local_58) {
      fVar3 = (float10)FUN_004428b0(&local_14,&local_20);
      local_5c = (float)fVar3;
      local_54 = local_5c / local_58;
      if (param_14 < local_54) {
        local_54 = param_14;
      }
    }
    else {
      local_54 = param_14;
    }
    if (0.0 < local_54) {
      puVar2 = (undefined4 *)
               FUN_00439d00(local_84,local_14,local_10,local_c,-local_54,local_20,local_1c,local_18)
      ;
      local_14 = *puVar2;
      local_10 = puVar2[1];
      local_c = puVar2[2];
    }
    else {
      local_54 = 0.0;
    }
    *param_15 = local_54;
    fVar3 = (float10)FUN_004428b0(&local_14,&local_14);
    local_60 = (float)fVar3;
    if (local_60 <= param_13 * param_13) {
      *param_16 = local_14;
      param_16[1] = local_10;
      param_16[2] = local_c;
    }
  }
  FUN_0083e885();
  return;
}

