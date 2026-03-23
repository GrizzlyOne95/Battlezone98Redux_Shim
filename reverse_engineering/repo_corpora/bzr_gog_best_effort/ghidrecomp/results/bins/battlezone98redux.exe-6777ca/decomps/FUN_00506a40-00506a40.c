
void FUN_00506a40(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_13c [24];
  undefined1 local_124 [24];
  undefined1 local_10c [24];
  undefined1 local_f4 [24];
  undefined1 local_dc [12];
  float local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  int local_c0;
  int local_bc;
  undefined4 *local_b8;
  undefined4 local_b4;
  undefined4 *local_b0;
  undefined4 local_ac;
  int local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
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
  local_ac = 0;
  local_c0 = FUN_004ff820(param_1,1);
  if (local_c0 == 0) {
    local_b8 = (undefined4 *)FUN_004ff7a0(param_1,1);
    if (local_b8 == (undefined4 *)0x0) {
      iVar2 = FUN_0082c9f5(param_1,1);
      if (iVar2 == 0) {
        local_c4 = FUN_004ff750(param_1,1);
        local_a8 = FUN_00462630();
        if (local_a8 == 0) goto LAB_00506e32;
        local_ac = (**(code **)(*(int *)(local_a8 + 0x18) + 0x2c))();
        puVar1 = (undefined4 *)FUN_004c0af0();
        puVar1 = (undefined4 *)FUN_0049c4f0(local_13c,*puVar1,puVar1[1],puVar1[2]);
        local_38 = *puVar1;
        local_34 = puVar1[1];
        local_30 = puVar1[2];
        local_2c = puVar1[3];
        local_28 = puVar1[4];
        local_24 = puVar1[5];
        local_20 = local_38;
        local_1c = local_34;
        local_18 = local_30;
        local_14 = local_2c;
        local_10 = local_28;
        local_c = local_24;
      }
      else {
        local_cc = FUN_0082d377(param_1,1,0);
        local_c8 = FUN_0082c1fd(param_1,2,0);
        puVar1 = (undefined4 *)FUN_005c8bd0(local_dc,local_cc,local_c8);
        local_a4 = *puVar1;
        local_a0 = puVar1[1];
        local_9c = puVar1[2];
        puVar1 = (undefined4 *)FUN_0049c4f0(local_10c,local_a4,local_a0,local_9c);
        local_80 = *puVar1;
        local_7c = puVar1[1];
        local_78 = puVar1[2];
        local_74 = puVar1[3];
        local_70 = puVar1[4];
        local_6c = puVar1[5];
        local_20 = local_80;
        local_1c = local_7c;
        local_18 = local_78;
        local_14 = local_74;
        local_10 = local_70;
        local_c = local_6c;
      }
    }
    else {
      puVar1 = (undefined4 *)FUN_0049c4f0(local_124,*local_b8,local_b8[1],local_b8[2]);
      local_68 = *puVar1;
      local_64 = puVar1[1];
      local_60 = puVar1[2];
      local_5c = puVar1[3];
      local_58 = puVar1[4];
      local_54 = puVar1[5];
      local_20 = local_68;
      local_1c = local_64;
      local_18 = local_60;
      local_14 = local_5c;
      local_10 = local_58;
      local_c = local_54;
    }
  }
  else {
    puVar1 = (undefined4 *)FUN_00447f60(local_f4,local_c0);
    local_50 = *puVar1;
    local_4c = puVar1[1];
    local_48 = puVar1[2];
    local_44 = puVar1[3];
    local_40 = puVar1[4];
    local_3c = puVar1[5];
    local_20 = local_50;
    local_1c = local_4c;
    local_18 = local_48;
    local_14 = local_44;
    local_10 = local_40;
    local_c = local_3c;
  }
  FUN_00444f70(local_ac,local_20,local_1c,local_18,local_14,local_10,local_c,&local_d0,&local_8c,
               &local_b0);
  FUN_0082cd58(param_1,(double)local_d0);
  puVar1 = (undefined4 *)FUN_004ff7e0();
  *puVar1 = local_8c;
  puVar1[1] = local_88;
  puVar1[2] = local_84;
  if (local_b0 == (undefined4 *)0x0) {
    local_b4 = 0;
  }
  else {
    local_b4 = *local_b0;
  }
  local_bc = FUN_00479f30();
  if (local_bc == 0) {
    FUN_0082cd45();
  }
  else {
    uVar3 = FUN_00462380();
    FUN_004ff770(param_1,uVar3);
  }
LAB_00506e32:
  FUN_0083e885();
  return;
}

