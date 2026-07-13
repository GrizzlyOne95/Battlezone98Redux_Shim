
void FUN_007e4e60(undefined4 param_1,undefined4 *param_2,int param_3)

{
  if (param_3 == 4) {
    *param_2 = &boost::spirit::karma::detail::
                generator_binder<struct_boost::spirit::karma::verbatim_generator<struct_boost::spirit::karma::sequence<struct_boost::fusion::cons<struct_boost::spirit::karma::literal_char<struct_boost::spirit::char_encoding::standard,struct_boost::spirit::unused_type,1>,struct_boost::fusion::cons<struct_boost::spirit::karma::reference<struct_boost::spirit::karma::rule<class_boost::spirit::karma::ostream_iterator<char,char,struct_std::char_traits<char>_>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>___cdecl(void),struct_boost::spirit::unused_type,struct_boost::spirit::unused_type,struct_boost::spirit::unused_type>_const_>,struct_boost::fusion::cons<struct_boost::spirit::karma::literal_char<struct_boost::spirit::char_encoding::standard,struct_boost::spirit::unused_type,1>,struct_boost::fusion::nil_>_>_>_>_>,struct_boost::mpl::bool_<1>_>
                ::RTTI_Type_Descriptor;
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)((int)param_2 + 5) = 0;
  }
  else {
    _Find_unchecked<>(param_1,param_2,param_3,0);
  }
  return;
}

