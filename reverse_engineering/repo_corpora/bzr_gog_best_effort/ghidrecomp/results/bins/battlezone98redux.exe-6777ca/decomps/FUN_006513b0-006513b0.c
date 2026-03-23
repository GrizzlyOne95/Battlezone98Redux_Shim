
void __fastcall FUN_006513b0(int param_1)

{
  undefined4 uVar1;
  int local_54;
  int local_50;
  char local_48 [64];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_005c7e90("target_silo");
  *(undefined4 *)(param_1 + 0x74) = uVar1;
  uVar1 = FUN_005c7e90("nav_1");
  *(undefined4 *)(param_1 + 0x78) = uVar1;
  uVar1 = FUN_005c7e90("cca_factory");
  *(undefined4 *)(param_1 + 0x94) = uVar1;
  uVar1 = FUN_005c7e90("factory");
  *(undefined4 *)(param_1 + 0x98) = uVar1;
  uVar1 = FUN_005c7e90("portal");
  *(undefined4 *)(param_1 + 0x90) = uVar1;
  for (local_54 = 0; local_54 < 0x19; local_54 = local_54 + 1) {
    local_48[0x20] = 0;
    local_48[0x21] = '\0';
    local_48[0x22] = '\0';
    local_48[0x23] = '\0';
    local_48[0x24] = '\0';
    local_48[0x25] = '\0';
    local_48[0x26] = '\0';
    local_48[0x27] = '\0';
    local_48[0x28] = '\0';
    local_48[0x29] = '\0';
    local_48[0x2a] = '\0';
    local_48[0x2b] = '\0';
    local_48[0x2c] = '\0';
    local_48[0x2d] = '\0';
    local_48[0x2e] = '\0';
    local_48[0x2f] = '\0';
    local_48[0x30] = '\0';
    local_48[0x31] = '\0';
    local_48[0x32] = '\0';
    local_48[0x33] = '\0';
    local_48[0x34] = '\0';
    local_48[0x35] = '\0';
    local_48[0x36] = '\0';
    local_48[0x37] = '\0';
    local_48[0x38] = '\0';
    local_48[0x39] = '\0';
    local_48[0x3a] = '\0';
    local_48[0x3b] = '\0';
    local_48[0x3c] = '\0';
    local_48[0x3d] = '\0';
    local_48[0x3e] = '\0';
    local_48[0x3f] = 0;
    sprintf(local_48 + 0x20,"empty_%i",local_54 + 1);
    uVar1 = FUN_005c7e90(local_48 + 0x20);
    *(undefined4 *)(param_1 + 0x15c + local_54 * 4) = uVar1;
  }
  for (local_50 = 0; local_50 < 4; local_50 = local_50 + 1) {
    local_48[0] = '\0';
    local_48[1] = '\0';
    local_48[2] = '\0';
    local_48[3] = '\0';
    local_48[4] = '\0';
    local_48[5] = '\0';
    local_48[6] = '\0';
    local_48[7] = '\0';
    local_48[8] = '\0';
    local_48[9] = '\0';
    local_48[10] = '\0';
    local_48[0xb] = '\0';
    local_48[0xc] = '\0';
    local_48[0xd] = '\0';
    local_48[0xe] = '\0';
    local_48[0xf] = '\0';
    local_48[0x10] = '\0';
    local_48[0x11] = '\0';
    local_48[0x12] = '\0';
    local_48[0x13] = '\0';
    local_48[0x14] = '\0';
    local_48[0x15] = '\0';
    local_48[0x16] = '\0';
    local_48[0x17] = '\0';
    local_48[0x18] = '\0';
    local_48[0x19] = '\0';
    local_48[0x1a] = '\0';
    local_48[0x1b] = '\0';
    local_48[0x1c] = '\0';
    local_48[0x1d] = '\0';
    local_48[0x1e] = '\0';
    local_48[0x1f] = 0;
    sprintf(local_48,"turret_%i",local_50 + 1);
    uVar1 = FUN_005c7e90(local_48);
    *(undefined4 *)(param_1 + 0x1c0 + local_50 * 4) = uVar1;
  }
  *(undefined1 *)(param_1 + 0x56) = 0;
  *(undefined1 *)(param_1 + 0x58) = 1;
  *(undefined4 *)(param_1 + 0x1d4) = 1;
  *(undefined4 *)(param_1 + 0x1dc) = 0;
  *(undefined4 *)(param_1 + 0x1e4) = 0;
  FUN_0083e885();
  return;
}

