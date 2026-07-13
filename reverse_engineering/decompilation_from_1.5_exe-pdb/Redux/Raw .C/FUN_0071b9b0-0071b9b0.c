
undefined4 * __thiscall FUN_0071b9b0(undefined4 *param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856158;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0071e4c0(param_2);
  local_8 = 0;
  *param_1 = boost::asio::ip::resolver_service<class_boost::asio::ip::tcp>::vftable;
  FUN_0071e4f0(param_2);
  ExceptionList = local_10;
  return param_1;
}

