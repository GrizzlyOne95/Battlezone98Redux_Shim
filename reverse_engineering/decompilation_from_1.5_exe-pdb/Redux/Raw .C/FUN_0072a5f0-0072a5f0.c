
void __fastcall FUN_0072a5f0(int param_1)

{
  shared_ptr<class___ExceptionPtr> *psVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
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
  puStack_c = &LAB_00859708;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iStack_28 = param_1 + 8;
  puStack_2c = (undefined1 *)0x72a624;
  local_14 = param_1;
  iStack_28 = FUN_00417780();
  puStack_2c = &stack0x00000004;
  puStack_30 = (undefined1 *)(local_14 + 8);
  iStack_28 = FUN_0072f970(local_14);
  puStack_2c = (undefined1 *)(local_14 + 8);
  puStack_30 = (undefined1 *)0x72a64c;
  puStack_2c = (undefined1 *)FUN_004242e0();
  puStack_30 = &stack0x00000004;
  psVar1 = (shared_ptr<class___ExceptionPtr> *)FUN_0070d600(local_14,local_14 + 8);
  local_1c = (undefined1 *)&puStack_30;
  local_20 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&puStack_30,psVar1);
  local_8 = 0;
  local_18 = local_20;
  uVar2 = FUN_00425000(local_14 + 8);
  puVar3 = (undefined4 *)FUN_0070d600(local_14,local_14 + 8,&stack0x00000004,uVar2);
  local_8 = 0xffffffff;
  FUN_0072b780(*puVar3);
  ExceptionList = local_10;
  return;
}

