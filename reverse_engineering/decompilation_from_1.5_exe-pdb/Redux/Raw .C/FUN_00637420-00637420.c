
void __fastcall FUN_00637420(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x55) = 0;
  *(undefined1 *)(param_1 + 0x56) = 0;
  *(undefined1 *)(param_1 + 0x57) = 0;
  *(undefined1 *)(param_1 + 0x58) = 0;
  *(undefined1 *)(param_1 + 99) = 0;
  uVar1 = FUN_005c7e90("recycler",0);
  *(undefined4 *)(param_1 + 0xa0) = uVar1;
  uVar1 = FUN_005c7e90("portal");
  *(undefined4 *)(param_1 + 0xa4) = uVar1;
  uVar1 = FUN_005c7e90("unit_1");
  *(undefined4 *)(param_1 + 0xa8) = uVar1;
  uVar1 = FUN_005c7e90("unit_2");
  *(undefined4 *)(param_1 + 0xac) = uVar1;
  uVar1 = FUN_005c7e90("unit_3");
  *(undefined4 *)(param_1 + 0xb0) = uVar1;
  uVar1 = FUN_005c7e90("unit_4");
  *(undefined4 *)(param_1 + 0xb4) = uVar1;
  uVar1 = FUN_005c7e90("unit_5");
  *(undefined4 *)(param_1 + 0xb8) = uVar1;
  uVar1 = FUN_005c7e90("unit_6");
  *(undefined4 *)(param_1 + 0xbc) = uVar1;
  uVar1 = FUN_005c7e90("unit_7");
  *(undefined4 *)(param_1 + 0xc0) = uVar1;
  uVar1 = FUN_005c7e90("unit_8");
  *(undefined4 *)(param_1 + 0xc4) = uVar1;
  uVar1 = FUN_005c7e90("unit_9");
  *(undefined4 *)(param_1 + 200) = uVar1;
  uVar1 = FUN_005c7e90("unit_10");
  *(undefined4 *)(param_1 + 0xcc) = uVar1;
  uVar1 = FUN_005c7e90("unit_11");
  *(undefined4 *)(param_1 + 0xd0) = uVar1;
  uVar1 = FUN_005c7e90("unit_12");
  *(undefined4 *)(param_1 + 0xd4) = uVar1;
  uVar1 = FUN_005c7e90("unit_13");
  *(undefined4 *)(param_1 + 0xd8) = uVar1;
  uVar1 = FUN_005c7e90("unit_14");
  *(undefined4 *)(param_1 + 0xdc) = uVar1;
  uVar1 = FUN_005c7e90("unit_15");
  *(undefined4 *)(param_1 + 0xe0) = uVar1;
  for (iVar2 = 0xf; iVar2 < 0x2e; iVar2 = iVar2 + 1) {
    *(undefined4 *)(param_1 + 0xa8 + iVar2 * 4) = 0;
  }
  *(undefined4 *)(param_1 + 0x18c) = 0;
  *(undefined4 *)(param_1 + 400) = 0;
  *(undefined4 *)(param_1 + 0x17c) = 0;
  *(undefined4 *)(param_1 + 0x180) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0x497423f0;
  *(undefined4 *)(param_1 + 0x8c) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x7c) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x80) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x84) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x94) = 0x497423fe;
  *(undefined4 *)(param_1 + 0x90) = 0xbf800000;
  *(undefined4 *)(param_1 + 0x184) = 0;
  return;
}

