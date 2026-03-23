
undefined4 * __thiscall FUN_006dfd50(undefined4 *param_1,int param_2,int param_3)

{
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853d1c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_3 != 0) {
    param_1[8] = &DAT_00896618;
    if (param_2 == 0) {
      local_18 = 0;
    }
    else {
      local_18 = param_2 + 0x20 + *(int *)(*(int *)(param_2 + 0x20) + 4);
    }
    FUN_00449fb0(local_18);
    local_8 = 0;
  }
  FUN_006dfe40(param_2);
  *param_1 = boost::exception_detail::
             clone_impl<struct_boost::exception_detail::error_info_injector<class_std::length_error>_>
             ::vftable;
  param_1[3] = boost::exception_detail::
               clone_impl<struct_boost::exception_detail::error_info_injector<class_std::length_error>_>
               ::vftable;
  *(undefined ***)((int)param_1 + *(int *)(param_1[8] + 4) + 0x20) =
       boost::exception_detail::
       clone_impl<struct_boost::exception_detail::error_info_injector<class_std::length_error>_>::
       vftable;
  *(undefined4 *)((int)param_1 + *(int *)(param_1[8] + 4) + 0x1c) = 0;
  ExceptionList = local_10;
  return param_1;
}

