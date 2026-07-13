
undefined4 * __thiscall FUN_006e0380(undefined4 *param_1,int param_2)

{
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853d78;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FID_conflict_evaluation_error(param_2);
  local_8 = 0;
  if (param_2 == 0) {
    local_18 = 0;
  }
  else {
    local_18 = param_2 + 0xc;
  }
  FUN_00449f60(local_18);
  *param_1 = boost::exception_detail::error_info_injector<struct_boost::gregorian::bad_month>::
             vftable;
  param_1[3] = boost::exception_detail::error_info_injector<struct_boost::gregorian::bad_month>::
               vftable;
  ExceptionList = local_10;
  return param_1;
}

