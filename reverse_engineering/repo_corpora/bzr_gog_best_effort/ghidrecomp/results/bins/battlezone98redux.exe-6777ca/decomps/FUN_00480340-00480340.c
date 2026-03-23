
void FUN_00480340(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 local_40 [12];
  undefined1 local_34 [12];
  float local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00584fe0(param_1,param_2);
  puVar1 = (undefined4 *)FUN_004560b0(local_34,*(int *)(local_24 + 0x14) + 0x20);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  puVar1 = (undefined4 *)
           FUN_004462d0(local_40,*(undefined4 *)(*(int *)(local_24 + 0xc) + 0x54),local_20,local_1c,
                        local_18);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  *(undefined4 *)(local_24 + 0x30) = local_14;
  *(undefined4 *)(local_24 + 0x34) = local_10;
  *(undefined4 *)(local_24 + 0x38) = local_c;
  *(undefined4 *)(local_24 + 0x20) = *(undefined4 *)(*(int *)(local_24 + 0xc) + 0x54);
  if (*(float *)(local_24 + 0x20) <= 0.0) {
    local_28 = 1e+30;
  }
  else {
    local_28 = 1.0 / *(float *)(local_24 + 0x20);
  }
  *(float *)(local_24 + 0x24) = local_28;
  *(undefined1 *)(local_24 + 0xe0) = 1;
  FUN_0083e885();
  return;
}

