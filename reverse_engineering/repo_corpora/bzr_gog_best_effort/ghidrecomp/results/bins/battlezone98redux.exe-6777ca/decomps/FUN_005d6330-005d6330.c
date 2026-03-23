
/* WARNING: Removing unreachable block (ram,0x005d6396) */

void FUN_005d6330(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  bool bVar4;
  undefined1 local_e8 [64];
  undefined4 local_a8;
  uint local_a4;
  uint local_a0;
  int local_9c;
  int local_98;
  int local_94;
  int local_90;
  int local_8c;
  undefined4 local_88 [16];
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_8c = FUN_00417c70();
  *(undefined1 *)(local_94 + 0x1e9) = 0;
  if (((local_8c != 0) &&
      (iVar1 = (*(code *)**(undefined4 **)(local_8c + 0x18))(), *(int *)(iVar1 + 0x1c) == 4)) &&
     (local_98 = FUN_00417ca0(), local_98 != 0)) {
    iVar1 = (*(code *)**(undefined4 **)(local_8c + 0x18))();
    bVar4 = *(char *)(iVar1 + 0xcc) == 's';
    local_a0 = (uint)bVar4;
    *(bool *)(local_94 + 0x1ea) = bVar4;
    local_a4 = FUN_00417f90();
    for (local_90 = 0; local_90 < 5; local_90 = local_90 + 1) {
      if ((1 << ((byte)local_90 & 0x1f) & local_a4) != 0) {
        local_9c = FUN_00417f60(local_90);
        local_a8 = *(undefined4 *)(local_9c + 8);
        puVar2 = (undefined4 *)
                 FUN_0081fe60(local_e8,*(int *)(local_9c + 0x10) + 0x20,local_9c + 0x28);
        puVar3 = local_48;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar2 = local_48;
        puVar3 = local_88;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        FUN_00689090(local_94 + 0x10,local_88);
        *(undefined1 *)(local_94 + 0x1e8) = 1;
      }
    }
  }
  FUN_0083e885();
  return;
}

