
undefined4 * __thiscall FUN_006e2c00(undefined4 *param_1,undefined4 param_2)

{
  FUN_006e43f0();
  *param_1 = boost::asio::detail::win_thread::
             func<struct_boost::asio::detail::win_iocp_io_service::timer_thread_function>::vftable;
  param_1[3] = param_2;
  return param_1;
}

