
void FUN_00502960(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined1 local_38 [12];
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
        local_2c = FUN_004ff750(param_1,1);
        local_18 = FUN_005c9cc0(local_2c);
      }
      else {
        local_28 = FUN_0082d377(param_1,1,0);
        local_24 = FUN_0082c1fd(param_1,2,0);
        local_18 = FUN_005c9d10(local_28,local_24);
      }
    }
    else {
      local_18 = FUN_005c9bc0(local_20,0);
    }
  }
  else {
    puVar1 = (undefined4 *)FUN_00439de0(local_38,local_1c);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    local_18 = FUN_005c9bc0(&local_14,0);
  }
  FUN_004ff770(param_1,local_18);
  FUN_0083e885();
  return;
}

