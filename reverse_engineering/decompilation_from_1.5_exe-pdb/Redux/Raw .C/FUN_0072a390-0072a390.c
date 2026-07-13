
void __fastcall FUN_0072a390(undefined1 *param_1)

{
  shared_ptr<class___ExceptionPtr> *psVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 *puStack_40;
  undefined1 *puStack_38;
  undefined1 *puStack_34;
  uint uStack_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined1 *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008596e0;
  local_10 = ExceptionList;
  uStack_30 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_34 = param_1 + 4;
  puStack_38 = (undefined1 *)0x72a3c4;
  local_14 = param_1;
  puStack_34 = (undefined1 *)FUN_00417780();
  puStack_38 = &stack0x00000004;
  puStack_40 = local_14;
  psVar1 = (shared_ptr<class___ExceptionPtr> *)FUN_00718e30();
  local_20 = (undefined1 *)&puStack_38;
  puStack_40 = (undefined1 *)0x72a3ea;
  local_24 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&puStack_38,psVar1);
  local_8 = 0;
  puStack_40 = (undefined1 *)0x72a406;
  local_18 = local_24;
  FUN_00718e20();
  puStack_40 = &stack0x00000004;
  uVar2 = FUN_0070d630(local_14,local_14 + 4);
  local_28 = (undefined1 *)&puStack_40;
  local_2c = shared_ptr<>(uVar2);
  local_8 = CONCAT31(local_8._1_3_,1);
  local_1c = local_2c;
  uVar2 = FUN_004242e0(local_14 + 4);
  puVar3 = (undefined4 *)FUN_0070d600(local_14,local_14 + 4,&stack0x00000004,uVar2);
  local_8 = 0xffffffff;
  FUN_0072b630(*puVar3);
  ExceptionList = local_10;
  return;
}

