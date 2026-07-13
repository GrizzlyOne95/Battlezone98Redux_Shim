
void FUN_007e4fa0(undefined4 param_1,undefined4 *param_2,int param_3)

{
  if (param_3 == 4) {
    *param_2 = &boost::spirit::karma::detail::
                generator_binder<struct_boost::spirit::karma::alternative<struct_boost::fusion::cons<struct_boost::spirit::karma::sequence<struct_boost::fusion::cons<struct_boost::spirit::karma::lazy_generator<struct_boost::phoenix::actor<struct_boost::proto::exprns_::basic_expr<struct_boost::phoenix::detail::tag::function_eval,struct_boost::proto::argsns_::list2<struct_boost::spirit::terminal<struct_boost::spirit::tag::eps>,struct_boost::phoenix::actor<struct_boost::spirit::attribute<1>_>_>,2>_>,struct_boost::spirit::unused_type>,struct_boost::fusion::cons<struct_boost::spirit::karma::literal_char<struct_boost::spirit::char_encoding::standard,struct_boost::spirit::unused_type,1>,struct_boost::fusion::nil_>_>_>,struct_boost::fusion::cons<struct_boost::spirit::karma::semantic_predicate,struct_boost::fusion::nil_>_>_>,struct_boost::mpl::bool_<1>_>
                ::RTTI_Type_Descriptor;
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)((int)param_2 + 5) = 0;
  }
  else {
    _Find_unchecked<>(param_1,param_2,param_3,0);
  }
  return;
}

