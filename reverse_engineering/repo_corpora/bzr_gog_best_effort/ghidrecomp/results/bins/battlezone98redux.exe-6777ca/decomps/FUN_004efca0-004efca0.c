
void FUN_004efca0(void)

{
  undefined4 *puVar1;
  undefined1 local_40 [12];
  undefined1 local_34 [12];
  uint local_28;
  undefined4 *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_004af0a0();
  *local_24 = HoverCraftClass::vftable;
  local_24[5] = 0x484f5652;
  local_24[6] = "hover";
  local_24[0xd3] = 0x3f800000;
  local_24[0xd4] = 0x40800000;
  local_24[0xd5] = 0x3f800000;
  local_24[0xd6] = 0x3c23d70a;
  local_24[0xd8] = 0x40400000;
  local_24[0xd7] = 0x41200000;
  local_24[0xd9] = 0x3e99999a;
  local_24[0xda] = 0x3dcccccd;
  local_24[0xdb] = 0x3dcccccd;
  local_24[0xdc] = 0x3dcccccd;
  local_24[0xca] = 0x41a00000;
  local_24[0xcb] = 0x41200000;
  local_24[0xcc] = 0x41700000;
  local_24[0xcd] = 0x41c80000;
  local_24[0xce] = 0x42960000;
  local_24[0xcf] = 0x40800000;
  local_24[0xd0] = 0x3fc00000;
  local_24[0xd1] = 0x40a00000;
  local_24[0xd2] = 0x3dcccccd;
  local_24[0xdd] = 0x3ecccccd;
  local_24[0xde] = 0x3e4ccccd;
  local_24[0xdf] = 0x3e4ccccd;
  local_24[0xe0] = 0x3dcccccd;
  local_24[0xe1] = 0;
  local_24[0xe2] = 0;
  local_24[0xe3] = 0x3ecccccd;
  local_24[0xe4] = 0x3e4ccccd;
  local_24[0xe5] = 0x3ecccccd;
  local_24[0xe6] = 0x3e4ccccd;
  local_24[0xe7] = 0;
  for (local_28 = 0; local_28 < 0x10; local_28 = local_28 + 1) {
    local_24[local_28 * 2 + 0xe8] = 0;
    local_24[local_28 * 2 + 0xe9] = 0;
    puVar1 = (undefined4 *)FUN_00440000(local_34,0,0,0);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    puVar1 = local_24 + local_28 * 3 + 0x108;
    *puVar1 = local_14;
    puVar1[1] = local_10;
    puVar1[2] = local_c;
    puVar1 = (undefined4 *)FUN_00440000(local_40,0x3fc90fdb,0,0);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    puVar1 = local_24 + local_28 * 3 + 0x138;
    *puVar1 = local_20;
    puVar1[1] = local_1c;
    puVar1[2] = local_18;
  }
  strncpy((char *)(local_24 + 0x168),"engthrst.wav",0x10);
  strncpy((char *)(local_24 + 0x16c),"engrev.wav",0x10);
  strncpy((char *)(local_24 + 0x170),"amb_wind.wav",0x10);
  strncpy((char *)(local_24 + 0x174),"trdeploy.wav",0x10);
  strncpy((char *)(local_24 + 0x178),"trundepl.wav",0x10);
  FUN_0083e885();
  return;
}

