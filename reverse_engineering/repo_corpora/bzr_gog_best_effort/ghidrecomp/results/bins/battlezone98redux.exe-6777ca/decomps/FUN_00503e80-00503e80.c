
void FUN_00503e80(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined1 local_34 [12];
  undefined4 local_28;
  int local_24;
  int local_20;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = FUN_0082d377(param_1,1,0);
  local_18 = 0;
  local_24 = FUN_004ff820(param_1,2);
  if (local_24 == 0) {
    local_20 = FUN_004ff7a0(param_1,2);
    if (local_20 == 0) {
      local_28 = FUN_004ff750(param_1,2);
      local_18 = FUN_005cc080(local_1c,local_28);
    }
    else {
      local_18 = FUN_005cc020(local_1c,local_20);
    }
  }
  else {
    puVar1 = (undefined4 *)FUN_00439de0(local_34,local_24);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    local_18 = FUN_005cc020(local_1c,&local_14);
  }
  FUN_0082cd58(param_1,(double)local_18);
  FUN_0083e885();
  return;
}

