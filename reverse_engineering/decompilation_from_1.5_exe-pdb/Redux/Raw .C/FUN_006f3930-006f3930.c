
bad_cast * __thiscall FUN_006f3930(bad_cast *param_1,bad_cast *param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855489;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::bad_cast::bad_cast(param_1,param_2);
  local_8 = 0;
  boost::exception::exception((exception *)(param_1 + 0xc));
  *(undefined ***)param_1 =
       boost::exception_detail::error_info_injector<class_std::bad_cast>::vftable;
  *(undefined ***)(param_1 + 0xc) =
       boost::exception_detail::error_info_injector<class_std::bad_cast>::vftable;
  ExceptionList = local_10;
  return param_1;
}

