
/* Library Function - Single Match
    public: static unsigned int __cdecl std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::_Pdif(class std::_String_const_iterator<class std::_String_val<struct
   std::_Simple_types<char> > >,class std::_String_const_iterator<class std::_String_val<struct
   std::_Simple_types<char> > >)
   
   Library: Visual Studio 2012 Release */

uint __cdecl
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::_Pdif
          (int param_1)

{
  uint local_8;
  
  if (param_1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
              operator-((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                         *)&param_1,
                        (_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                         *)&stack0x00000008);
  }
  return local_8;
}

