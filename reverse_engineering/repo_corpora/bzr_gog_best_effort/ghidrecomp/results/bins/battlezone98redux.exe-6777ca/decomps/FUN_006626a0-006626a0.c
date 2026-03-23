
basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
FUN_006626a0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
            uint param_2,_String_val<struct_std::_Simple_types<char>_> *param_3,uint param_4,
            uint param_5)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  uint local_10;
  
  if (param_2 <= *(uint *)(param_1 + 0x10)) {
    uVar2 = FUN_004170c0();
    if (param_4 <= uVar2) goto LAB_006626c9;
  }
  FUN_00417440();
LAB_006626c9:
  iVar3 = FUN_004170c0();
  if (iVar3 - param_4 < param_5) {
    param_5 = iVar3 - param_4;
  }
  if (-*(int *)(param_1 + 0x10) - 1U <= param_5) {
    FUN_00417420();
  }
  if (param_5 != 0) {
    uVar2 = *(int *)(param_1 + 0x10) + param_5;
    bVar1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::_Grow
                      (param_1,uVar2,false);
    if (bVar1) {
      iVar3 = *(int *)(param_1 + 0x10) - param_2;
      pcVar4 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)param_1);
      pcVar4 = pcVar4 + param_2;
      pcVar5 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr
                         ((_String_val<struct_std::_Simple_types<char>_> *)param_1);
      FUN_00416310(pcVar5 + param_5 + param_2,pcVar4,iVar3);
      if (param_1 ==
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)param_3) {
        if (param_2 < param_4) {
          local_10 = param_4 + param_5;
        }
        else {
          local_10 = param_4;
        }
        pcVar4 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr
                           ((_String_val<struct_std::_Simple_types<char>_> *)param_1);
        pcVar4 = pcVar4 + local_10;
        pcVar5 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr
                           ((_String_val<struct_std::_Simple_types<char>_> *)param_1);
        FUN_00416310(pcVar5 + param_2,pcVar4,param_5);
      }
      else {
        pcVar4 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr(param_3);
        pcVar4 = pcVar4 + param_4;
        pcVar5 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr
                           ((_String_val<struct_std::_Simple_types<char>_> *)param_1);
        std::char_traits<char>::copy(pcVar5 + param_2,pcVar4,param_5);
      }
      std::basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::
      _Eos((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_> *
           )param_1,uVar2);
    }
  }
  return param_1;
}

