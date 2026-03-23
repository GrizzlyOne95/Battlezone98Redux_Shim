
void FUN_005e6010(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 local_3c [24];
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00480340(param_1,param_2);
  puVar1 = (undefined4 *)FUN_00447f60(local_3c,*(int *)(local_24 + 0x14) + 0x20);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  local_14 = puVar1[3];
  local_10 = puVar1[4];
  local_c = puVar1[5];
  *(undefined4 *)(local_24 + 0xe8) = local_20;
  *(undefined4 *)(local_24 + 0xec) = local_1c;
  *(undefined4 *)(local_24 + 0xf0) = local_18;
  *(undefined4 *)(local_24 + 0xf4) = local_14;
  *(undefined4 *)(local_24 + 0xf8) = local_10;
  *(undefined4 *)(local_24 + 0xfc) = local_c;
  FUN_0083e885();
  return;
}

