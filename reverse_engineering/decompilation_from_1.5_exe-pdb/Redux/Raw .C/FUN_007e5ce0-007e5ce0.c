
void FUN_007e5ce0(int *param_1,int *param_2,int param_3)

{
  int iVar1;
  bool bVar2;
  void *pvVar3;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863c1c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_3 == 0) {
    iVar1 = *param_1;
    pvVar3 = operator_new(0x7c);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_18 = 0;
    }
    else {
      local_18 = FUN_007dd770(iVar1);
    }
    *param_2 = local_18;
  }
  else if (param_3 == 1) {
    *param_2 = *param_1;
    *param_1 = 0;
  }
  else if (param_3 == 2) {
    if (*param_2 != 0) {
      FUN_007e6170(1);
    }
    *param_2 = 0;
  }
  else if (param_3 == 3) {
    bVar2 = type_info::operator==
                      ((type_info *)*param_2,
                       (type_info *)
                       &boost::spirit::karma::detail::
                        generator_binder<struct_boost::spirit::karma::sequence<struct_boost::fusion::cons<struct_boost::spirit::karma::literal_string<char_const_(&)[2],struct_boost::spirit::unused_type,struct_boost::spirit::unused_type,1>,struct_boost::fusion::cons<struct_boost::spirit::karma::optional<struct_boost::spirit::karma::buffer_directive<struct_boost::spirit::karma::sequence<struct_boost::fusion::cons<struct_boost::spirit::karma::optional<struct_boost::spirit::karma::parameterized_nonterminal<struct_boost::spirit::karma::rule<class_boost::spirit::karma::ostream_iterator<char,char,struct_std::char_traits<char>_>,struct_boost::spirit::unused_type___cdecl(bool,unsigned_int,unsigned_int,bool),struct_boost::spirit::unused_type,struct_boost::spirit::unused_type,struct_boost::spirit::unused_type>,struct_boost::fusion::vector<struct_boost::phoenix::actor<struct_boost::spirit::attribute<1>_>,struct_boost::phoenix::actor<struct_boost::proto::exprns_::basic_expr<struct_boost::proto::tagns_::tag::plus,struct_bo...ruct_boost::spirit::unused_type,1>,struct_boost::fusion::nil_>_>_>_>_>,struct_boost::mpl::bool_<1>_>
                        ::RTTI_Type_Descriptor);
    if (bVar2) {
      *param_2 = *param_1;
    }
    else {
      *param_2 = 0;
    }
  }
  else {
    *param_2 = (int)&boost::spirit::karma::detail::
                     generator_binder<struct_boost::spirit::karma::sequence<struct_boost::fusion::cons<struct_boost::spirit::karma::literal_string<char_const_(&)[2],struct_boost::spirit::unused_type,struct_boost::spirit::unused_type,1>,struct_boost::fusion::cons<struct_boost::spirit::karma::optional<struct_boost::spirit::karma::buffer_directive<struct_boost::spirit::karma::sequence<struct_boost::fusion::cons<struct_boost::spirit::karma::optional<struct_boost::spirit::karma::parameterized_nonterminal<struct_boost::spirit::karma::rule<class_boost::spirit::karma::ostream_iterator<char,char,struct_std::char_traits<char>_>,struct_boost::spirit::unused_type___cdecl(bool,unsigned_int,unsigned_int,bool),struct_boost::spirit::unused_type,struct_boost::spirit::unused_type,struct_boost::spirit::unused_type>,struct_boost::fusion::vector<struct_boost::phoenix::actor<struct_boost::spirit::attribute<1>_>,struct_boost::phoenix::actor<struct_boost::proto::exprns_::basic_expr<struct_boost::proto::tagns_::tag::plus,struct_bo...ruct_boost::spirit::unused_type,1>,struct_boost::fusion::nil_>_>_>_>_>,struct_boost::mpl::bool_<1>_>
                     ::RTTI_Type_Descriptor;
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)((int)param_2 + 5) = 0;
  }
  ExceptionList = local_10;
  return;
}

