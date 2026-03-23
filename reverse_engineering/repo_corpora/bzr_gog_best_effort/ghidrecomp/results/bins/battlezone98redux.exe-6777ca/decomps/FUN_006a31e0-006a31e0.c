
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006a31e0(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  undefined4 local_8;
  
  DAT_00931014 = 0;
  _DAT_02c00a98 = 0;
  iVar1 = FUN_00417c70();
  if (iVar1 == 0) {
    local_10 = 1;
  }
  else {
    local_10 = (**(code **)(*(int *)(iVar1 + 0x18) + 4))();
  }
  _DAT_009310b0 = local_10;
  FUN_006a1d40();
  FUN_006a2060();
  DAT_008eda24 = DAT_009310ac - DAT_00931018;
  DAT_008eda20 = DAT_00931024 - DAT_00931020;
  FUN_006a1bb0();
  for (local_8 = 1; local_8 < 0x10; local_8 = local_8 + 1) {
    uVar2 = FUN_005e0bc0(local_8);
    uVar2 = FUN_005e10b0(uVar2);
    FUN_006a90a0(local_8,uVar2);
    FUN_00690120(local_8,uVar2);
  }
  DAT_02c00a94 = *(undefined4 *)(DAT_00920f04 + 0x80);
  DAT_02c00ed8 = *(undefined4 *)(DAT_00920f04 + 0x84);
  FUN_0046eed0(DAT_00931018,DAT_00931020,0x10,DAT_02c00a94,DAT_02c00ed8);
  return;
}

