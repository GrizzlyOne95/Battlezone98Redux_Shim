
void __fastcall FUN_00633590(int param_1)

{
  undefined4 uVar1;
  int local_c;
  
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x55) = 0;
  *(undefined1 *)(param_1 + 0x56) = 0;
  *(undefined1 *)(param_1 + 0x57) = 0;
  *(undefined1 *)(param_1 + 0x62) = 0;
  *(undefined1 *)(param_1 + 99) = 0;
  *(undefined1 *)(param_1 + 0x67) = 0;
  *(undefined1 *)(param_1 + 0x65) = 0;
  *(undefined1 *)(param_1 + 0x66) = 0;
  *(undefined1 *)(param_1 + 0x68) = 0;
  *(undefined1 *)(param_1 + 100) = 0;
  for (local_c = 0; local_c < 10; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x58) = 0;
    *(undefined4 *)(param_1 + 0xc4 + local_c * 4) = 0;
  }
  uVar1 = FUN_005c7e90("recycler");
  *(undefined4 *)(param_1 + 0x98) = uVar1;
  uVar1 = FUN_005c7e90("nav_delta");
  *(undefined4 *)(param_1 + 0x9c) = uVar1;
  FUN_005cd7f0(*(undefined4 *)(param_1 + 0x9c),"Nav Delta");
  *(undefined4 *)(param_1 + 0xa0) = 0;
  uVar1 = FUN_005c7e90("bobcat_kill_me_now");
  *(undefined4 *)(param_1 + 0xa4) = uVar1;
  uVar1 = FUN_005c7e90("scout_kill_me_now");
  *(undefined4 *)(param_1 + 0xa8) = uVar1;
  uVar1 = FUN_005c7e90("geyser1");
  *(undefined4 *)(param_1 + 0xac) = uVar1;
  uVar1 = FUN_005c7e90("evil_scout1");
  *(undefined4 *)(param_1 + 0xb0) = uVar1;
  uVar1 = FUN_005c7e90("evil_scout2");
  *(undefined4 *)(param_1 + 0xb4) = uVar1;
  uVar1 = FUN_005c7e90("evil_scout3");
  *(undefined4 *)(param_1 + 0xb8) = uVar1;
  uVar1 = FUN_005c7e90("evil_tank1");
  *(undefined4 *)(param_1 + 0xbc) = uVar1;
  *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x78) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x80) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x84) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x88) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x8c) = 0x497423fe;
  return;
}

