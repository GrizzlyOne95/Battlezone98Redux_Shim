
void FUN_0066e170(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  uint uStack_38;
  undefined4 local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084eb50;
  local_10 = ExceptionList;
  uStack_38 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_38;
  ExceptionList = &local_10;
  local_18 = FUN_0066e530(1);
  local_8 = 0;
  uVar1 = FUN_00417780(local_18);
  puVar2 = &local_18;
  uVar1 = FUN_00417780(uVar1,puVar2);
  construct<>(uVar1,puVar2);
  uVar1 = FUN_004242e0(local_18);
  puVar2 = &local_18;
  uVar1 = FUN_00417780(uVar1,puVar2);
  construct<>(uVar1,puVar2);
  uVar1 = FUN_004242f0(local_18);
  puVar2 = &local_18;
  uVar1 = FUN_00417780(uVar1,puVar2);
  construct<>(uVar1,puVar2);
  FUN_0066e259();
  return;
}

