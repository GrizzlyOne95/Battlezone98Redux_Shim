
_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_> * __fastcall
FUN_006c8830(_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>
             *param_1)

{
  char cVar1;
  allocator<char> *paVar2;
  uint uVar3;
  char *pcVar4;
  allocator<char> local_5;
  
  paVar2 = (allocator<char> *)std::allocator<char>::allocator<char>(&local_5);
  std::_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>::
  _String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>(param_1,paVar2)
  ;
  FID_conflict__Tidy(0,0);
  cVar1 = FID_conflict_operator__(&stack0x00000008);
  if (cVar1 != '\0') {
    uVar3 = std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
            operator-((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                       *)&stack0x00000008,
                      (_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                       *)&stack0x00000004);
    pcVar4 = (char *)get();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               param_1,pcVar4,uVar3);
  }
  return param_1;
}

