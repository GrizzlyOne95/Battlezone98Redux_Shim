
void __fastcall FUN_00647420(int param_1)

{
  undefined4 uVar1;
  int local_c;
  
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x5e) = 0;
  *(undefined1 *)(param_1 + 0x55) = 0;
  *(undefined1 *)(param_1 + 0x56) = 0;
  *(undefined1 *)(param_1 + 0x57) = 0;
  for (local_c = 0; local_c < 2; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x5a) = 0;
    *(undefined1 *)(param_1 + local_c + 0x58) = 0;
  }
  *(undefined1 *)(param_1 + 0x5c) = 0;
  *(undefined1 *)(param_1 + 0x5d) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  uVar1 = FUN_005c7e90("recycler");
  *(undefined4 *)(param_1 + 0x84) = uVar1;
  uVar1 = FUN_005c7e90("chin_recycler");
  *(undefined4 *)(param_1 + 0x88) = uVar1;
  *(undefined4 *)(param_1 + 0x94) = 0;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0x497423fe;
  *(undefined4 *)(param_1 + 100) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x68) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x6c) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
  return;
}

