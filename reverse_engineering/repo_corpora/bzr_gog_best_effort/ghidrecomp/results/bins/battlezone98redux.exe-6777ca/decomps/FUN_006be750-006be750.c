
/* WARNING: Removing unreachable block (ram,0x006be86d) */
/* WARNING: Removing unreachable block (ram,0x006be881) */
/* WARNING: Removing unreachable block (ram,0x006be889) */
/* WARNING: Removing unreachable block (ram,0x006be8d7) */

void FUN_006be750(void)

{
  undefined4 uVar1;
  uint uVar2;
  undefined1 *puVar3;
  uint uStack_a8;
  undefined1 local_98 [8];
  undefined1 local_90 [8];
  undefined1 local_88 [4];
  undefined1 local_84 [16];
  undefined4 local_74;
  undefined1 local_6d;
  undefined1 local_34 [28];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00851560;
  local_10 = ExceptionList;
  uStack_a8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_a8;
  ExceptionList = &local_10;
  local_18 = uStack_a8;
  uVar1 = FUN_006b3f20(local_88);
  FUN_006cb230(uVar1);
  FUN_004fbb60();
  puVar3 = local_90;
  uVar2 = (uint)DAT_00945704;
  uVar1 = FUN_006b3160(uVar2,puVar3);
  uVar1 = FUN_006cb490(uVar1,uVar2);
  FUN_006cb330(local_98,uVar1,puVar3);
  FUN_006cb370(local_34);
  DAT_00945704 = FUN_006cac60();
  local_6d = 0;
  local_74 = 0x100000;
  local_8 = 0;
  FUN_00447eb0(0x100000);
  FUN_006db7b0(local_84);
  local_6d = 1;
  FUN_006be85b();
  return;
}

