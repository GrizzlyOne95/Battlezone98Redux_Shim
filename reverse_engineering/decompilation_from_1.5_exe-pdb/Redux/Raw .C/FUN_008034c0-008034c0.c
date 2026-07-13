
void FUN_008034c0(undefined4 param_1,undefined4 *param_2,int param_3)

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
    iVar2 = forward<>(0x10,param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
    local_8 = 0;
    if (iVar2 != 0) {
      FUN_007fe060(param_1);
    }
  }
  else if (param_3 != 2) {
    if (param_3 == 3) {
      bVar1 = type_info::operator==
                        ((type_info *)*param_2,
                         (type_info *)
                         &boost::spirit::qi::detail::
                          parser_binder<struct_boost::spirit::qi::expect<struct_boost::fusion::cons<struct_boost::spirit::qi::lexeme_directive<struct_boost::spirit::qi::reference<struct_boost::spirit::qi::rule<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>___cdecl(void),struct_boost::spirit::unused_type,struct_boost::spirit::unused_type,struct_boost::spirit::unused_type>_const_>_>,struct_boost::fusion::cons<struct_boost::spirit::qi::literal_char<struct_boost::spirit::char_encoding::standard,1,0>,struct_boost::fusion::cons<struct_boost::spirit::qi::reference<struct_boost::spirit::qi::rule<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>,struct_lloyd::json::qi::qi_json_space_skipper<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>,class_boost::variant<struct_boost::detail::variant::recursive_f..._boost::spirit::unused_type>_const_>,struct_boost::fusion::nil_>_>_>_>,struct_boost::mpl::bool_<1>_>
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
                  parser_binder<struct_boost::spirit::qi::expect<struct_boost::fusion::cons<struct_boost::spirit::qi::lexeme_directive<struct_boost::spirit::qi::reference<struct_boost::spirit::qi::rule<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>___cdecl(void),struct_boost::spirit::unused_type,struct_boost::spirit::unused_type,struct_boost::spirit::unused_type>_const_>_>,struct_boost::fusion::cons<struct_boost::spirit::qi::literal_char<struct_boost::spirit::char_encoding::standard,1,0>,struct_boost::fusion::cons<struct_boost::spirit::qi::reference<struct_boost::spirit::qi::rule<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>,struct_lloyd::json::qi::qi_json_space_skipper<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>,class_boost::variant<struct_boost::detail::variant::recursive_f..._boost::spirit::unused_type>_const_>,struct_boost::fusion::nil_>_>_>_>,struct_boost::mpl::bool_<1>_>
                  ::RTTI_Type_Descriptor;
      *(undefined1 *)(param_2 + 1) = 0;
      *(undefined1 *)((int)param_2 + 5) = 0;
    }
  }
  ExceptionList = local_10;
  return;
}

