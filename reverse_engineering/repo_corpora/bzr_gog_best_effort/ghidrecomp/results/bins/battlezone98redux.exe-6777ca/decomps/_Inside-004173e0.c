
/* Library Function - Single Match
    public: bool __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::_Inside(char const *)
   
   Library: Visual Studio 2012 Release */

bool __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::_Inside
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          char *param_1)

{
  char *pcVar1;
  
  if (((param_1 != (char *)0x0) &&
      (pcVar1 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                          ((_String_val<struct_std::_Simple_types<char>_> *)this), pcVar1 <= param_1
      )) && (pcVar1 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                                ((_String_val<struct_std::_Simple_types<char>_> *)this),
            param_1 < pcVar1 + *(int *)(this + 0x10))) {
    return true;
  }
  return false;
}

