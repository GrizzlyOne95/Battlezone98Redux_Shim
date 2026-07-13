
/* Library Function - Single Match
    public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
   & __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::append(unsigned int,char)
   
   Library: Visual Studio 2012 Release */

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          uint param_1,char param_2)

{
  int iVar1;
  bool bVar2;
  
  if (-*(int *)(this + 0x10) - 1U <= param_1) {
    FUN_00417420();
  }
  if (param_1 != 0) {
    iVar1 = *(int *)(this + 0x10);
    bVar2 = _Grow(this,iVar1 + param_1,false);
    if (bVar2) {
      _Chassign(this,*(uint *)(this + 0x10),param_1,param_2);
      basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
                ((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
                  *)this,iVar1 + param_1);
    }
  }
  return this;
}

