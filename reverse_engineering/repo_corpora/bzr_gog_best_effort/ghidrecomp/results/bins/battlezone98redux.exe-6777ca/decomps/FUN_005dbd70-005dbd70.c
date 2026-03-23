
void __fastcall FUN_005dbd70(int param_1)

{
  undefined4 uVar1;
  uint local_c;
  
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  uVar1 = FUN_0068bed0("status_left");
  *(undefined4 *)(param_1 + 8) = uVar1;
  uVar1 = FUN_0068bed0("status_right");
  *(undefined4 *)(param_1 + 0xc) = uVar1;
  DAT_00918350 = FUN_0068bed0("hulltext");
  DAT_0091833c = FUN_0068bed0("shulltext");
  uVar1 = FUN_0068bed0("hull_bar");
  *(undefined4 *)(param_1 + 0x14) = uVar1;
  DAT_00918360 = FUN_0068bed0("ammotext");
  DAT_0091834c = FUN_0068bed0("sammotext");
  uVar1 = FUN_0068bed0("ammo_bar");
  *(undefined4 *)(param_1 + 0x20) = uVar1;
  DAT_00918348 = FUN_0068bed0("weaponunderlay");
  DAT_00918354 = FUN_0068bed0("sweaponunderlay");
  for (local_c = 0; local_c < 5; local_c = local_c + 1) {
    uVar1 = FUN_0068bed0((&PTR_s_weapon___008ea398)[local_c * 2]);
    *(undefined4 *)(&DAT_008ea39c + local_c * 8) = uVar1;
  }
  *(undefined1 *)(param_1 + 0x28) = 0;
  *(undefined1 *)(param_1 + 0x29) = 0;
  return;
}

