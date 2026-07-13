
void FUN_008023c0(undefined4 param_1,undefined4 *param_2,int param_3)

{
  if (param_3 == 4) {
    *param_2 = &boost::spirit::qi::detail::
                parser_binder<struct_boost::spirit::qi::lexeme_directive<struct_boost::spirit::qi::expect<struct_boost::fusion::cons<struct_boost::spirit::qi::sequence<struct_boost::fusion::cons<struct_boost::spirit::qi::literal_char<struct_boost::spirit::char_encoding::standard,1,0>,struct_boost::fusion::cons<struct_boost::spirit::qi::kleene<struct_boost::spirit::qi::alternative<struct_boost::fusion::cons<struct_boost::spirit::qi::reference<struct_boost::spirit::qi::symbols<char_const_,char_const_,struct_boost::spirit::qi::tst<char_const_,char_const_>,struct_boost::spirit::qi::tst_pass_through>_>,struct_boost::fusion::cons<struct_boost::spirit::qi::sequence<struct_boost::fusion::cons<struct_boost::spirit::qi::literal_string<char_const_(&)[5],1>,struct_boost::fusion::cons<struct_boost::spirit::qi::any_uint_parser<unsigned_int,16,1,-1>,struct_boost::fusion::nil_>_>_>,struct_boost::fusion::cons<struct_boost::spirit::qi::sequence<struct_boost::fusion::cons<struct_boost::spirit::qi::literal_string<char_const_(&)[3],1>,struct_boost::fusion::cons<struct_boost::spirit::qi::semantic_predicate,struct_boost::fusion::nil_>_>_>,struct_boost::fusion::cons<struct_boost::spirit::qi::difference<struct_boost::spirit::qi::char_class<struct_boost::spirit::tag::char_code<struct_boost::spirit::tag::char_,struct_boost::spirit::char_encoding::standard>_>,struct_boost::spirit::qi::alternative<struct_boost::fusion::cons<struct_boost::spirit::qi::literal_char<struct_boost::spirit::char_encoding::standard,1,0>,struct_boost::fusion::cons<struct_boost::spirit::qi::literal_char<struct_boost::spirit::char_encoding::standard,1,0>,struct_boost::fusion::nil_>_>_>_>,struct_boost::fusion::nil_>_>_>_>_>_>,struct_boost::fusion::nil_>_>_>,struct_boost::fusion::cons<struct_boost::spirit::qi::literal_char<struct_boost::spirit::char_encoding::standard,1,0>,struct_boost::fusion::nil_>_>_>_>,struct_boost::mpl::bool_<0>_>
                ::RTTI_Type_Descriptor;
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)((int)param_2 + 5) = 0;
  }
  else {
    _Find_unchecked<>(param_1,param_2,param_3,0);
  }
  return;
}

