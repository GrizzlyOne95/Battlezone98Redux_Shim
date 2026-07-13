
void __fastcall FUN_00645710(int param_1)

{
  undefined4 uVar1;
  int local_c;
  
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x55) = 0;
  *(undefined1 *)(param_1 + 0x56) = 0;
  *(undefined1 *)(param_1 + 0x57) = 0;
  for (local_c = 0; local_c < 2; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x5a) = 0;
    *(undefined1 *)(param_1 + local_c + 0x58) = 0;
  }
  for (local_c = 0; local_c < 6; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x62) = 0;
    *(undefined1 *)(param_1 + local_c + 0x5c) = 0;
  }
  *(undefined1 *)(param_1 + 0x68) = 0;
  *(undefined1 *)(param_1 + 0x6a) = 0;
  *(undefined1 *)(param_1 + 0x6b) = 0;
  *(undefined1 *)(param_1 + 0x69) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0;
  uVar1 = FUN_005c7e90("recycler");
  *(undefined4 *)(param_1 + 0x8c) = uVar1;
  uVar1 = FUN_005c7e90("chin_recycler");
  *(undefined4 *)(param_1 + 0x90) = uVar1;
  uVar1 = FUN_005c7e90("chin_silo1");
  *(undefined4 *)(param_1 + 0x94) = uVar1;
  uVar1 = FUN_005c7e90("chin_silo2");
  *(undefined4 *)(param_1 + 0x98) = uVar1;
  uVar1 = FUN_005c7e90("chin_silo3");
  *(undefined4 *)(param_1 + 0x9c) = uVar1;
  uVar1 = FUN_005c7e90("chin_silo4");
  *(undefined4 *)(param_1 + 0xa0) = uVar1;
  uVar1 = FUN_005c7e90("chin_silo5");
  *(undefined4 *)(param_1 + 0xa4) = uVar1;
  uVar1 = FUN_005c7e90("chin_silo6");
  *(undefined4 *)(param_1 + 0xa8) = uVar1;
  *(undefined4 *)(param_1 + 0xb8) = 0;
  *(undefined4 *)(param_1 + 0xbc) = 0;
  *(undefined4 *)(param_1 + 0xc0) = 0;
  *(undefined4 *)(param_1 + 0xc4) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x74) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x78) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
  *(undefined4 *)(param_1 + 0xb4) = 0;
  *(undefined4 *)(param_1 + 0xb0) = 0;
  return;
}

