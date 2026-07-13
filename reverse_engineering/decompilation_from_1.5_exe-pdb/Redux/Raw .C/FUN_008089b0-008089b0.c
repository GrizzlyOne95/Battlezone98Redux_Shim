
undefined4 * __thiscall
FUN_008089b0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846128;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00448470("boost::spirit::qi::expectation_failure");
  local_8 = 0;
  *param_1 = boost::spirit::qi::
             expectation_failure<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>
             ::vftable;
  param_1[3] = param_2;
  param_1[4] = param_3;
  FUN_008018b0(param_4);
  ExceptionList = local_10;
  return param_1;
}

