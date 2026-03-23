
void __fastcall FUN_0065c460(int param_1)

{
  undefined4 uVar1;
  int local_24;
  char local_1c [20];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_005c7e90("west_1_1");
  *(undefined4 *)(param_1 + 0x78) = uVar1;
  uVar1 = FUN_005c7e90("west_1_2");
  *(undefined4 *)(param_1 + 0x7c) = uVar1;
  uVar1 = FUN_005c7e90("west_1_3");
  *(undefined4 *)(param_1 + 0x80) = uVar1;
  uVar1 = FUN_005c7e90("west_1_4");
  *(undefined4 *)(param_1 + 0x84) = uVar1;
  uVar1 = FUN_005c7e90("east_1_1");
  *(undefined4 *)(param_1 + 0x88) = uVar1;
  uVar1 = FUN_005c7e90("east_1_2");
  *(undefined4 *)(param_1 + 0x8c) = uVar1;
  uVar1 = FUN_005c7e90("east_1_3");
  *(undefined4 *)(param_1 + 0x90) = uVar1;
  uVar1 = FUN_005c7e90("east_1_4");
  *(undefined4 *)(param_1 + 0x94) = uVar1;
  uVar1 = FUN_005c7e90(&DAT_00891958);
  *(undefined4 *)(param_1 + 0x170) = uVar1;
  FUN_005cd7f0(*(undefined4 *)(param_1 + 0x170),&DAT_00890cfc);
  uVar1 = FUN_005c7e90("howitzer_nw");
  *(undefined4 *)(param_1 + 0x98) = uVar1;
  uVar1 = FUN_005c7e90("howitzer_ne");
  *(undefined4 *)(param_1 + 0x9c) = uVar1;
  uVar1 = FUN_005c7e90("west_power");
  *(undefined4 *)(param_1 + 0xa0) = uVar1;
  uVar1 = FUN_005c7e90("east_power");
  *(undefined4 *)(param_1 + 0xa4) = uVar1;
  uVar1 = FUN_005c7e90("east_bolt");
  *(undefined4 *)(param_1 + 0xb4) = uVar1;
  uVar1 = FUN_005c7e90("west_bolt");
  *(undefined4 *)(param_1 + 0xb0) = uVar1;
  uVar1 = FUN_005c7e90("walker_1");
  *(undefined4 *)(param_1 + 0xb8) = uVar1;
  for (local_24 = 0; local_24 < 6; local_24 = local_24 + 1) {
    sprintf(local_1c,"magpull_%d",local_24 + 1);
    uVar1 = FUN_005c7e90(local_1c);
    *(undefined4 *)(param_1 + 0xd0 + local_24 * 4) = uVar1;
  }
  for (local_24 = 0; local_24 < 4; local_24 = local_24 + 1) {
    sprintf(local_1c,"west_mag_%d",local_24 + 1);
    uVar1 = FUN_005c7e90(local_1c);
    *(undefined4 *)(param_1 + 0xe8 + local_24 * 4) = uVar1;
    sprintf(local_1c,"east_mag_%d",local_24 + 1);
    uVar1 = FUN_005c7e90(local_1c);
    *(undefined4 *)(param_1 + 0xf8 + local_24 * 4) = uVar1;
  }
  for (local_24 = 0; local_24 < 0x1a; local_24 = local_24 + 1) {
    sprintf(local_1c,"sniper_%d",local_24 + 1);
    uVar1 = FUN_005c7e90(local_1c);
    *(undefined4 *)(param_1 + 0x108 + local_24 * 4) = uVar1;
  }
  uVar1 = FUN_005c7e90("west_comm");
  *(undefined4 *)(param_1 + 0xa8) = uVar1;
  uVar1 = FUN_005c7e90("east_comm");
  *(undefined4 *)(param_1 + 0xac) = uVar1;
  *(undefined1 *)(param_1 + 0x55) = 0;
  *(undefined1 *)(param_1 + 0x56) = 0;
  *(undefined1 *)(param_1 + 0x57) = 0;
  *(undefined1 *)(param_1 + 0x58) = 0;
  *(undefined1 *)(param_1 + 0x59) = 0;
  *(undefined1 *)(param_1 + 0x5a) = 0;
  *(undefined1 *)(param_1 + 0x5b) = 0;
  *(undefined1 *)(param_1 + 0x5c) = 0;
  *(undefined1 *)(param_1 + 0x5d) = 0;
  *(undefined1 *)(param_1 + 0x5e) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x180) = 1;
  *(undefined4 *)(param_1 + 0x184) = 0;
  FUN_0083e885();
  return;
}

