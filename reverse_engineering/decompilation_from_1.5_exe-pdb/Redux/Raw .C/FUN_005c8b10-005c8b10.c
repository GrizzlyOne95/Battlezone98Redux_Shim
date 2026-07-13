
void FUN_005c8b10(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 local_30 [12];
  int local_24;
  undefined1 local_20 [12];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = FUN_00462630(param_2);
  if (local_24 == 0) {
    puVar1 = (undefined4 *)FUN_00440000(local_30,0,0,0);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    *param_1 = local_14;
    param_1[1] = local_10;
    param_1[2] = local_c;
  }
  else {
    puVar1 = (undefined4 *)FUN_004c0af0(local_20);
    *param_1 = *puVar1;
    param_1[1] = puVar1[1];
    param_1[2] = puVar1[2];
  }
  FUN_0083e885();
  return;
}

