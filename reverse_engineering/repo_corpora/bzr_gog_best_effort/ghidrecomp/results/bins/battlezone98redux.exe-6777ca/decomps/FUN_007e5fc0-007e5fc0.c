
void FUN_007e5fc0(undefined4 *param_1,undefined4 *param_2,int param_3)

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
    pvVar3 = operator_new(0x38);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_18 = 0;
    }
    else {
      local_18 = FUN_007dd810(uVar1);
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
                       &boost::spirit::karma::detail::
                        generator_binder<struct_boost::spirit::karma::alternative<struct_boost::fusion::cons<struct_boost::spirit::karma::sequence<struct_boost::fusion::cons<struct_boost::spirit::karma::lazy_generator<struct_boost::phoenix::actor<struct_boost::proto::exprns_::basic_expr<struct_boost::phoenix::detail::tag::function_eval,struct_boost::proto::argsns_::list2<struct_boost::spirit::terminal<struct_boost::spirit::tag::eps>,struct_boost::phoenix::actor<struct_boost::spirit::attribute<1>_>_>,2>_>,struct_boost::spirit::unused_type>,struct_boost::fusion::cons<struct_boost::spirit::karma::eol_generator,struct_boost::fusion::cons<struct_boost::spirit::karma::alternative<struct_boost::fusion::cons<struct_boost::spirit::karma::sequence<struct_boost::fusion::cons<struct_boost::spirit::karma::lazy_generator<struct_boost::phoenix::actor<struct_boost::proto::exprns_::basic_expr<struct_boost::phoenix::detail::tag::function_eval,struct_boost::proto::argsns_::list2<struct_boost::spirit::terminal<struct_boost::spir...t::spirit::karma::semantic_predicate,struct_boost::fusion::nil_>_>_>_>,struct_boost::mpl::bool_<1>_>
                        ::RTTI_Type_Descriptor);
    if (bVar2) {
      *param_2 = *param_1;
    }
    else {
      *param_2 = 0;
    }
  }
  else {
    *param_2 = &boost::spirit::karma::detail::
                generator_binder<struct_boost::spirit::karma::alternative<struct_boost::fusion::cons<struct_boost::spirit::karma::sequence<struct_boost::fusion::cons<struct_boost::spirit::karma::lazy_generator<struct_boost::phoenix::actor<struct_boost::proto::exprns_::basic_expr<struct_boost::phoenix::detail::tag::function_eval,struct_boost::proto::argsns_::list2<struct_boost::spirit::terminal<struct_boost::spirit::tag::eps>,struct_boost::phoenix::actor<struct_boost::spirit::attribute<1>_>_>,2>_>,struct_boost::spirit::unused_type>,struct_boost::fusion::cons<struct_boost::spirit::karma::eol_generator,struct_boost::fusion::cons<struct_boost::spirit::karma::alternative<struct_boost::fusion::cons<struct_boost::spirit::karma::sequence<struct_boost::fusion::cons<struct_boost::spirit::karma::lazy_generator<struct_boost::phoenix::actor<struct_boost::proto::exprns_::basic_expr<struct_boost::phoenix::detail::tag::function_eval,struct_boost::proto::argsns_::list2<struct_boost::spirit::terminal<struct_boost::spir...t::spirit::karma::semantic_predicate,struct_boost::fusion::nil_>_>_>_>,struct_boost::mpl::bool_<1>_>
                ::RTTI_Type_Descriptor;
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)((int)param_2 + 5) = 0;
  }
  ExceptionList = local_10;
  return;
}

