
void __fastcall FUN_006fdae0(undefined1 *param_1)

{
  shared_ptr<class___ExceptionPtr> *psVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 *puStack_68;
  undefined1 *puStack_60;
  undefined1 *puStack_5c;
  undefined1 auStack_58 [4];
  undefined4 uStack_54;
  undefined1 *puStack_50;
  undefined1 *puStack_4c;
  undefined1 *puStack_48;
  undefined1 *puStack_44;
  undefined1 *puStack_40;
  uint uStack_3c;
  undefined4 local_38;
  undefined1 *local_34;
  undefined4 local_30;
  undefined1 *local_2c;
  undefined4 local_28;
  undefined1 *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855db8;
  local_10 = ExceptionList;
  uStack_3c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_40 = param_1 + 8;
  puStack_44 = (undefined1 *)0x6fdb14;
  local_14 = param_1;
  puStack_40 = (undefined1 *)FUN_00417780();
  puStack_44 = &stack0x00000004;
  puStack_48 = local_14 + 8;
  puStack_4c = local_14;
  puStack_50 = (undefined1 *)0x6fdb2c;
  puStack_40 = (undefined1 *)FUN_0070d630();
  puStack_44 = local_14 + 8;
  puStack_48 = (undefined1 *)0x6fdb3c;
  puStack_44 = (undefined1 *)FUN_004242f0();
  puStack_48 = &stack0x00000004;
  puStack_4c = local_14 + 8;
  puStack_50 = local_14;
  uStack_54 = 0x6fdb54;
  puStack_5c = (undefined1 *)FUN_0070d600();
  local_24 = auStack_58;
  puStack_60 = (undefined1 *)0x6fdb62;
  local_28 = function<>();
  local_8 = 0;
  puStack_5c = local_14 + 8;
  puStack_60 = (undefined1 *)0x6fdb7e;
  local_18 = local_28;
  puStack_5c = (undefined1 *)FUN_0070d620();
  puStack_60 = &stack0x00000004;
  puStack_68 = local_14;
  psVar1 = (shared_ptr<class___ExceptionPtr> *)FUN_0070d600();
  local_2c = (undefined1 *)&puStack_60;
  puStack_68 = (undefined1 *)0x6fdba4;
  local_30 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&puStack_60,psVar1);
  local_8._0_1_ = 1;
  puStack_68 = (undefined1 *)0x6fdbbd;
  local_1c = local_30;
  FUN_0070d610();
  puStack_68 = &stack0x00000004;
  psVar1 = (shared_ptr<class___ExceptionPtr> *)FUN_0070d600(local_14,local_14 + 8);
  local_34 = (undefined1 *)&puStack_68;
  local_38 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&puStack_68,psVar1);
  local_8 = CONCAT31(local_8._1_3_,2);
  local_20 = local_38;
  uVar2 = FUN_0070d5f0(local_14 + 8);
  puVar3 = (undefined4 *)FUN_0070d600(local_14,local_14 + 8,&stack0x00000004,uVar2);
  local_8 = 0xffffffff;
  FUN_00700990(*puVar3);
  ExceptionList = local_10;
  return;
}

