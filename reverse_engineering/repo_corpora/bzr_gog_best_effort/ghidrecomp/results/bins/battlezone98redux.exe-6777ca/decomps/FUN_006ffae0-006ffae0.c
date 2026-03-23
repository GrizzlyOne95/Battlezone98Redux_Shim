
undefined4 * __thiscall FUN_006ffae0(undefined4 *param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856158;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00704d60(param_2);
  local_8 = 0;
  *param_1 = boost::asio::
             deadline_timer_service<class_boost::posix_time::ptime,struct_boost::asio::time_traits<class_boost::posix_time::ptime>_>
             ::vftable;
  FUN_00704d90(param_2);
  ExceptionList = local_10;
  return param_1;
}

