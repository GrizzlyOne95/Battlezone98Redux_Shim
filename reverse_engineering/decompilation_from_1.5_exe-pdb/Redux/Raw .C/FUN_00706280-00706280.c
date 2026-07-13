
shared_ptr<class___ExceptionPtr> * __fastcall
FUN_00706280(shared_ptr<class___ExceptionPtr> *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00856f10;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
            (param_1,(shared_ptr<class___ExceptionPtr> *)&stack0x00000004);
  local_8 = CONCAT31(local_8._1_3_,1);
  uVar2 = FUN_006ba710(&stack0x0000000c,uVar1);
  *(undefined4 *)(param_1 + 8) = uVar2;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0xc));
  local_8 = 0xffffffff;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_1;
}

