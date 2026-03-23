
undefined4 * __thiscall FUN_006df500(undefined4 *param_1,int param_2)

{
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853cd8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0044a1d0(param_2);
  local_8 = 0;
  if (param_2 == 0) {
    local_18 = 0;
  }
  else {
    local_18 = param_2 + 0x2c;
  }
  FUN_00449f60(local_18);
  *param_1 = boost::exception_detail::error_info_injector<class_boost::system::system_error>::
             vftable;
  param_1[0xb] = boost::exception_detail::error_info_injector<class_boost::system::system_error>::
                 vftable;
  ExceptionList = local_10;
  return param_1;
}

