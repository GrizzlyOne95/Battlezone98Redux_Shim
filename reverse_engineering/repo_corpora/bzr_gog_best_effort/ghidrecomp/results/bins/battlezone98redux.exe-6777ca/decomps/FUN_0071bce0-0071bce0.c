
undefined4 * __thiscall FUN_0071bce0(undefined4 *param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856158;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0071e660(param_2);
  local_8 = 0;
  *param_1 = boost::asio::
             waitable_timer_service<class_std::chrono::steady_clock,struct_boost::asio::wait_traits<class_std::chrono::steady_clock>_>
             ::vftable;
  FUN_0071e690(param_2);
  ExceptionList = local_10;
  return param_1;
}

