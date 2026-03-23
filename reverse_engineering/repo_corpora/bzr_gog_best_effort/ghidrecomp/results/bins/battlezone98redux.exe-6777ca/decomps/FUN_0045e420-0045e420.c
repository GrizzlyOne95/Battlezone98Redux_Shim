
_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_> * __thiscall
FUN_0045e420(_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>
             *param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
            uint param_3,uint param_4,allocator<char> *param_5)

{
  std::_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>::
  _String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>
            (param_1,param_5);
  FID_conflict__Tidy(0,0);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)param_1
             ,param_2,param_3,param_4);
  return param_1;
}

