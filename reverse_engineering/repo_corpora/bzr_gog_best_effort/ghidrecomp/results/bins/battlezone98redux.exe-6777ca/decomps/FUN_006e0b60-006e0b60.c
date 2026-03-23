
_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_> * __thiscall
FUN_006e0b60(_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>
             *param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
            uint param_3,uint param_4)

{
  allocator<char> *paVar1;
  undefined1 local_5;
  
  paVar1 = (allocator<char> *)Getal(&local_5);
  std::_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>::
  _String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>(param_1,paVar1)
  ;
  FID_conflict__Tidy(0,0);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)param_1
             ,param_2,param_3,param_4);
  return param_1;
}

