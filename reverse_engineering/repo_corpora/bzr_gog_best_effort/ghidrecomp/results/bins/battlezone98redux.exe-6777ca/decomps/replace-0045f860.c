
/* Library Function - Single Match
    public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
   & __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::replace(unsigned int,unsigned int,class std::basic_string<char,struct
   std::char_traits<char>,class std::allocator<char> > const &,unsigned int,unsigned int)
   
   Library: Visual Studio 2012 Release */

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::replace
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          uint param_1,uint param_2,
          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_3,
          uint param_4,uint param_5)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  uint uVar5;
  
  if (param_1 <= *(uint *)(this + 0x10)) {
    uVar1 = FUN_004170c0();
    if (param_4 <= uVar1) goto LAB_0045f889;
  }
  FUN_00417440();
LAB_0045f889:
  if (*(int *)(this + 0x10) - param_1 < param_2) {
    param_2 = *(int *)(this + 0x10) - param_1;
  }
  iVar2 = FUN_004170c0();
  if (iVar2 - param_4 < param_5) {
    param_5 = iVar2 - param_4;
  }
  if (-param_5 - 1 <= *(int *)(this + 0x10) - param_2) {
    FUN_00417420();
  }
  iVar2 = (*(int *)(this + 0x10) - param_2) - param_1;
  uVar1 = (*(int *)(this + 0x10) + param_5) - param_2;
  if (*(uint *)(this + 0x10) < uVar1) {
    _Grow(this,uVar1,false);
  }
  if (this == param_3) {
    if (param_2 < param_5) {
      if (param_1 < param_4) {
        if (param_4 < param_1 + param_2) {
          uVar5 = param_2;
          pcVar3 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                             ((_String_val<struct_std::_Simple_types<char>_> *)this);
          pcVar3 = pcVar3 + param_4;
          pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                             ((_String_val<struct_std::_Simple_types<char>_> *)this);
          FUN_00416310(pcVar4 + param_1,pcVar3,uVar5);
          pcVar3 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                             ((_String_val<struct_std::_Simple_types<char>_> *)this);
          pcVar3 = pcVar3 + param_2 + param_1;
          pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                             ((_String_val<struct_std::_Simple_types<char>_> *)this);
          FUN_00416310(pcVar4 + param_5 + param_1,pcVar3,iVar2);
          iVar2 = param_5 - param_2;
          pcVar3 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                             ((_String_val<struct_std::_Simple_types<char>_> *)this);
          pcVar3 = pcVar3 + param_5 + param_4;
          pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                             ((_String_val<struct_std::_Simple_types<char>_> *)this);
          FUN_00416310(pcVar4 + param_2 + param_1,pcVar3,iVar2);
        }
        else {
          pcVar3 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                             ((_String_val<struct_std::_Simple_types<char>_> *)this);
          pcVar3 = pcVar3 + param_2 + param_1;
          pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                             ((_String_val<struct_std::_Simple_types<char>_> *)this);
          FUN_00416310(pcVar4 + param_5 + param_1,pcVar3,iVar2);
          uVar5 = param_5;
          pcVar3 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                             ((_String_val<struct_std::_Simple_types<char>_> *)this);
          pcVar3 = pcVar3 + ((param_4 + param_5) - param_2);
          pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                             ((_String_val<struct_std::_Simple_types<char>_> *)this);
          FUN_00416310(pcVar4 + param_1,pcVar3,uVar5);
        }
      }
      else {
        pcVar3 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                           ((_String_val<struct_std::_Simple_types<char>_> *)this);
        pcVar3 = pcVar3 + param_2 + param_1;
        pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                           ((_String_val<struct_std::_Simple_types<char>_> *)this);
        FUN_00416310(pcVar4 + param_5 + param_1,pcVar3,iVar2);
        pcVar3 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                           ((_String_val<struct_std::_Simple_types<char>_> *)this);
        pcVar3 = pcVar3 + param_4;
        pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                           ((_String_val<struct_std::_Simple_types<char>_> *)this);
        FUN_00416310(pcVar4 + param_1,pcVar3,param_5);
      }
    }
    else {
      uVar5 = param_5;
      pcVar3 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)this);
      pcVar3 = pcVar3 + param_4;
      pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)this);
      FUN_00416310(pcVar4 + param_1,pcVar3,uVar5);
      pcVar3 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)this);
      pcVar3 = pcVar3 + param_2 + param_1;
      pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)this);
      FUN_00416310(pcVar4 + param_5 + param_1,pcVar3,iVar2);
    }
  }
  else {
    pcVar3 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                       ((_String_val<struct_std::_Simple_types<char>_> *)this);
    pcVar3 = pcVar3 + param_2 + param_1;
    pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                       ((_String_val<struct_std::_Simple_types<char>_> *)this);
    FUN_00416310(pcVar4 + param_5 + param_1,pcVar3,iVar2);
    pcVar3 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                       ((_String_val<struct_std::_Simple_types<char>_> *)param_3);
    pcVar3 = pcVar3 + param_4;
    pcVar4 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                       ((_String_val<struct_std::_Simple_types<char>_> *)this);
    char_traits<char>::copy(pcVar4 + param_1,pcVar3,param_5);
  }
  basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
            ((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
              *)this,uVar1);
  return this;
}

