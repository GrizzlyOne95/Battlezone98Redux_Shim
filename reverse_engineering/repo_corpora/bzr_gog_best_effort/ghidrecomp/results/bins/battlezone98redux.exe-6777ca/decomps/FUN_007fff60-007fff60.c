
void FUN_007fff60(int *param_1,int *param_2,int param_3)

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
    pvVar3 = operator_new(0x38);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_18 = 0;
    }
    else {
      local_18 = FUN_007fc680(iVar1);
    }
    *param_2 = local_18;
  }
  else if (param_3 == 1) {
    *param_2 = *param_1;
    *param_1 = 0;
  }
  else if (param_3 == 2) {
    if (*param_2 != 0) {
      FUN_00800110(1);
    }
    *param_2 = 0;
  }
  else if (param_3 == 3) {
    bVar2 = type_info::operator==
                      ((type_info *)*param_2,
                       (type_info *)
                       &boost::spirit::qi::
                        error_handler<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>,struct_boost::spirit::context<struct_boost::fusion::cons<class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_b...st::spirit::argument<1>_>,struct_boost::phoenix::actor<struct_boost::spirit::argument<2>_>_>,4>_>,0>
                        ::RTTI_Type_Descriptor);
    if (bVar2) {
      *param_2 = *param_1;
    }
    else {
      *param_2 = 0;
    }
  }
  else {
    *param_2 = (int)&boost::spirit::qi::
                     error_handler<class_std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>,struct_boost::spirit::context<struct_boost::fusion::cons<class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::variant<struct_boost::detail::variant::recursive_flag<struct_lloyd::json::null>,bool,long,double,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,class_boost::container::map<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>,struct_boost::recursive_variant_,struct_std::less<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>,class_boost::container::new_allocator<struct_std::pair<class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const_,struct_boost::recursive_variant_>_>,struct_boost::container::tree_opt<0,1>_>,class_boost::container::vector<struct_b...st::spirit::argument<1>_>,struct_boost::phoenix::actor<struct_boost::spirit::argument<2>_>_>,4>_>,0>
                     ::RTTI_Type_Descriptor;
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)((int)param_2 + 5) = 0;
  }
  ExceptionList = local_10;
  return;
}

