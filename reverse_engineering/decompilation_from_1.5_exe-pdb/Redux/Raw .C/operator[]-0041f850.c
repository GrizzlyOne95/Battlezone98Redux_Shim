
/* Library Function - Single Match
    public: char const & __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::operator[](unsigned int)const 
   
   Library: Visual Studio 2012 Release */

char * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator[]
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          uint param_1)

{
  char *pcVar1;
  
  pcVar1 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                     ((_String_val<struct_std::_Simple_types<char>_> *)this);
  return pcVar1 + param_1;
}

