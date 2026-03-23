
undefined4 * __thiscall FUN_007130d0(undefined4 *param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857ba8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00712780(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = std::
             _Func_impl<struct_std::_Callable_obj<class_std::_Bind<1,void,struct_std::_Pmf_wrap<void_(__thiscall_cBZRNetInterfaceHelper::*)(class_std::weak_ptr<void>),void,class_cBZRNetInterfaceHelper,class_std::weak_ptr<void>_>,class_cBZRNetInterfaceHelper*_const,class_std::_Ph<1>&>,0>,class_std::allocator<class_std::_Func_class<void,class_std::weak_ptr<void>_>_>,void,class_std::weak_ptr<void>_>
             ::vftable;
  FID_conflict__Callable_obj<class_<lambda_22c800ac295261976027df48869e3267>,0><class_<lambda_22c800ac295261976027df48869e3267>_>
            (param_2 + 4);
  allocator<>(param_2 + 0x10);
  ExceptionList = local_10;
  return param_1;
}

