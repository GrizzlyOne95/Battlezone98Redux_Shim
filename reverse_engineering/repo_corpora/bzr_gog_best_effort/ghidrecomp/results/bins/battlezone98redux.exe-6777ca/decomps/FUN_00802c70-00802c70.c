
void FUN_00802c70(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  undefined4 uVar1;
  bool bVar2;
  void *pvVar3;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863c4c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_3 == 0) {
    uVar1 = *param_1;
    pvVar3 = operator_new(0x20);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_18 = 0;
    }
    else {
      local_18 = FUN_007fe000(uVar1);
    }
    *param_2 = local_18;
  }
  else if (param_3 == 1) {
    *param_2 = *param_1;
    *param_1 = 0;
  }
  else if (param_3 == 2) {
    operator_delete((void *)*param_2);
    *param_2 = 0;
  }
  else if (param_3 == 3) {
    bVar2 = type_info::operator==
                      ((type_info *)*param_2,
                       (type_info *)
                       &boost::spirit::qi::detail::
                        parser_binder<struct_boost::spirit::qi::alternative<struct_boost::fusion::cons<struct_boost::spirit::qi::char_class<struct_boost::spirit::tag::char_code<struct_boost::spirit::tag::space,struct_boost::spirit::char_encoding::ascii>_>,struct_boost::fusion::cons<struct_boost::spirit::qi::expect<struct_boost::fusion::cons<struct_boost::spirit::qi::literal_string<char_const_(&)[3],1>,struct_boost::fusion::cons<struct_boost::spirit::qi::kleene<struct_boost::spirit::qi::difference<struct_boost::spirit::qi::char_class<struct_boost::spirit::tag::char_code<struct_boost::spirit::tag::char_,struct_boost::spirit::char_encoding::standard>_>,struct_boost::spirit::qi::eol_parser>_>,struct_boost::fusion::cons<struct_boost::spirit::qi::eol_parser,struct_boost::fusion::nil_>_>_>_>,struct_boost::fusion::cons<struct_boost::spirit::qi::expect<struct_boost::fusion::cons<struct_boost::spirit::qi::literal_string<char_const_(&)[3],1>,struct_boost::fusion::cons<struct_boost::spirit::qi::kleene<struct_boost::spirit::qi::difference<struct_boost::spirit::qi::char_class<struct_boost::spirit::tag::char_code<struct_boost::spirit::tag::char_,struct_boost::spirit::char_encoding::standard>_>,struct_boost::spirit::qi::literal_string<char_const_(&)[3],1>_>_>,struct_boost::fusion::nil_>_>_>,struct_boost::fusion::nil_>_>_>_>,struct_boost::mpl::bool_<1>_>
                        ::RTTI_Type_Descriptor);
    if (bVar2) {
      *param_2 = *param_1;
    }
    else {
      *param_2 = 0;
    }
  }
  else {
    *param_2 = &boost::spirit::qi::detail::
                parser_binder<struct_boost::spirit::qi::alternative<struct_boost::fusion::cons<struct_boost::spirit::qi::char_class<struct_boost::spirit::tag::char_code<struct_boost::spirit::tag::space,struct_boost::spirit::char_encoding::ascii>_>,struct_boost::fusion::cons<struct_boost::spirit::qi::expect<struct_boost::fusion::cons<struct_boost::spirit::qi::literal_string<char_const_(&)[3],1>,struct_boost::fusion::cons<struct_boost::spirit::qi::kleene<struct_boost::spirit::qi::difference<struct_boost::spirit::qi::char_class<struct_boost::spirit::tag::char_code<struct_boost::spirit::tag::char_,struct_boost::spirit::char_encoding::standard>_>,struct_boost::spirit::qi::eol_parser>_>,struct_boost::fusion::cons<struct_boost::spirit::qi::eol_parser,struct_boost::fusion::nil_>_>_>_>,struct_boost::fusion::cons<struct_boost::spirit::qi::expect<struct_boost::fusion::cons<struct_boost::spirit::qi::literal_string<char_const_(&)[3],1>,struct_boost::fusion::cons<struct_boost::spirit::qi::kleene<struct_boost::spirit::qi::difference<struct_boost::spirit::qi::char_class<struct_boost::spirit::tag::char_code<struct_boost::spirit::tag::char_,struct_boost::spirit::char_encoding::standard>_>,struct_boost::spirit::qi::literal_string<char_const_(&)[3],1>_>_>,struct_boost::fusion::nil_>_>_>,struct_boost::fusion::nil_>_>_>_>,struct_boost::mpl::bool_<1>_>
                ::RTTI_Type_Descriptor;
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)((int)param_2 + 5) = 0;
  }
  ExceptionList = local_10;
  return;
}

