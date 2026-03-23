
void FUN_005b53e0(void)

{
  undefined4 *puVar1;
  undefined1 local_6c [12];
  undefined1 local_60 [12];
  undefined1 local_54 [12];
  undefined1 local_48 [12];
  undefined4 *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
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
  FUN_00461ba0();
  *local_3c = RecycleTask::vftable;
  local_3c[0xb] = 0;
  local_3c[0x12] = 0;
  local_3c[0x13] = 1;
  local_3c[0xc] = 0;
  puVar1 = (undefined4 *)FUN_00440000(local_60,0,0xbf800000,0);
  local_2c = *puVar1;
  local_28 = puVar1[1];
  local_24 = puVar1[2];
  local_3c[0xd] = local_2c;
  local_3c[0xe] = local_28;
  local_3c[0xf] = local_24;
  local_3c[0x10] = 0;
  local_3c[0x11] = 0;
  local_3c[6] = 0;
  puVar1 = (undefined4 *)FUN_00440000(local_48,0,0,0);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  local_3c[7] = local_20;
  local_3c[8] = local_1c;
  local_3c[9] = local_18;
  local_3c[10] = 0;
  puVar1 = (undefined4 *)FUN_00440000(local_54,0,0,0);
  local_38 = *puVar1;
  local_34 = puVar1[1];
  local_30 = puVar1[2];
  local_3c[0x14] = local_38;
  local_3c[0x15] = local_34;
  local_3c[0x16] = local_30;
  local_3c[0x17] = 0;
  puVar1 = (undefined4 *)FUN_00440000(local_6c,0,0,0);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  local_3c[0x18] = local_14;
  local_3c[0x19] = local_10;
  local_3c[0x1a] = local_c;
  local_3c[2] = 0;
  local_3c[3] = 0;
  local_3c[4] = 0;
  local_3c[5] = 0;
  FUN_0083e885();
  return;
}

