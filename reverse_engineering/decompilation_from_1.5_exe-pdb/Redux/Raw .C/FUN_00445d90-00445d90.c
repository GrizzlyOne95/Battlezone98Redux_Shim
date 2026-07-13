
void FUN_00445d90(undefined4 param_1,undefined4 param_2,undefined4 param_3,float param_4,
                 float param_5,float param_6,float param_7,float param_8,float param_9,
                 float param_10,float param_11,float param_12,float param_13,float *param_14,
                 undefined4 *param_15,float param_16)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_78 [12];
  undefined1 local_6c [12];
  undefined1 local_60 [12];
  undefined1 local_54 [12];
  undefined1 local_48 [12];
  undefined1 local_3c [12];
  float local_30;
  int local_2c;
  int local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_2c = 0;
  iVar1 = FUN_004461b0(param_1,param_4,param_7 - param_16,param_10 + param_16,&local_18,&local_1c);
  if ((iVar1 != 0) &&
     (iVar1 = FUN_004461b0(param_3,param_6,param_9 - param_16,param_12 + param_16,&local_24,
                           &local_20), iVar1 != 0)) {
    if (local_18 < local_24) {
      local_18 = local_24;
      local_2c = 1;
    }
    if (local_20 < local_1c) {
      local_1c = local_20;
    }
    iVar1 = FUN_004461b0(param_2,param_5,param_8 - param_16,param_11 + param_16,&local_24,&local_20)
    ;
    if (iVar1 != 0) {
      if (local_18 < local_24) {
        local_18 = local_24;
        local_2c = 2;
      }
      if (local_20 < local_1c) {
        local_1c = local_20;
      }
      if (((local_18 <= local_1c) && (0.0 <= local_1c)) && (local_18 <= param_13)) {
        local_28 = local_2c;
        if (local_2c == 0) {
          if (param_4 <= 0.0) {
            puVar2 = (undefined4 *)FUN_00440000(local_54,0x3f800000,0,0);
            local_14 = *puVar2;
            local_10 = puVar2[1];
            local_c = puVar2[2];
          }
          else {
            puVar2 = (undefined4 *)FUN_00440000(local_6c,0xbf800000,0,0);
            local_14 = *puVar2;
            local_10 = puVar2[1];
            local_c = puVar2[2];
          }
        }
        else if (local_2c == 1) {
          if (param_6 <= 0.0) {
            puVar2 = (undefined4 *)FUN_00440000(local_48,0,0,0x3f800000);
            local_14 = *puVar2;
            local_10 = puVar2[1];
            local_c = puVar2[2];
          }
          else {
            puVar2 = (undefined4 *)FUN_00440000(local_3c,0,0,0xbf800000);
            local_14 = *puVar2;
            local_10 = puVar2[1];
            local_c = puVar2[2];
          }
        }
        else if (local_2c == 2) {
          if (param_5 <= 0.0) {
            puVar2 = (undefined4 *)FUN_00440000(local_78,0,0x3f800000,0);
            local_14 = *puVar2;
            local_10 = puVar2[1];
            local_c = puVar2[2];
          }
          else {
            puVar2 = (undefined4 *)FUN_00440000(local_60,0,0xbf800000,0);
            local_14 = *puVar2;
            local_10 = puVar2[1];
            local_c = puVar2[2];
          }
        }
        if (local_18 < 0.0) {
          fVar3 = (float10)FUN_004428b0(&param_4,&local_14);
          local_30 = (float)fVar3;
          if (param_16 + 0.1 < local_30 * local_18) goto LAB_00446196;
        }
        *param_14 = local_18;
        *param_15 = local_14;
        param_15[1] = local_10;
        param_15[2] = local_c;
      }
    }
  }
LAB_00446196:
  FUN_0083e885();
  return;
}

