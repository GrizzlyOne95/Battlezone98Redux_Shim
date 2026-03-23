
void __fastcall FUN_0072ace0(undefined1 *param_1)

{
  shared_ptr<class___ExceptionPtr> *psVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 *puStack_80;
  undefined1 *puStack_78;
  undefined1 *puStack_74;
  undefined1 auStack_70 [4];
  undefined4 uStack_6c;
  undefined1 *puStack_68;
  undefined1 *puStack_64;
  undefined1 *puStack_60;
  undefined1 *puStack_5c;
  undefined1 *puStack_58;
  undefined1 *puStack_54;
  undefined1 *puStack_50;
  undefined1 *puStack_4c;
  uint uStack_48;
  undefined4 local_44;
  undefined1 *local_40;
  undefined4 local_3c;
  undefined1 *local_38;
  undefined4 local_34;
  undefined1 *local_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859800;
  local_10 = ExceptionList;
  uStack_48 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_4c = param_1 + 8;
  puStack_50 = (undefined1 *)0x72ad14;
  local_14 = param_1;
  puStack_4c = (undefined1 *)FUN_00417780();
  puStack_50 = &stack0x00000004;
  puStack_54 = local_14 + 8;
  puStack_58 = local_14;
  puStack_5c = (undefined1 *)0x72ad2c;
  puStack_58 = (undefined1 *)FUN_00718e30();
  local_28 = (undefined1 *)&puStack_54;
  puStack_5c = (undefined1 *)0x72ad3a;
  local_2c = FUN_006d4f40();
  local_8 = 0;
  puStack_58 = local_14 + 8;
  puStack_5c = (undefined1 *)0x72ad56;
  local_18 = local_2c;
  puStack_58 = (undefined1 *)FUN_00718e20();
  puStack_5c = &stack0x00000004;
  puStack_60 = local_14 + 8;
  puStack_64 = local_14;
  puStack_68 = (undefined1 *)0x72ad6e;
  puStack_58 = (undefined1 *)FUN_0070d630();
  puStack_5c = local_14 + 8;
  puStack_60 = (undefined1 *)0x72ad7e;
  puStack_5c = (undefined1 *)FUN_004242f0();
  puStack_60 = &stack0x00000004;
  puStack_64 = local_14 + 8;
  puStack_68 = local_14;
  uStack_6c = 0x72ad96;
  puStack_74 = (undefined1 *)FUN_0070d600();
  local_30 = auStack_70;
  puStack_78 = (undefined1 *)0x72ada4;
  local_34 = function<>();
  local_8._0_1_ = 1;
  puStack_74 = local_14 + 8;
  puStack_78 = (undefined1 *)0x72adbd;
  local_1c = local_34;
  puStack_74 = (undefined1 *)FUN_0070d620();
  puStack_78 = &stack0x00000004;
  puStack_80 = local_14;
  psVar1 = (shared_ptr<class___ExceptionPtr> *)FUN_0070d600();
  local_38 = (undefined1 *)&puStack_78;
  puStack_80 = (undefined1 *)0x72ade3;
  local_3c = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&puStack_78,psVar1);
  local_8._0_1_ = 2;
  puStack_80 = (undefined1 *)0x72adfc;
  local_20 = local_3c;
  FUN_0070d610();
  puStack_80 = &stack0x00000004;
  psVar1 = (shared_ptr<class___ExceptionPtr> *)FUN_0070d600(local_14,local_14 + 8);
  local_40 = (undefined1 *)&puStack_80;
  local_44 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&puStack_80,psVar1);
  local_8 = CONCAT31(local_8._1_3_,3);
  local_24 = local_44;
  uVar2 = FUN_0070d5f0(local_14 + 8);
  puVar3 = (undefined4 *)FUN_0070d600(local_14,local_14 + 8,&stack0x00000004,uVar2);
  local_8 = 0xffffffff;
  FUN_0072b8d0(*puVar3);
  ExceptionList = local_10;
  return;
}

