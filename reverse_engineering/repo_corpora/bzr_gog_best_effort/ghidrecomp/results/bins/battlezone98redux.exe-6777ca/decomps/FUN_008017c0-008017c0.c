
bad_alloc * __thiscall FUN_008017c0(bad_alloc *param_1,bad_alloc *param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846128;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::bad_alloc::bad_alloc(param_1,param_2);
  local_8 = 0;
  *(undefined ***)param_1 =
       boost::spirit::qi::
       expectation_failure<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>
       ::vftable;
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);
  *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_2 + 0x10);
  FUN_008018b0(param_2 + 0x14);
  ExceptionList = local_10;
  return param_1;
}

