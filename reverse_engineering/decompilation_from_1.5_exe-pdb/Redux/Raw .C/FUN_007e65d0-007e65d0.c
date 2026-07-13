
void FUN_007e65d0(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  bool bVar1;
  undefined4 *puVar2;
  
  if ((param_3 == 0) || (param_3 == 1)) {
    puVar2 = (undefined4 *)forward<>(4,param_2);
    if (puVar2 != (undefined4 *)0x0) {
      *puVar2 = *param_1;
    }
  }
  else if (param_3 != 2) {
    if (param_3 == 3) {
      bVar1 = type_info::operator==
                        ((type_info *)*param_2,
                         (type_info *)
                         &boost::spirit::karma::detail::
                          generator_binder<struct_boost::spirit::karma::kleene<struct_boost::spirit::karma::reference<struct_boost::spirit::karma::rule<class_boost::spirit::karma::ostream_iterator<char,char,struct_std::char_traits<char>_>,char_const___cdecl(void),struct_boost::spirit::unused_type,struct_boost::spirit::unused_type,struct_boost::spirit::unused_type>_const_>_>,struct_boost::mpl::bool_<0>_>
                          ::RTTI_Type_Descriptor);
      if (bVar1) {
        *param_2 = param_1;
      }
      else {
        *param_2 = 0;
      }
    }
    else {
      *param_2 = &boost::spirit::karma::detail::
                  generator_binder<struct_boost::spirit::karma::kleene<struct_boost::spirit::karma::reference<struct_boost::spirit::karma::rule<class_boost::spirit::karma::ostream_iterator<char,char,struct_std::char_traits<char>_>,char_const___cdecl(void),struct_boost::spirit::unused_type,struct_boost::spirit::unused_type,struct_boost::spirit::unused_type>_const_>_>,struct_boost::mpl::bool_<0>_>
                  ::RTTI_Type_Descriptor;
      *(undefined1 *)(param_2 + 1) = 0;
      *(undefined1 *)((int)param_2 + 5) = 0;
    }
  }
  return;
}

