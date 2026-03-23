
void FUN_0079c620(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_3c [24];
  uint uStack_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859c68;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_1c = auStack_3c;
  local_20 = basic_string<>("sniper");
  local_8 = 0;
  uVar2 = *(undefined4 *)(local_14 + 0x1a4);
  local_18 = local_20;
  iVar1 = FUN_0056f900(uVar2);
  local_8 = 0xffffffff;
  FUN_0079b880(iVar1 + 0x124,uVar2);
  ExceptionList = local_10;
  return;
}

