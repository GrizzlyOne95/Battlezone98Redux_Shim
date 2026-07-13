
void FUN_0045efa0(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  uint uStack_4c;
  undefined4 local_20 [2];
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008472b0;
  local_10 = ExceptionList;
  uStack_4c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_4c;
  ExceptionList = &local_10;
  uVar1 = 1;
  Getal(&local_15);
  local_20[0] = allocate(uVar1);
  local_8 = 0;
  uVar1 = FUN_00417780(local_20[0]);
  Getal(&local_16);
  puVar2 = local_20;
  uVar1 = FUN_00417780(uVar1,puVar2);
  construct<>(uVar1,puVar2);
  uVar1 = FUN_004242e0(local_20[0]);
  Getal(&local_17);
  puVar2 = local_20;
  uVar1 = FUN_00417780(uVar1,puVar2);
  construct<>(uVar1,puVar2);
  uVar1 = FUN_004242f0(local_20[0]);
  Getal(&local_18);
  puVar2 = local_20;
  uVar1 = FUN_00417780(uVar1,puVar2);
  construct<>(uVar1,puVar2);
  FUN_0045f0bd();
  return;
}

