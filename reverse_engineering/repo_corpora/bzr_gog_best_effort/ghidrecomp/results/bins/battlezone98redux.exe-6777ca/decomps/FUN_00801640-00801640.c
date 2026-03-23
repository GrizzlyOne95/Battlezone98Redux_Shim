
undefined4 * __thiscall FUN_00801640(undefined4 *param_1,int param_2,int param_3)

{
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0086478c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_3 != 0) {
    param_1[0x17] = &DAT_008a1c54;
    if (param_2 == 0) {
      local_18 = 0;
    }
    else {
      local_18 = param_2 + 0x5c + *(int *)(*(int *)(param_2 + 0x5c) + 4);
    }
    FUN_00449fb0(local_18);
    local_8 = 0;
  }
  FUN_00801730(param_2);
  *param_1 = boost::exception_detail::
             clone_impl<struct_boost::exception_detail::error_info_injector<struct_boost::spirit::qi::expectation_failure<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>_>_>
             ::vftable;
  param_1[0x12] =
       boost::exception_detail::
       clone_impl<struct_boost::exception_detail::error_info_injector<struct_boost::spirit::qi::expectation_failure<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>_>_>
       ::vftable;
  *(undefined ***)((int)param_1 + *(int *)(param_1[0x17] + 4) + 0x5c) =
       boost::exception_detail::
       clone_impl<struct_boost::exception_detail::error_info_injector<struct_boost::spirit::qi::expectation_failure<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>_>_>
       ::vftable;
  *(undefined4 *)((int)param_1 + *(int *)(param_1[0x17] + 4) + 0x58) = 0;
  ExceptionList = local_10;
  return param_1;
}

