
undefined4 * __thiscall FUN_00801730(undefined4 *param_1,int param_2)

{
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008647b8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_008017c0(param_2);
  local_8 = 0;
  if (param_2 == 0) {
    local_18 = 0;
  }
  else {
    local_18 = param_2 + 0x48;
  }
  FUN_00449f60(local_18);
  *param_1 = boost::exception_detail::
             error_info_injector<struct_boost::spirit::qi::expectation_failure<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>_>
             ::vftable;
  param_1[0x12] =
       boost::exception_detail::
       error_info_injector<struct_boost::spirit::qi::expectation_failure<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>_>
       ::vftable;
  ExceptionList = local_10;
  return param_1;
}

