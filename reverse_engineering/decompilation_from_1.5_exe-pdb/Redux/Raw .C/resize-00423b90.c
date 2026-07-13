
/* Library Function - Single Match
    public: void __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::resize(unsigned int,char)
   
   Library: Visual Studio 2012 Release */

void __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::resize
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          uint param_1,char param_2)

{
  if (*(uint *)(this + 0x10) < param_1) {
    append(this,param_1 - *(int *)(this + 0x10),param_2);
  }
  else {
    basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
              ((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
                *)this,param_1);
  }
  return;
}

