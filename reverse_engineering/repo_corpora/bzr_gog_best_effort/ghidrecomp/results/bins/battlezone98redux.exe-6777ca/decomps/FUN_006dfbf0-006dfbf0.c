
bad_cast * __thiscall FUN_006dfbf0(bad_cast *param_1,bad_cast *param_2)

{
  bad_cast *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853dd9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::bad_cast::bad_cast(param_1,param_2);
  local_8 = 0;
  if (param_2 == (bad_cast *)0x0) {
    local_18 = (bad_cast *)0x0;
  }
  else {
    local_18 = param_2 + 0xc;
  }
  FUN_00449f60(local_18);
  *(undefined ***)param_1 =
       boost::exception_detail::error_info_injector<class_std::bad_cast>::vftable;
  *(undefined ***)(param_1 + 0xc) =
       boost::exception_detail::error_info_injector<class_std::bad_cast>::vftable;
  ExceptionList = local_10;
  return param_1;
}

