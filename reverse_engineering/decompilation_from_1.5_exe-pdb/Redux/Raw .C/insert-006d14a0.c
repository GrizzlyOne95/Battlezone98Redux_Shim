
/* Library Function - Single Match
    public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
   & __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::insert(unsigned int,unsigned int,char)
   
   Library: Visual Studio 2012 Release */

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::insert
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          uint param_1,uint param_2,char param_3)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  
  if (*(uint *)(this + 0x10) < param_1) {
    FUN_00417440();
  }
  if (-*(int *)(this + 0x10) - 1U <= param_2) {
    FUN_00417420();
  }
  if (param_2 != 0) {
    iVar1 = *(int *)(this + 0x10);
    bVar2 = _Grow(this,iVar1 + param_2,false);
    if (bVar2) {
      iVar3 = *(int *)(this + 0x10) - param_1;
      pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)this);
      pcVar4 = pcVar4 + param_1;
      pcVar5 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)this);
      FUN_00416310(pcVar5 + param_2 + param_1,pcVar4,iVar3);
      _Chassign(this,param_1,param_2,param_3);
      basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
                ((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
                  *)this,iVar1 + param_2);
    }
  }
  return this;
}

