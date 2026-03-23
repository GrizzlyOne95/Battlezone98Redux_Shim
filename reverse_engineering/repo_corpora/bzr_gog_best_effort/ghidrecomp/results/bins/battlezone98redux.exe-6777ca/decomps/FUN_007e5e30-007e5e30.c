
void FUN_007e5e30(int *param_1,int *param_2,int param_3)

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
    pvVar3 = operator_new(0x2c);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_18 = 0;
    }
    else {
      local_18 = FUN_007dd790(iVar1);
    }
    *param_2 = local_18;
  }
  else if (param_3 == 1) {
    *param_2 = *param_1;
    *param_1 = 0;
  }
  else if (param_3 == 2) {
    if (*param_2 != 0) {
      FUN_007e61a0(1);
    }
    *param_2 = 0;
  }
  else if (param_3 == 3) {
    bVar2 = type_info::operator==
                      ((type_info *)*param_2,
                       (type_info *)
                       &boost::spirit::karma::detail::
                        generator_binder<struct_boost::spirit::karma::alternative<struct_boost::fusion::cons<struct_boost::spirit::karma::reference<struct_boost::spirit::karma::symbols<char,char_const*,class_std::map<char,char_const*,struct_std::less<char>,class_std::allocator<struct_std::pair<char_const_,char_const*>_>_>,struct_boost::spirit::unused_type,struct_boost::spirit::unused_type>_>,struct_boost::fusion::cons<struct_boost::spirit::karma::char_class<struct_boost::spirit::tag::char_code<struct_boost::spirit::tag::print,struct_boost::spirit::char_encoding::standard>,struct_boost::spirit::char_encoding::standard,struct_boost::spirit::unused_type>,struct_boost::fusion::cons<struct_boost::spirit::karma::char_class<struct_boost::spirit::tag::char_code<struct_boost::spirit::tag::blank,struct_boost::spirit::char_encoding::standard>,struct_boost::spirit::char_encoding::standard,struct_boost::spirit::unused_type>,struct_boost::fusion::cons<struct_boost::spirit::karma::sequence<struct_boost::fusion::cons<struct_boost::spirit::karma::literal_string<char_const_(&)[5],struct_boost::spirit::unused_type,struct_boost::spirit::unused_type,1>,struct_boost::fusion::cons<struct_boost::spirit::karma::any_uint_generator<unsigned_int,struct_boost::spirit::unused_type,struct_boost::spirit::unused_type,16>,struct_boost::fusion::nil_>_>_>,struct_boost::fusion::nil_>_>_>_>_>,struct_boost::mpl::bool_<1>_>
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
                     generator_binder<struct_boost::spirit::karma::alternative<struct_boost::fusion::cons<struct_boost::spirit::karma::reference<struct_boost::spirit::karma::symbols<char,char_const*,class_std::map<char,char_const*,struct_std::less<char>,class_std::allocator<struct_std::pair<char_const_,char_const*>_>_>,struct_boost::spirit::unused_type,struct_boost::spirit::unused_type>_>,struct_boost::fusion::cons<struct_boost::spirit::karma::char_class<struct_boost::spirit::tag::char_code<struct_boost::spirit::tag::print,struct_boost::spirit::char_encoding::standard>,struct_boost::spirit::char_encoding::standard,struct_boost::spirit::unused_type>,struct_boost::fusion::cons<struct_boost::spirit::karma::char_class<struct_boost::spirit::tag::char_code<struct_boost::spirit::tag::blank,struct_boost::spirit::char_encoding::standard>,struct_boost::spirit::char_encoding::standard,struct_boost::spirit::unused_type>,struct_boost::fusion::cons<struct_boost::spirit::karma::sequence<struct_boost::fusion::cons<struct_boost::spirit::karma::literal_string<char_const_(&)[5],struct_boost::spirit::unused_type,struct_boost::spirit::unused_type,1>,struct_boost::fusion::cons<struct_boost::spirit::karma::any_uint_generator<unsigned_int,struct_boost::spirit::unused_type,struct_boost::spirit::unused_type,16>,struct_boost::fusion::nil_>_>_>,struct_boost::fusion::nil_>_>_>_>_>,struct_boost::mpl::bool_<1>_>
                     ::RTTI_Type_Descriptor;
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)((int)param_2 + 5) = 0;
  }
  ExceptionList = local_10;
  return;
}

