
void FUN_0043a7e0(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined1 local_e4 [64];
  undefined1 local_a4 [4];
  int local_a0;
  int local_9c;
  int *local_98;
  undefined4 local_94 [16];
  undefined4 local_54 [16];
  undefined1 local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((((DAT_00915594 != 0) && (iVar1 = ___scrt_is_ucrt_dll_in_use(DAT_00915594), iVar1 != 0)) &&
      (local_a0 = FUN_00439e60(), local_a0 != 0)) &&
     ((local_98 = (int *)FUN_00439e70(), local_98 != (int *)0x0 &&
      (local_9c = *local_98, local_9c != 0)))) {
    iVar1 = ___scrt_is_user_matherr_present();
    if (iVar1 == 0) {
      FUN_0043c510();
    }
    else {
      FUN_0043c4d0();
    }
    puVar2 = (undefined4 *)FUN_0062e070(local_e4,local_9c,0);
    puVar3 = local_94;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar2 = local_94;
    puVar3 = local_54;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    FUN_0043c550(local_54);
    FUN_0062bec0(*local_98,local_14,local_a4);
    FUN_0043c490(local_14);
    FUN_0043c6c0(DAT_00915594);
  }
  FUN_0083e885();
  return;
}

