
undefined4 * __thiscall FUN_0071bdf0(undefined4 *param_1,undefined1 param_2,undefined1 param_3)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00858636;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_0071e810(param_2,param_3);
  local_8._0_1_ = 1;
  *param_1 = websocketpp::processor::hybi00<struct_websocketpp::config::asio_client>::vftable;
  *(undefined1 *)(param_1 + 3) = 0;
  *(undefined1 *)((int)param_1 + 0xd) = 0xff;
  param_1[4] = 0;
  std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
            ((shared_ptr<class___ExceptionPtr> *)(param_1 + 5),
             (shared_ptr<class___ExceptionPtr> *)&stack0x0000000c);
  local_8._0_1_ = 2;
  FUN_0068b0a0(uVar1);
  local_8 = CONCAT31(local_8._1_3_,3);
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 9));
  local_8 = 0xffffffff;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_1;
}

