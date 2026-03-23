
undefined4 * __fastcall FUN_0071fc80(undefined4 *param_1)

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
             timer_queue<struct_boost::asio::detail::chrono_time_traits<class_std::chrono::steady_clock,struct_boost::asio::wait_traits<class_std::chrono::steady_clock>_>_>
             ::vftable;
  param_1[2] = 0;
  vector<>();
  ExceptionList = local_10;
  return param_1;
}

