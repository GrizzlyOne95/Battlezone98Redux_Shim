
undefined4 * __thiscall FUN_00713500(undefined4 *param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857bd8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007127d0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = std::
             _Func_impl<struct_std::_Callable_obj<class_std::_Bind<1,void,struct_std::_Pmf_wrap<void_(__thiscall_websocketpp::transport::asio::endpoint<struct_websocketpp::config::asio_client::transport_config>::*)(class_std::shared_ptr<class_websocketpp::transport::asio::connection<struct_websocketpp::config::asio_client::transport_config>_>,class_std::shared_ptr<class_boost::asio::basic_waitable_timer<class_std::chrono::steady_clock,struct_boost::asio::wait_traits<class_std::chrono::steady_clock>,class_boost::asio::waitable_timer_service<class_std::chrono::steady_clock,struct_boost::asio::wait_traits<class_std::chrono::steady_clock>_>_>_>,class_std::function<void___cdecl(class_std::error_code_const&)>,class_std::error_code_const&),void,class_websocketpp::transport::asio::endpoint<struct_websocketpp::config::asio_client::transport_config>,class_std::shared_ptr<class_websocketpp::transport::asio::connection<struct_websocketpp::config::asio_client::transport_config>_>,class_std::shared_ptr<class_boo...cator<class_std::_Func_class<void,class_std::error_code_const&>_>,void,class_std::error_code_const&>
             ::vftable;
  FID_conflict__Callable_obj<class_<lambda_22c800ac295261976027df48869e3267>,0><class_<lambda_22c800ac295261976027df48869e3267>_>
            (param_2 + 8);
  allocator<>(param_2 + 0x48);
  ExceptionList = local_10;
  return param_1;
}

