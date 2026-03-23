
void FUN_006a49c0(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 *param_5,
                 float *param_6)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_a4 [12];
  undefined1 local_98 [12];
  undefined1 local_8c [12];
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  int local_5c;
  int local_58;
  int local_54;
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
  local_5c = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_64 = 0.0;
  for (local_54 = 0; local_54 < param_2; local_54 = local_54 + 1) {
    if (*(char *)(param_1 + 4 + local_54 * 8) != '\0') {
      local_58 = *(int *)(param_1 + local_54 * 8);
      puVar1 = (undefined4 *)(**(code **)(*(int *)(local_58 + 0x18) + 0xc))();
      local_50 = *puVar1;
      local_4c = puVar1[1];
      local_48 = puVar1[2];
      puVar1 = (undefined4 *)
               FUN_00440130(local_8c,local_44,local_40,local_3c,local_50,local_4c,local_48);
      local_44 = *puVar1;
      local_40 = puVar1[1];
      local_3c = puVar1[2];
      local_5c = local_5c + 1;
      local_2c = local_44;
      local_28 = local_40;
      local_24 = local_3c;
    }
  }
  if (local_5c < 2) {
    *param_6 = 0.0;
  }
  else {
    puVar1 = (undefined4 *)FUN_004462d0(local_98,1.0 / (float)local_5c,local_44,local_40,local_3c);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    *param_5 = local_20;
    param_5[1] = local_1c;
    param_5[2] = local_18;
    local_60 = 0.0;
    for (local_54 = 0; local_54 < param_2; local_54 = local_54 + 1) {
      if (*(char *)(param_1 + 4 + local_54 * 8) != '\0') {
        local_58 = *(int *)(param_1 + local_54 * 8);
        puVar1 = (undefined4 *)(**(code **)(*(int *)(local_58 + 0x18) + 0xc))();
        local_50 = *puVar1;
        local_4c = puVar1[1];
        local_48 = puVar1[2];
        puVar1 = (undefined4 *)
                 FUN_004401a0(local_a4,*param_5,param_5[1],param_5[2],local_50,local_4c,local_48);
        local_38 = *puVar1;
        local_34 = puVar1[1];
        local_30 = puVar1[2];
        local_14 = local_38;
        local_10 = local_34;
        local_c = local_30;
        fVar2 = (float10)FUN_006a0730(local_38);
        local_80 = (float)fVar2;
        local_74 = local_80;
        fVar2 = (float10)FUN_006a0730(local_30);
        local_7c = (float)fVar2;
        local_6c = local_74 + local_7c;
        fVar2 = (float10)FUN_00453f80(local_64);
        local_78 = (float)fVar2;
        if (local_78 <= 8.0) {
          local_64 = 8.0;
        }
        local_68 = local_6c / local_64;
        if (local_60 < local_68) {
          local_60 = local_68;
        }
      }
    }
    fVar2 = (float10)FUN_00822d80();
    local_70 = (float)fVar2;
    *param_6 = local_70 + local_60;
  }
  FUN_0083e885();
  return;
}

