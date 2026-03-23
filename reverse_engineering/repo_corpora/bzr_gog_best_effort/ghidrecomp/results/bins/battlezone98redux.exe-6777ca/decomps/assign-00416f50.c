
/* Library Function - Single Match
    public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
   & __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::assign(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
   const &,unsigned int,unsigned int)
   
   Library: Visual Studio 2012 Release */

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
          uint param_2,uint param_3)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  uint local_c;
  
  uVar2 = FUN_004170c0();
  if (uVar2 < param_2) {
    FUN_00417440();
  }
  iVar3 = FUN_004170c0();
  local_c = iVar3 - param_2;
  if (param_3 < local_c) {
    local_c = param_3;
  }
  if (this == param_1) {
    erase(this,param_2 + local_c);
    erase(this,0,param_2);
  }
  else {
    bVar1 = _Grow(this,local_c,false);
    if (bVar1) {
      uVar2 = local_c;
      pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)param_1);
      pcVar4 = pcVar4 + param_2;
      pcVar5 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)this);
      char_traits<char>::copy(pcVar5,pcVar4,uVar2);
      basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
                ((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
                  *)this,local_c);
    }
  }
  return this;
}

