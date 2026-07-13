
void FUN_00501fc0(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  float10 fVar3;
  undefined1 local_3c [12];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  undefined4 local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = FUN_004ff750(param_1,1);
  local_20 = FUN_004ff820(param_1,2);
  if (local_20 == 0) {
    local_24 = FUN_004ff7a0(param_1,2);
    if (local_24 == 0) {
      iVar2 = FUN_0082c9f5(param_1,2);
      if (iVar2 == 0) {
        local_30 = FUN_004ff750(param_1,2);
        fVar3 = (float10)FUN_005c9780(local_1c,local_30);
        local_18 = (float)fVar3;
      }
      else {
        local_2c = FUN_0082d377(param_1,2,0);
        local_28 = FUN_0082c1fd(param_1,3,0);
        fVar3 = (float10)FUN_005c9800(local_1c,local_2c,local_28);
        local_18 = (float)fVar3;
      }
    }
    else {
      fVar3 = (float10)FUN_005c9730(local_1c,local_24);
      local_18 = (float)fVar3;
    }
  }
  else {
    puVar1 = (undefined4 *)FUN_00439de0(local_3c,local_20);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    fVar3 = (float10)FUN_005c9730(local_1c,&local_14);
    local_18 = (float)fVar3;
  }
  FUN_0082cd58(param_1,(double)local_18);
  FUN_0083e885();
  return;
}

