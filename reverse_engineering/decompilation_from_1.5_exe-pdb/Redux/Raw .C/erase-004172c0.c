
/* Library Function - Single Match
    public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
   & __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::erase(unsigned int)
   
   Library: Visual Studio 2012 Release */

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          uint param_1)

{
  if (*(uint *)(this + 0x10) < param_1) {
    FUN_00417440();
  }
  basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
            ((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
              *)this,param_1);
  return this;
}

