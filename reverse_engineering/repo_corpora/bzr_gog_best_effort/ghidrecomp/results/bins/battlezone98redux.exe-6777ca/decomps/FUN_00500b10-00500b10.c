
void FUN_00500b10(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined1 local_24 [12];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = FUN_004ff7c0(param_1,1);
  puVar1 = (undefined4 *)FUN_004621a0(local_24,local_18);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  puVar1 = (undefined4 *)FUN_004ff7e0(param_1);
  *puVar1 = local_14;
  puVar1[1] = local_10;
  puVar1[2] = local_c;
  FUN_0083e885();
  return;
}

