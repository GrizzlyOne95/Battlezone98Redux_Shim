
void __fastcall FUN_00656ff0(int param_1)

{
  undefined4 uVar1;
  int local_c;
  
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x55) = 0;
  *(undefined1 *)(param_1 + 0x56) = 0;
  *(undefined1 *)(param_1 + 0x57) = 0;
  *(undefined1 *)(param_1 + 0x5c) = 0;
  *(undefined1 *)(param_1 + 0x5d) = 0;
  *(undefined1 *)(param_1 + 0x5e) = 0;
  *(undefined1 *)(param_1 + 0x5f) = 0;
  for (local_c = 0; local_c < 2; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x58) = 0;
    *(undefined1 *)(param_1 + local_c + 0x5a) = 0;
  }
  *(undefined4 *)(param_1 + 0x8c) = 0;
  uVar1 = FUN_005c7e90("avrecy2_recycler");
  *(undefined4 *)(param_1 + 0x90) = uVar1;
  uVar1 = FUN_005c7e90("avmuf2_factory");
  *(undefined4 *)(param_1 + 0x94) = uVar1;
  uVar1 = FUN_005c7e90("avslf2_armory");
  *(undefined4 *)(param_1 + 0x98) = uVar1;
  uVar1 = FUN_005c7e90("absilo2_scrapsilo");
  *(undefined4 *)(param_1 + 0x9c) = uVar1;
  uVar1 = FUN_005c7e90("absilo3_scrapsilo");
  *(undefined4 *)(param_1 + 0xa0) = uVar1;
  for (local_c = 0; local_c < 0xc; local_c = local_c + 1) {
    *(undefined4 *)(param_1 + 0xa4 + local_c * 4) = 0;
  }
  uVar1 = FUN_005c7e90("psu_1");
  *(undefined4 *)(param_1 + 0xd4) = uVar1;
  uVar1 = FUN_005c7e90("psu_2");
  *(undefined4 *)(param_1 + 0xd8) = uVar1;
  uVar1 = FUN_005c7e90("psu_3");
  *(undefined4 *)(param_1 + 0xdc) = uVar1;
  uVar1 = FUN_005c7e90("psu_4");
  *(undefined4 *)(param_1 + 0xe0) = uVar1;
  for (local_c = 0; local_c < 10; local_c = local_c + 1) {
    *(undefined4 *)(param_1 + 0xe4 + local_c * 4) = 0;
  }
  *(undefined4 *)(param_1 + 0x114) = 0;
  *(undefined4 *)(param_1 + 0x118) = 0;
  *(undefined4 *)(param_1 + 0x11c) = 0;
  *(undefined4 *)(param_1 + 0x120) = 0;
  *(undefined4 *)(param_1 + 100) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x68) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x78) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x80) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x84) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x124) = 10;
  *(undefined4 *)(param_1 + 0x128) = 0;
  *(undefined4 *)(param_1 + 0x110) = 0;
  return;
}

