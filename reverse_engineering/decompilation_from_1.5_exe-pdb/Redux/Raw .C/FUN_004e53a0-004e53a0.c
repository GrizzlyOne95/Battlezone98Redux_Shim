
void FUN_004e53a0(void)

{
  undefined4 *puVar1;
  undefined1 local_24 [12];
  undefined4 *local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_005fe010();
  *local_18 = GotoTask::vftable;
  local_18[2] = 1;
  local_18[3] = 1;
  local_18[0x4d] = 0;
  *(undefined1 *)(local_18 + 0x4f) = 0;
  local_18[0x4e] = 0;
  puVar1 = (undefined4 *)FUN_00440000(local_24,0,0,0);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  local_18[0x50] = local_14;
  local_18[0x51] = local_10;
  local_18[0x52] = local_c;
  *(undefined1 *)((int)local_18 + 0x13d) = 0;
  *(undefined1 *)((int)local_18 + 0x13e) = 0;
  FUN_0083e885();
  return;
}

