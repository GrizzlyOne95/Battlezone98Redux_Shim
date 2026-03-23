
void FUN_008032c0(undefined4 param_1,undefined4 *param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863c81;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if ((param_3 == 0) || (param_3 == 1)) {
    iVar2 = forward<>(0xc,param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
    local_8 = 0;
    if (iVar2 != 0) {
      FUN_007fe020(param_1);
    }
  }
  else if (param_3 != 2) {
    if (param_3 == 3) {
      bVar1 = type_info::operator==
                        ((type_info *)*param_2,
                         (type_info *)
                         &boost::spirit::qi::detail::
                          parser_binder<struct_boost::spirit::qi::sequence<struct_boost::fusion::cons<struct_boost::spirit::qi::eps_parser,struct_boost::fusion::cons<struct_boost::spirit::qi::literal_string<char_const_(&)[5],1>,struct_boost::fusion::nil_>_>_>,struct_boost::mpl::bool_<1>_>
                          ::RTTI_Type_Descriptor);
      if (bVar1) {
        *param_2 = param_1;
      }
      else {
        *param_2 = 0;
      }
    }
    else {
      *param_2 = &boost::spirit::qi::detail::
                  parser_binder<struct_boost::spirit::qi::sequence<struct_boost::fusion::cons<struct_boost::spirit::qi::eps_parser,struct_boost::fusion::cons<struct_boost::spirit::qi::literal_string<char_const_(&)[5],1>,struct_boost::fusion::nil_>_>_>,struct_boost::mpl::bool_<1>_>
                  ::RTTI_Type_Descriptor;
      *(undefined1 *)(param_2 + 1) = 0;
      *(undefined1 *)((int)param_2 + 5) = 0;
    }
  }
  ExceptionList = local_10;
  return;
}

