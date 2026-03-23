
void FUN_00502490(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  float10 fVar3;
  undefined1 local_74 [12];
  undefined1 local_68 [12];
  undefined1 local_5c [12];
  undefined4 local_50;
  float local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 *local_40;
  int local_3c;
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
  fVar3 = (float10)FUN_0082c276(param_1,1,0x407c200000000000);
  local_4c = (float)fVar3;
  local_3c = FUN_004ff820(param_1,2);
  if (local_3c == 0) {
    local_40 = (undefined4 *)FUN_004ff7a0(param_1,2);
    if (local_40 == (undefined4 *)0x0) {
      iVar2 = FUN_0082c9f5(param_1,2);
      if (iVar2 == 0) {
        local_48 = FUN_004ff750(param_1,2);
        puVar1 = (undefined4 *)FUN_005c8b10(local_74,local_48);
        local_2c = *puVar1;
        local_28 = puVar1[1];
        local_24 = puVar1[2];
        local_14 = local_2c;
        local_10 = local_28;
        local_c = local_24;
      }
      else {
        local_44 = FUN_0082d377(param_1,2,0);
        local_50 = FUN_0082c1fd(param_1,3,0);
        puVar1 = (undefined4 *)FUN_005c8bd0(local_68,local_44,local_50);
        local_38 = *puVar1;
        local_34 = puVar1[1];
        local_30 = puVar1[2];
        local_14 = local_38;
        local_10 = local_34;
        local_c = local_30;
      }
    }
    else {
      local_14 = *local_40;
      local_10 = local_40[1];
      local_c = local_40[2];
    }
  }
  else {
    puVar1 = (undefined4 *)FUN_00439de0(local_5c,local_3c);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
  }
  FUN_0082cd58(param_1,(double)local_4c);
  puVar1 = (undefined4 *)FUN_004ff7e0();
  *puVar1 = local_14;
  puVar1[1] = local_10;
  puVar1[2] = local_c;
  FUN_0082ccca(param_1,0);
  FUN_0082cc15(param_1,FUN_00502360,3);
  FUN_0083e885();
  return;
}

