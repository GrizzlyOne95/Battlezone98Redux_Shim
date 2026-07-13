
void FUN_00607320(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined1 local_34 [12];
  undefined4 local_28;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_28 = FUN_0045c4d0();
  puVar1 = (undefined4 *)FUN_00440300(local_34,param_1,local_28);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_18;
  FUN_006073a0(&local_20);
  FUN_0083e885();
  return;
}

