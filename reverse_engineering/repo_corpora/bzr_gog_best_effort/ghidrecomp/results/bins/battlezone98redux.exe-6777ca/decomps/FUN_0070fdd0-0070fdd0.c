
bad_alloc * __thiscall FUN_0070fdd0(bad_alloc *param_1,bad_alloc *param_2)

{
  bad_alloc *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853d48;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::bad_alloc::bad_alloc(param_1,param_2);
  local_8 = 0;
  if (param_2 == (bad_alloc *)0x0) {
    local_18 = (bad_alloc *)0x0;
  }
  else {
    local_18 = param_2 + 0xc;
  }
  FUN_00449f60(local_18);
  *(undefined ***)param_1 =
       boost::exception_detail::error_info_injector<class_boost::bad_get>::vftable;
  *(undefined ***)(param_1 + 0xc) =
       boost::exception_detail::error_info_injector<class_boost::bad_get>::vftable;
  ExceptionList = local_10;
  return param_1;
}

