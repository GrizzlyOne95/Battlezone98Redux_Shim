
/* Library Function - Single Match
    public: void __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::reserve(unsigned int)
   
   Libraries: Visual Studio 2003, Visual Studio 2005, Visual Studio 2008, Visual Studio 2010 */

void __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::reserve
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          uint param_1)

{
  uint uVar1;
  bool bVar2;
  
  if ((*(uint *)(this + 0x10) <= param_1) && (*(uint *)(this + 0x14) != param_1)) {
    uVar1 = *(uint *)(this + 0x10);
    bVar2 = _Grow(this,param_1,true);
    if (bVar2) {
      basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
                ((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
                  *)this,uVar1);
    }
  }
  return;
}

