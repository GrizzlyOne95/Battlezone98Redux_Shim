
void __fastcall FUN_0064f690(int param_1)

{
  undefined4 uVar1;
  int local_c;
  
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x55) = 0;
  *(undefined1 *)(param_1 + 0x56) = 0;
  *(undefined1 *)(param_1 + 0x57) = 0;
  for (local_c = 0; local_c < 6; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x5c) = 0;
    *(undefined1 *)(param_1 + local_c + 0x62) = 0;
  }
  for (local_c = 0; local_c < 6; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x68) = 0;
  }
  *(undefined1 *)(param_1 + 0x6b) = 0;
  for (local_c = 0; local_c < 2; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x58) = 0;
    *(undefined1 *)(param_1 + local_c + 0x5a) = 0;
  }
  *(undefined4 *)(param_1 + 0xc4) = 0;
  *(undefined4 *)(param_1 + 200) = 0;
  uVar1 = FUN_005c7e90("howitzer_1");
  *(undefined4 *)(param_1 + 0xcc) = uVar1;
  uVar1 = FUN_005c7e90("howitzer_2");
  *(undefined4 *)(param_1 + 0xd0) = uVar1;
  uVar1 = FUN_005c7e90("howitzer_3");
  *(undefined4 *)(param_1 + 0xd4) = uVar1;
  uVar1 = FUN_005c7e90("howitzer_4");
  *(undefined4 *)(param_1 + 0xd8) = uVar1;
  uVar1 = FUN_005c7e90("howitzer_5");
  *(undefined4 *)(param_1 + 0xdc) = uVar1;
  uVar1 = FUN_005c7e90("howitzer_6");
  *(undefined4 *)(param_1 + 0xe0) = uVar1;
  for (local_c = 0; local_c < 6; local_c = local_c + 1) {
    *(undefined4 *)(param_1 + 0xe4 + local_c * 4) = 0;
  }
  *(undefined4 *)(param_1 + 0xfc) = 0;
  *(undefined4 *)(param_1 + 0x100) = 0;
  *(undefined4 *)(param_1 + 0x104) = 0;
  *(undefined4 *)(param_1 + 0x110) = 0;
  *(undefined4 *)(param_1 + 0x114) = 0;
  *(undefined4 *)(param_1 + 0x118) = 0;
  *(undefined4 *)(param_1 + 0x11c) = 0;
  *(undefined4 *)(param_1 + 0x120) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x78) = 0x497423fe;
  for (local_c = 0; local_c < 0xf; local_c = local_c + 1) {
    *(undefined4 *)(param_1 + 0x80 + local_c * 4) = 0x497423fe;
  }
  *(undefined4 *)(param_1 + 0xbc) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x10c) = 0xffffffff;
  return;
}

