
void FUN_00501710(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined1 local_34 [12];
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
  local_18 = FUN_004ff750(param_1,1);
  local_1c = FUN_004ff820(param_1,2);
  if (local_1c == 0) {
    local_20 = FUN_004ff7a0(param_1,2);
    if (local_20 == 0) {
      iVar2 = FUN_0082c9f5(param_1,2);
      if (iVar2 != 0) {
        local_28 = FUN_0082ba59(param_1,2,0);
        local_24 = FUN_0082c1fd(param_1,3,0);
        FUN_005c8cb0(local_18,local_28,local_24);
      }
    }
    else {
      FUN_005c8c80(local_18,local_20);
    }
  }
  else {
    puVar1 = (undefined4 *)FUN_00439de0(local_34,local_1c);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    FUN_005c8c80(local_18,&local_14);
  }
  FUN_0083e885();
  return;
}

