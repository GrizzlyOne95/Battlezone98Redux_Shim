
undefined4 * __thiscall
FUN_0071bfd0(undefined4 *param_1,undefined1 param_2,undefined1 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008586c1;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_0071e810(param_2,param_3);
  local_8._0_1_ = 1;
  *param_1 = websocketpp::processor::hybi13<struct_websocketpp::config::asio_client>::vftable;
  FUN_006ba100(uVar1);
  std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
            ((shared_ptr<class___ExceptionPtr> *)(param_1 + 4),
             (shared_ptr<class___ExceptionPtr> *)&param_4);
  local_8._0_1_ = 2;
  Concurrency::details::SchedulerBase::NumaInformation::NumaInformation
            ((NumaInformation *)(param_1 + 8));
  local_8._0_1_ = 3;
  Concurrency::details::SchedulerBase::NumaInformation::NumaInformation
            ((NumaInformation *)(param_1 + 0xd));
  local_8 = CONCAT31(local_8._1_3_,4);
  FUN_006ba210();
  param_1[0x16] = param_6;
  FUN_007058a0();
  local_8 = 0xffffffff;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_1;
}

