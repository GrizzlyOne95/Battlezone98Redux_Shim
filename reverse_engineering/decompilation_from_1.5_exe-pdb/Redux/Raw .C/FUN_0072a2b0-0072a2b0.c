
void __fastcall FUN_0072a2b0(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
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
  puStack_c = &LAB_008596a8;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iStack_28 = param_1 + 4;
  puStack_2c = (undefined1 *)0x72a2e4;
  local_14 = param_1;
  iStack_28 = FUN_00417780();
  puStack_2c = &stack0x00000004;
  puStack_30 = (undefined1 *)(local_14 + 4);
  iStack_28 = FUN_00718e30(local_14);
  puStack_2c = (undefined1 *)(local_14 + 4);
  puStack_30 = (undefined1 *)0x72a30c;
  puStack_2c = (undefined1 *)FUN_00718e20();
  puStack_30 = &stack0x00000004;
  uVar1 = FUN_0070d630(local_14,local_14 + 4);
  local_1c = (undefined1 *)&puStack_30;
  local_20 = shared_ptr<>(uVar1);
  local_8 = 0;
  local_18 = local_20;
  uVar1 = FUN_004242e0(local_14 + 4);
  puVar2 = (undefined4 *)FUN_0070d600(local_14,local_14 + 4,&stack0x00000004,uVar1);
  local_8 = 0xffffffff;
  FUN_0072b5b0(*puVar2);
  ExceptionList = local_10;
  return;
}

