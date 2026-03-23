
undefined4 * __thiscall FUN_0072cd10(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
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
             _Func_impl<struct_std::_Callable_obj<class_std::_Bind<1,void,struct_std::_Pmf_wrap<void_(__thiscall_websocketpp::connection<struct_websocketpp::config::asio_client>::*)(class_std::error_code_const&),void,class_websocketpp::connection<struct_websocketpp::config::asio_client>,class_std::error_code_const&>,class_websocketpp::connection<struct_websocketpp::config::asio_client>*_const,class_std::_Ph<1>&>,0>,class_std::allocator<class_std::_Func_class<void,class_std::error_code_const&>_>,void,class_std::error_code_const&>
             ::vftable;
  uVar1 = FUN_00417780(param_2 + 8);
  FID_conflict__Callable_obj<class_<lambda_22c800ac295261976027df48869e3267>,0><class_<lambda_22c800ac295261976027df48869e3267>_>
            (uVar1);
  allocator<>(param_2 + 0x18);
  ExceptionList = local_10;
  return param_1;
}

