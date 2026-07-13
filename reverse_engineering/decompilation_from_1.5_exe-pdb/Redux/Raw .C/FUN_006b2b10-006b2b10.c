
undefined4 * __fastcall FUN_006b2b10(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850648;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006aca20(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = boost::asio::detail::
             timer_queue<struct_boost::asio::time_traits<class_boost::posix_time::ptime>_>::vftable;
  FUN_006c9bf0();
  ExceptionList = local_10;
  return param_1;
}

