
undefined4 * __thiscall FUN_00712fc0(undefined4 *param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857b78;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00712730(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = std::
             _Func_impl<struct_std::_Callable_obj<class_std::_Bind<1,void,void_(__cdecl*const)(class_std::weak_ptr<void>,class_boost::asio::basic_stream_socket<class_boost::asio::ip::tcp,class_boost::asio::stream_socket_service<class_boost::asio::ip::tcp>_>&),class_std::_Ph<1>&,class_std::_Ph<2>&>,0>,class_std::allocator<class_std::_Func_class<void,class_std::weak_ptr<void>,class_boost::asio::basic_stream_socket<class_boost::asio::ip::tcp,class_boost::asio::stream_socket_service<class_boost::asio::ip::tcp>_>&>_>,void,class_std::weak_ptr<void>,class_boost::asio::basic_stream_socket<class_boost::asio::ip::tcp,class_boost::asio::stream_socket_service<class_boost::asio::ip::tcp>_>&>
             ::vftable;
  FID_conflict__Callable_obj<class_<lambda_22c800ac295261976027df48869e3267>,0><class_<lambda_22c800ac295261976027df48869e3267>_>
            (param_2 + 4);
  allocator<>(param_2 + 0xc);
  ExceptionList = local_10;
  return param_1;
}

