
void FUN_00501620(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 local_44 [12];
  undefined1 local_38 [12];
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
  iVar1 = FUN_0082c9f5(param_1,1);
  if (iVar1 == 0) {
    local_28 = FUN_004ff750(param_1,1);
    puVar2 = (undefined4 *)FUN_005c8b10(local_44,local_28);
    local_20 = *puVar2;
    local_1c = puVar2[1];
    local_18 = puVar2[2];
    puVar2 = (undefined4 *)FUN_004ff7e0(param_1);
    *puVar2 = local_20;
    puVar2[1] = local_1c;
    puVar2[2] = local_18;
  }
  else {
    local_2c = FUN_0082ba59(param_1,1,0);
    local_24 = FUN_0082c1fd(param_1,2,0);
    puVar2 = (undefined4 *)FUN_005c8bd0(local_38,local_2c,local_24);
    local_14 = *puVar2;
    local_10 = puVar2[1];
    local_c = puVar2[2];
    puVar2 = (undefined4 *)FUN_004ff7e0(param_1);
    *puVar2 = local_14;
    puVar2[1] = local_10;
    puVar2[2] = local_c;
  }
  FUN_0083e885();
  return;
}

