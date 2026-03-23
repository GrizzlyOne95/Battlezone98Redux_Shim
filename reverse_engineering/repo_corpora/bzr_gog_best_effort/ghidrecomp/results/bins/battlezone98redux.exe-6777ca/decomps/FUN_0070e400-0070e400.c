
void __fastcall FUN_0070e400(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 auStack_44 [4];
  undefined4 uStack_40;
  int iStack_3c;
  int iStack_38;
  undefined1 *puStack_34;
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
  puStack_2c = (undefined1 *)0x70e434;
  local_14 = param_1;
  iStack_28 = FUN_00417780();
  puStack_2c = &stack0x00000004;
  puStack_30 = (undefined1 *)(local_14 + 8);
  puStack_34 = (undefined1 *)local_14;
  iStack_38 = 0x70e44c;
  puVar1 = (undefined4 *)FUN_00718e30();
  iStack_28 = *puVar1;
  puStack_2c = (undefined1 *)(local_14 + 8);
  puStack_30 = (undefined1 *)0x70e45e;
  puStack_2c = (undefined1 *)FUN_00718e20();
  puStack_30 = &stack0x00000004;
  puStack_34 = (undefined1 *)(local_14 + 8);
  iStack_38 = local_14;
  iStack_3c = 0x70e476;
  puStack_2c = (undefined1 *)FUN_0070d630();
  puStack_30 = (undefined1 *)(local_14 + 8);
  puStack_34 = (undefined1 *)0x70e486;
  puStack_30 = (undefined1 *)FUN_004242f0();
  puStack_34 = &stack0x00000004;
  iStack_38 = local_14 + 8;
  iStack_3c = local_14;
  uStack_40 = 0x70e49e;
  uVar2 = FUN_0070d600();
  local_1c = auStack_44;
  local_20 = function<>(uVar2);
  local_8 = 0;
  local_18 = local_20;
  uVar2 = FUN_0070d620(local_14 + 8);
  uVar2 = FUN_0070d600(local_14,local_14 + 8,&stack0x00000004,uVar2);
  local_8 = 0xffffffff;
  FUN_00718e50(uVar2);
  ExceptionList = local_10;
  return;
}

