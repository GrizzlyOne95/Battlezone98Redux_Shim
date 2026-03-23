
void __fastcall FUN_00641360(int param_1)

{
  undefined4 uVar1;
  int local_c;
  
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x55) = 0;
  *(undefined1 *)(param_1 + 0x56) = 0;
  *(undefined1 *)(param_1 + 0x57) = 0;
  *(undefined1 *)(param_1 + 0x5c) = 0;
  *(undefined1 *)(param_1 + 0x5d) = 0;
  *(undefined1 *)(param_1 + 0x5f) = 0;
  *(undefined1 *)(param_1 + 0x60) = 0;
  *(undefined1 *)(param_1 + 0x61) = 0;
  *(undefined1 *)(param_1 + 0x65) = 0;
  *(undefined1 *)(param_1 + 0x5e) = 0;
  *(undefined1 *)(param_1 + 0x66) = 0;
  for (local_c = 0; local_c < 2; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x5a) = 0;
    *(undefined1 *)(param_1 + local_c + 0x58) = 0;
  }
  *(undefined1 *)(param_1 + 0x62) = 0;
  *(undefined1 *)(param_1 + 99) = 0;
  *(undefined1 *)(param_1 + 100) = 0;
  uVar1 = FUN_005c7e90("recycler");
  *(undefined4 *)(param_1 + 0xcc) = uVar1;
  uVar1 = FUN_005c7e90("portal");
  *(undefined4 *)(param_1 + 0x224) = uVar1;
  uVar1 = FUN_005c7e90(&DAT_00875928);
  *(undefined4 *)(param_1 + 0xd0) = uVar1;
  for (local_c = 0; local_c < 0x47; local_c = local_c + 1) {
    *(undefined4 *)(param_1 + 0xd8 + local_c * 4) = 0;
  }
  uVar1 = FUN_005c7e90("enemy_1");
  *(undefined4 *)(param_1 + 0xd8) = uVar1;
  uVar1 = FUN_005c7e90("enemy_2");
  *(undefined4 *)(param_1 + 0xdc) = uVar1;
  uVar1 = FUN_005c7e90("enemy_3");
  *(undefined4 *)(param_1 + 0xe0) = uVar1;
  uVar1 = FUN_005c7e90("enemy_4");
  *(undefined4 *)(param_1 + 0xe4) = uVar1;
  uVar1 = FUN_005c7e90("enemy_5");
  *(undefined4 *)(param_1 + 0xe8) = uVar1;
  uVar1 = FUN_005c7e90("enemy_6");
  *(undefined4 *)(param_1 + 0xec) = uVar1;
  *(undefined4 *)(param_1 + 0xd4) = 0;
  *(undefined4 *)(param_1 + 0x22c) = 0;
  *(undefined4 *)(param_1 + 0x228) = 0;
  for (local_c = 0; local_c < 0xc; local_c = local_c + 1) {
    *(undefined4 *)(param_1 + 500 + local_c * 4) = 0;
  }
  *(undefined4 *)(param_1 + 0x238) = 0;
  *(undefined4 *)(param_1 + 0x23c) = 0;
  *(undefined4 *)(param_1 + 0x240) = 0;
  *(undefined4 *)(param_1 + 0x244) = 0;
  *(undefined4 *)(param_1 + 0x248) = 0;
  *(undefined4 *)(param_1 + 0x24c) = 0;
  *(undefined4 *)(param_1 + 0x250) = 0;
  *(undefined4 *)(param_1 + 0x254) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
  for (local_c = 0; local_c < 6; local_c = local_c + 1) {
    *(undefined4 *)(param_1 + 0x74 + local_c * 4) = 0x497423fe;
  }
  *(undefined4 *)(param_1 + 0x8c) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x90) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x94) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x98) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x9c) = 0x497423fe;
  *(undefined4 *)(param_1 + 0xa0) = 0x497423fe;
  *(undefined4 *)(param_1 + 0xa4) = 0x497423fe;
  *(undefined4 *)(param_1 + 0xa8) = 0x497423fe;
  *(undefined4 *)(param_1 + 0xb4) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x234) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
  *(undefined4 *)(param_1 + 0xac) = 0x497423fe;
  *(undefined4 *)(param_1 + 0xb0) = 0x497423fe;
  *(undefined4 *)(param_1 + 0xb8) = 0x497423fe;
  *(undefined4 *)(param_1 + 0xbc) = 0x497423fe;
  *(undefined4 *)(param_1 + 0xc0) = 0x497423fe;
  return;
}

