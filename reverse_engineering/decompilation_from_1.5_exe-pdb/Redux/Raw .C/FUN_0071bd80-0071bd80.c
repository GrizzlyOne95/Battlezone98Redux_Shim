
undefined4 * __thiscall FUN_0071bd80(undefined4 *param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856158;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0071e850(param_2);
  local_8 = 0;
  *param_1 = boost::asio::socket_acceptor_service<class_boost::asio::ip::tcp>::vftable;
  FUN_00704ea0(param_2);
  ExceptionList = local_10;
  return param_1;
}

