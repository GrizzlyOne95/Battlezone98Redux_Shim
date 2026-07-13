
/* Library Function - Single Match
    public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
   & __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::replace(unsigned int,unsigned int,char const *,unsigned int)
   
   Library: Visual Studio 2012 Release */

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::replace
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          uint param_1,uint param_2,char *param_3,uint param_4)

{
  bool bVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  
  bVar1 = _Inside(this,param_3);
  if (bVar1) {
    pcVar2 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                       ((_String_val<struct_std::_Simple_types<char>_> *)this);
    this = replace(this,param_1,param_2,this,(int)param_3 - (int)pcVar2,param_4);
  }
  else {
    if (*(uint *)(this + 0x10) < param_1) {
      FUN_00417440();
    }
    if (*(int *)(this + 0x10) - param_1 < param_2) {
      param_2 = *(int *)(this + 0x10) - param_1;
    }
    if (-param_4 - 1 <= *(int *)(this + 0x10) - param_2) {
      FUN_00417420();
    }
    iVar3 = (*(int *)(this + 0x10) - param_2) - param_1;
    if (param_4 < param_2) {
      iVar6 = iVar3;
      pcVar2 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)this);
      pcVar2 = pcVar2 + param_2 + param_1;
      pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)this);
      FUN_00416310(pcVar4 + param_4 + param_1,pcVar2,iVar6);
    }
    if ((param_4 != 0) || (param_2 != 0)) {
      uVar5 = (*(int *)(this + 0x10) + param_4) - param_2;
      bVar1 = _Grow(this,uVar5,false);
      if (bVar1) {
        if (param_2 < param_4) {
          pcVar2 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                             ((_String_val<struct_std::_Simple_types<char>_> *)this);
          pcVar2 = pcVar2 + param_2 + param_1;
          pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                             ((_String_val<struct_std::_Simple_types<char>_> *)this);
          FUN_00416310(pcVar4 + param_4 + param_1,pcVar2,iVar3);
        }
        pcVar2 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                           ((_String_val<struct_std::_Simple_types<char>_> *)this);
        char_traits<char>::copy(pcVar2 + param_1,param_3,param_4);
        basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
                  ((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
                    *)this,uVar5);
      }
    }
  }
  return this;
}

