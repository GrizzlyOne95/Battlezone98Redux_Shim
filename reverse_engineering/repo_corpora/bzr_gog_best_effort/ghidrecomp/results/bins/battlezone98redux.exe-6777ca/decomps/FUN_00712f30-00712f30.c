
undefined4 * __thiscall FUN_00712f30(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857b48;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007126e0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = std::
             _Func_impl<struct_std::_Callable_obj<class_std::_Bind<1,void,struct_std::_Pmf_wrap<void_(__thiscall_cBZRNetInterfaceHelper::*)(class_std::weak_ptr<void>,class_std::shared_ptr<class_websocketpp::message_buffer::message<class_websocketpp::message_buffer::alloc::con_msg_manager>_>),void,class_cBZRNetInterfaceHelper,class_std::weak_ptr<void>,class_std::shared_ptr<class_websocketpp::message_buffer::message<class_websocketpp::message_buffer::alloc::con_msg_manager>_>_>,class_cBZRNetInterfaceHelper*_const,class_std::_Ph<1>&,class_std::_Ph<2>&>,0>,class_std::allocator<class_std::_Func_class<void,class_std::weak_ptr<void>,class_std::shared_ptr<class_websocketpp::message_buffer::message<class_websocketpp::message_buffer::alloc::con_msg_manager>_>_>_>,void,class_std::weak_ptr<void>,class_std::shared_ptr<class_websocketpp::message_buffer::message<class_websocketpp::message_buffer::alloc::con_msg_manager>_>_>
             ::vftable;
  uVar1 = FUN_00417780(param_2 + 4);
  FID_conflict__Callable_obj<class_<lambda_22c800ac295261976027df48869e3267>,0><class_<lambda_22c800ac295261976027df48869e3267>_>
            (uVar1);
  allocator<>(param_2 + 0x10);
  ExceptionList = local_10;
  return param_1;
}

