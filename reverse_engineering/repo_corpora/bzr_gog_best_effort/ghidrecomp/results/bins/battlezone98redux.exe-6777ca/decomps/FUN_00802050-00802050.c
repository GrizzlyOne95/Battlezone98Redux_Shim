
void FUN_00802050(undefined4 param_1,undefined4 *param_2,int param_3)

{
  if (param_3 == 4) {
    *param_2 = &boost::spirit::qi::detail::
                parser_binder<struct_boost::spirit::qi::sequence<struct_boost::fusion::cons<struct_boost::spirit::qi::eps_parser,struct_boost::fusion::cons<struct_boost::spirit::qi::literal_string<char_const_(&)[5],1>,struct_boost::fusion::nil_>_>_>,struct_boost::mpl::bool_<1>_>
                ::RTTI_Type_Descriptor;
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)((int)param_2 + 5) = 0;
  }
  else {
    _Find_unchecked<>(param_1,param_2,param_3,0);
  }
  return;
}

