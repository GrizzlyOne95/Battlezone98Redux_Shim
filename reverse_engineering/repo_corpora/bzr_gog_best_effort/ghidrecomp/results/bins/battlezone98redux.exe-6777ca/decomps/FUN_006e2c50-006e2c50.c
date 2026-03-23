
undefined4 * __thiscall FUN_006e2c50(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_006e43f0();
  *param_1 = boost::asio::detail::win_thread::
             func<class_boost::asio::detail::binder1<void_(__cdecl*)(class_boost::asio::detail::select_reactor*),class_boost::asio::detail::select_reactor*>_>
             ::vftable;
  param_1[3] = param_2;
  param_1[4] = param_3;
  return param_1;
}

