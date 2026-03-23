
void __fastcall FUN_0072a6d0(int param_1)

{
  shared_ptr<class___ExceptionPtr> *psVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 *puStack_54;
  int iStack_50;
  undefined1 auStack_4c [4];
  undefined4 uStack_48;
  int iStack_44;
  int iStack_40;
  undefined1 *puStack_3c;
  undefined1 *puStack_38;
  int iStack_34;
  uint uStack_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined1 *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859740;
  local_10 = ExceptionList;
  uStack_30 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iStack_34 = param_1 + 8;
  puStack_38 = (undefined1 *)0x72a704;
  local_14 = param_1;
  iStack_34 = FUN_00417780();
  puStack_38 = &stack0x00000004;
  puStack_3c = (undefined1 *)(local_14 + 8);
  iStack_40 = local_14;
  iStack_44 = 0x72a71c;
  iStack_34 = FUN_0072f970();
  puStack_38 = (undefined1 *)(local_14 + 8);
  puStack_3c = (undefined1 *)0x72a72c;
  puStack_38 = (undefined1 *)FUN_004242f0();
  puStack_3c = &stack0x00000004;
  iStack_40 = local_14 + 8;
  iStack_44 = local_14;
  uStack_48 = 0x72a744;
  iStack_50 = FUN_0070d600();
  local_20 = auStack_4c;
  puStack_54 = (undefined1 *)0x72a752;
  local_24 = function<>();
  local_8 = 0;
  iStack_50 = local_14 + 8;
  puStack_54 = (undefined1 *)0x72a76e;
  local_18 = local_24;
  iStack_50 = FUN_0070d620();
  puStack_54 = &stack0x00000004;
  psVar1 = (shared_ptr<class___ExceptionPtr> *)FUN_0070d600(local_14,local_14 + 8);
  local_28 = (undefined1 *)&puStack_54;
  local_2c = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&puStack_54,psVar1);
  local_8 = CONCAT31(local_8._1_3_,1);
  local_1c = local_2c;
  uVar2 = FUN_0070d610(local_14 + 8);
  puVar3 = (undefined4 *)FUN_0070d600(local_14,local_14 + 8,&stack0x00000004,uVar2);
  local_8 = 0xffffffff;
  FUN_0072b810(*puVar3);
  ExceptionList = local_10;
  return;
}

