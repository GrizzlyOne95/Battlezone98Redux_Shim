
/* Library Function - Single Match
    public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
   & __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::assign(unsigned int,char)
   
   Library: Visual Studio 2012 Release */

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          uint param_1,char param_2)

{
  bool bVar1;
  
  if (param_1 == 0xffffffff) {
    FUN_00417420();
  }
  bVar1 = _Grow(this,param_1,false);
  if (bVar1) {
    _Chassign(this,0,param_1,param_2);
    basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
              ((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
                *)this,param_1);
  }
  return this;
}

