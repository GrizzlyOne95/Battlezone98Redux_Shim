
void FUN_005c8dd0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 local_24 [12];
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = FUN_00462630(param_2);
  if (local_18 == 0) {
    puVar1 = (undefined4 *)FUN_00440000(local_24,0,0,0);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    *param_1 = local_14;
    param_1[1] = local_10;
    param_1[2] = local_c;
  }
  else {
    puVar1 = (undefined4 *)FUN_004624b0();
    *param_1 = *puVar1;
    param_1[1] = puVar1[1];
    param_1[2] = puVar1[2];
  }
  FUN_0083e885();
  return;
}

