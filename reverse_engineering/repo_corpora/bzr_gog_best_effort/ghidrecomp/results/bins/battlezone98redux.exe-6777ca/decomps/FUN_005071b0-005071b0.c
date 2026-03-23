
void FUN_005071b0(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined1 local_48 [12];
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = FUN_004ff820(param_1,1);
  if (local_1c == 0) {
    local_20 = FUN_004ff7a0(param_1,1);
    if (local_20 == 0) {
      iVar2 = FUN_0082c9f5(param_1,1);
      if (iVar2 == 0) {
        local_30 = FUN_004ff750(param_1,1);
        local_28 = FUN_0082d338(param_1,2);
        local_18 = FUN_005cd980(local_30,local_28);
      }
      else {
        local_34 = FUN_0082d377(param_1,1,0);
        local_3c = FUN_0082c1fd(param_1,2,0);
        local_24 = FUN_0082d338(param_1,3);
        local_18 = FUN_005cd9d0(local_34,local_3c,local_24);
      }
    }
    else {
      local_38 = FUN_0082d338(param_1,2);
      local_18 = FUN_005cd820(local_20,0,local_38);
    }
  }
  else {
    local_2c = FUN_0082d338(param_1,2);
    puVar1 = (undefined4 *)FUN_00439de0(local_48,local_1c);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    local_18 = FUN_005cd820(&local_14,0,local_2c);
  }
  FUN_004ff770(param_1,local_18);
  FUN_0083e885();
  return;
}

