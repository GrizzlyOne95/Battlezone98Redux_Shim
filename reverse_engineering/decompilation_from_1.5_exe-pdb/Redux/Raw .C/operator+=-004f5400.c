
/* Library Function - Single Match
    public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::iterator & __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::iterator::operator+=(int)
   
   Library: Visual Studio 2003 Debug */

iterator * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::iterator::
operator+=(iterator *this,int param_1)

{
  *(int *)this = *(int *)this + param_1;
  return this;
}

