
void __fastcall FUN_00631aa0(int param_1)

{
  undefined4 uVar1;
  
  *(undefined1 *)(param_1 + 0x54) = 0;
  uVar1 = FUN_005c7e90("recycler",0);
  *(undefined4 *)(param_1 + 0x6c) = uVar1;
  uVar1 = FUN_005c7e90("enemy_turret1");
  *(undefined4 *)(param_1 + 0xac) = uVar1;
  uVar1 = FUN_005c7e90("enemy_turret2");
  *(undefined4 *)(param_1 + 0xb0) = uVar1;
  uVar1 = FUN_005c7e90("enemy_turret3");
  *(undefined4 *)(param_1 + 0xb4) = uVar1;
  uVar1 = FUN_005c7e90("enemy_turret4");
  *(undefined4 *)(param_1 + 0xb8) = uVar1;
  *(undefined4 *)(param_1 + 0xd4) = 0;
  return;
}

