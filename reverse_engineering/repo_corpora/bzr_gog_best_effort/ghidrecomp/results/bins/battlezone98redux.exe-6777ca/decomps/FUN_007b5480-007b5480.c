
void __fastcall FUN_007b5480(int param_1)

{
  undefined4 uVar1;
  undefined1 local_28 [32];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_0061f650("throttle_up",local_28);
  FUN_0081c440("throttle_up",local_28);
  uVar1 = FUN_007b5460(local_28);
  (**(code **)(**(int **)(param_1 + 0x148) + 0x3c))(uVar1);
  FUN_0061f650("throttle_down",local_28);
  FUN_0081c440("throttle_down",local_28);
  uVar1 = FUN_007b5460(local_28);
  (**(code **)(**(int **)(param_1 + 0x144) + 0x3c))(uVar1);
  FUN_0061f650("strafe_right",local_28);
  FUN_0081c440("strafe_right",local_28);
  uVar1 = FUN_007b5460(local_28);
  (**(code **)(**(int **)(param_1 + 0x158) + 0x3c))(uVar1);
  FUN_0061f650("strafe_left",local_28);
  FUN_0081c440("strafe_left",local_28);
  uVar1 = FUN_007b5460(local_28);
  (**(code **)(**(int **)(param_1 + 0x154) + 0x3c))(uVar1);
  FUN_0061f650(&DAT_008857d0,local_28);
  FUN_0081c440(&DAT_008857d0,local_28);
  uVar1 = FUN_007b5460(local_28);
  (**(code **)(**(int **)(param_1 + 0x160) + 0x3c))(uVar1);
  FUN_0061f650("turbo",local_28);
  FUN_0081c440("turbo",local_28);
  uVar1 = FUN_007b5460(local_28);
  (**(code **)(**(int **)(param_1 + 0x15c) + 0x3c))(uVar1);
  FUN_0061f650("pitch_down",local_28);
  FUN_0081c440("pitch_down",local_28);
  uVar1 = FUN_007b5460(local_28);
  (**(code **)(**(int **)(param_1 + 0x150) + 0x3c))(uVar1);
  FUN_0061f650("pitch_up",local_28);
  FUN_0081c440("pitch_up",local_28);
  uVar1 = FUN_007b5460(local_28);
  (**(code **)(**(int **)(param_1 + 0x14c) + 0x3c))(uVar1);
  FUN_0061f650("steer_right",local_28);
  FUN_0081c440("steer_right",local_28);
  uVar1 = FUN_007b5460(local_28);
  (**(code **)(**(int **)(param_1 + 0x164) + 0x3c))(uVar1);
  FUN_0061f650("steer_left",local_28);
  FUN_0081c440("steer_left",local_28);
  uVar1 = FUN_007b5460(local_28);
  (**(code **)(**(int **)(param_1 + 0x168) + 0x3c))(uVar1);
  FUN_0061f650("weapon_fire",local_28);
  FUN_0081c440("weapon_fire",local_28);
  uVar1 = FUN_007b5460(local_28);
  (**(code **)(**(int **)(param_1 + 0x16c) + 0x3c))(uVar1);
  FUN_0061f650("weapon_cycle",local_28);
  FUN_0081c440("weapon_cycle",local_28);
  uVar1 = FUN_007b5460(local_28);
  (**(code **)(**(int **)(param_1 + 0x170) + 0x3c))(uVar1);
  FUN_0083e885();
  return;
}

