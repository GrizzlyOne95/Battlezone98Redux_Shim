
basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
FUN_006e45f0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
            uint param_2,char *param_3,uint param_4)

{
  bool bVar1;
  char *pcVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  
  bVar1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::_Inside
                    (param_1,param_3);
  if (bVar1) {
    pcVar2 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr
                       ((_String_val<struct_std::_Simple_types<char>_> *)param_1);
    param_1 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
              FUN_006626a0(param_2,param_1,(int)param_3 - (int)pcVar2,param_4);
  }
  else {
    if (*(uint *)(param_1 + 0x10) < param_2) {
      FUN_00417440();
    }
    if (-*(int *)(param_1 + 0x10) - 1U <= param_4) {
      FUN_00417420();
    }
    if (param_4 != 0) {
      uVar3 = *(int *)(param_1 + 0x10) + param_4;
      bVar1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
              _Grow(param_1,uVar3,false);
      if (bVar1) {
        iVar5 = *(int *)(param_1 + 0x10) - param_2;
        pcVar2 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr
                           ((_String_val<struct_std::_Simple_types<char>_> *)param_1);
        pcVar2 = pcVar2 + param_2;
        pcVar4 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr
                           ((_String_val<struct_std::_Simple_types<char>_> *)param_1);
        FUN_00416310(pcVar4 + param_4 + param_2,pcVar2,iVar5);
        pcVar2 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr
                           ((_String_val<struct_std::_Simple_types<char>_> *)param_1);
        std::char_traits<char>::copy(pcVar2 + param_2,param_3,param_4);
        std::basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
        ::_Eos((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
                *)param_1,uVar3);
      }
    }
  }
  return param_1;
}

