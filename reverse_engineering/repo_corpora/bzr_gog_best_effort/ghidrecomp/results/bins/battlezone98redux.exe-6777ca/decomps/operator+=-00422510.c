
/* Library Function - Single Match
    public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
   & __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::operator+=(char)
   
   Libraries: Visual Studio 2010 Debug, Visual Studio 2010 Release, Visual Studio 2012 Debug, Visual
   Studio 2012 Release */

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          char param_1)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar1;
  
  pbVar1 = append(this,1,param_1);
  return pbVar1;
}

