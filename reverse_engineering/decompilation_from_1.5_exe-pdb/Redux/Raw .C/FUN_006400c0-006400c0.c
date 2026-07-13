
void __fastcall FUN_006400c0(int param_1)

{
  undefined4 uVar1;
  int local_c;
  
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x55) = 0;
  for (local_c = 0; local_c < 3; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x59) = 0;
    *(undefined1 *)(param_1 + local_c + 0x56) = 0;
  }
  *(undefined1 *)(param_1 + 0x5c) = 0;
  *(undefined1 *)(param_1 + 0x5d) = 0;
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x5f) = 0;
  }
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 99) = 0;
  }
  uVar1 = FUN_005c7e90("destroy_1");
  *(undefined4 *)(param_1 + 0x84) = uVar1;
  uVar1 = FUN_005c7e90("destroy_2");
  *(undefined4 *)(param_1 + 0x88) = uVar1;
  uVar1 = FUN_005c7e90("destroy_3");
  *(undefined4 *)(param_1 + 0x8c) = uVar1;
  uVar1 = FUN_005c7e90("destroy_4");
  *(undefined4 *)(param_1 + 0x90) = uVar1;
  uVar1 = FUN_005c7e90("destroy_5");
  *(undefined4 *)(param_1 + 0x94) = uVar1;
  uVar1 = FUN_005c7e90("destroy_6");
  *(undefined4 *)(param_1 + 0x98) = uVar1;
  *(undefined4 *)(param_1 + 0xa8) = 0;
  *(undefined4 *)(param_1 + 0xac) = 0;
  *(undefined4 *)(param_1 + 0xb0) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x78) = 0x497423fe;
  return;
}

