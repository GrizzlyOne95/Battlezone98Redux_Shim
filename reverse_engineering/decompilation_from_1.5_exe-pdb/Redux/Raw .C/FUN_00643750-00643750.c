
void __fastcall FUN_00643750(int param_1)

{
  undefined4 uVar1;
  int local_c;
  
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x55) = 0;
  *(undefined1 *)(param_1 + 0x56) = 0;
  *(undefined1 *)(param_1 + 0x57) = 0;
  *(undefined1 *)(param_1 + 0x5c) = 0;
  *(undefined1 *)(param_1 + 0x5d) = 0;
  for (local_c = 0; local_c < 8; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x5f) = 0;
  }
  for (local_c = 0; local_c < 2; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x58) = 0;
    *(undefined1 *)(param_1 + local_c + 0x5a) = 0;
  }
  *(undefined4 *)(param_1 + 0xec) = 0;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  uVar1 = FUN_005c7e90("portal");
  *(undefined4 *)(param_1 + 0xb4) = uVar1;
  uVar1 = FUN_005c7e90("shield_1");
  *(undefined4 *)(param_1 + 0xb8) = uVar1;
  uVar1 = FUN_005c7e90("shield_2");
  *(undefined4 *)(param_1 + 0xbc) = uVar1;
  uVar1 = FUN_005c7e90("shield_3");
  *(undefined4 *)(param_1 + 0xc0) = uVar1;
  uVar1 = FUN_005c7e90("shield_4");
  *(undefined4 *)(param_1 + 0xc4) = uVar1;
  uVar1 = FUN_005c7e90("power_1");
  *(undefined4 *)(param_1 + 200) = uVar1;
  uVar1 = FUN_005c7e90("power_2");
  *(undefined4 *)(param_1 + 0xcc) = uVar1;
  uVar1 = FUN_005c7e90("power_3");
  *(undefined4 *)(param_1 + 0xd0) = uVar1;
  uVar1 = FUN_005c7e90("power_4");
  *(undefined4 *)(param_1 + 0xd4) = uVar1;
  uVar1 = FUN_005c7e90("goal_1");
  *(undefined4 *)(param_1 + 0xd8) = uVar1;
  uVar1 = FUN_005c7e90("goal_2");
  *(undefined4 *)(param_1 + 0xdc) = uVar1;
  uVar1 = FUN_005c7e90("goal_3");
  *(undefined4 *)(param_1 + 0xe0) = uVar1;
  uVar1 = FUN_005c7e90("goal_4");
  *(undefined4 *)(param_1 + 0xe4) = uVar1;
  *(undefined4 *)(param_1 + 0x98) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x9c) = 0x497423fe;
  for (local_c = 0; local_c < 10; local_c = local_c + 1) {
    *(undefined4 *)(param_1 + 0x70 + local_c * 4) = 0x497423fe;
  }
  *(undefined4 *)(param_1 + 0xa0) = 0x497423fe;
  *(undefined4 *)(param_1 + 0xa4) = 0x497423fe;
  return;
}

