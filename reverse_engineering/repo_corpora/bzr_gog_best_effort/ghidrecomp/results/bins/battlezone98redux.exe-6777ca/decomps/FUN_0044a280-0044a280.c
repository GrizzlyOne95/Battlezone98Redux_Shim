
undefined4 * __thiscall FUN_0044a280(undefined4 *param_1,int param_2,int param_3)

{
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084638c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_3 != 0) {
    param_1[0x10] = &DAT_008749c8;
    if (param_2 == 0) {
      local_18 = 0;
    }
    else {
      local_18 = param_2 + 0x40 + *(int *)(*(int *)(param_2 + 0x40) + 4);
    }
    FUN_00449fb0(local_18);
    local_8 = 0;
  }
  FUN_0044a370(param_2);
  *param_1 = boost::exception_detail::
             clone_impl<struct_boost::exception_detail::error_info_injector<class_boost::lock_error>_>
             ::vftable;
  param_1[0xb] = boost::exception_detail::
                 clone_impl<struct_boost::exception_detail::error_info_injector<class_boost::lock_error>_>
                 ::vftable;
  *(undefined ***)((int)param_1 + *(int *)(param_1[0x10] + 4) + 0x40) =
       boost::exception_detail::
       clone_impl<struct_boost::exception_detail::error_info_injector<class_boost::lock_error>_>::
       vftable;
  *(undefined4 *)((int)param_1 + *(int *)(param_1[0x10] + 4) + 0x3c) = 0;
  ExceptionList = local_10;
  return param_1;
}

