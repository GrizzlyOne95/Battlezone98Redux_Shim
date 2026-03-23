
undefined4 *
FUN_0071beb0(undefined1 param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  shared_ptr<class___ExceptionPtr> asStack_30 [8];
  undefined4 uStack_28;
  uint uStack_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00858668;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  uStack_28 = param_5;
  local_18 = asStack_30;
  local_1c = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       (asStack_30,(shared_ptr<class___ExceptionPtr> *)&param_3);
  local_20 = FUN_0071bf40(param_1,param_2);
  *local_14 = websocketpp::processor::hybi07<struct_websocketpp::config::asio_client>::vftable;
  local_8 = 0xffffffff;
  uStack_28 = 0x71bf24;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return local_14;
}

