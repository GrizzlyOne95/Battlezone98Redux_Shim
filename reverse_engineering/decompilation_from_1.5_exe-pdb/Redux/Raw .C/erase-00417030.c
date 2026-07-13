
/* Library Function - Single Match
    public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
   & __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::erase(unsigned int,unsigned int)
   
   Library: Visual Studio 2012 Release */

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          uint param_1,uint param_2)

{
  int iVar1;
  char *pcVar2;
  
  if (*(uint *)(this + 0x10) < param_1) {
    FUN_00417440();
  }
  if (param_2 < *(int *)(this + 0x10) - param_1) {
    if (param_2 != 0) {
      pcVar2 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)this);
      iVar1 = *(int *)(this + 0x10);
      FUN_00416310(pcVar2 + param_1,pcVar2 + param_1 + param_2,(iVar1 - param_2) - param_1);
      basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
                ((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
                  *)this,iVar1 - param_2);
    }
  }
  else {
    basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
              ((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
                *)this,param_1);
  }
  return this;
}

