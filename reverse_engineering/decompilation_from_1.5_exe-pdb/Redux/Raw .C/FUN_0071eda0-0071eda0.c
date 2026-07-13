
undefined4 * __thiscall FUN_0071eda0(undefined4 *param_1,int param_2)

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
             _Func_impl<struct_std::_Callable_obj<class_std::_Bind<1,void,struct_std::_Pmf_wrap<void_(__thiscall_websocketpp::connection<struct_websocketpp::config::asio_client>::*)(class_std::error_code_const&),void,class_websocketpp::connection<struct_websocketpp::config::asio_client>,class_std::error_code_const&>,class_std::shared_ptr<class_websocketpp::connection<struct_websocketpp::config::asio_client>_>,class_std::_Ph<1>&>,0>,class_std::allocator<class_std::_Func_class<void,class_std::error_code_const&>_>,void,class_std::error_code_const&>
             ::vftable;
  FID_conflict__Callable_obj<class_<lambda_22c800ac295261976027df48869e3267>,0><class_<lambda_22c800ac295261976027df48869e3267>_>
            (param_2 + 8);
  allocator<>(param_2 + 0x20);
  ExceptionList = local_10;
  return param_1;
}

