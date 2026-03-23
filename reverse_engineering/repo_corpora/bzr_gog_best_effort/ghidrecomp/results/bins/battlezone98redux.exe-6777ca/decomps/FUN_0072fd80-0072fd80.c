
void __fastcall FUN_0072fd80(int param_1)

{
  undefined4 uVar1;
  undefined1 auStack_40 [4];
  undefined4 uStack_3c;
  int iStack_38;
  int iStack_34;
  undefined1 *puStack_30;
  undefined1 *puStack_2c;
  int iStack_28;
  uint uStack_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857838;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iStack_28 = param_1 + 8;
  puStack_2c = (undefined1 *)0x72fdb4;
  local_14 = param_1;
  iStack_28 = FUN_00417780();
  puStack_2c = &stack0x00000004;
  puStack_30 = (undefined1 *)(local_14 + 8);
  iStack_34 = local_14;
  iStack_38 = 0x72fdcc;
  iStack_28 = FUN_0072f970();
  puStack_2c = (undefined1 *)(local_14 + 8);
  puStack_30 = (undefined1 *)0x72fddc;
  puStack_2c = (undefined1 *)FUN_004242f0();
  puStack_30 = &stack0x00000004;
  iStack_34 = local_14 + 8;
  iStack_38 = local_14;
  uStack_3c = 0x72fdf4;
  uVar1 = FUN_0070d600();
  local_1c = auStack_40;
  local_20 = function<>(uVar1);
  local_8 = 0;
  local_18 = local_20;
  uVar1 = FUN_0070d620(local_14 + 8);
  uVar1 = FUN_0070d600(local_14,local_14 + 8,&stack0x00000004,uVar1);
  local_8 = 0xffffffff;
  FUN_00718b90(uVar1);
  ExceptionList = local_10;
  return;
}

