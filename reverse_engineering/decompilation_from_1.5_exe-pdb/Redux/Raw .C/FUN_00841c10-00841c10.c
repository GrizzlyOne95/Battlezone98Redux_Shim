
basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
FUN_00841c10(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
            uint param_2,int param_3,char *param_4,char *param_5)

{
  uint uVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  
  if (param_4 != param_5) {
    pbVar2 = param_1;
    if (0xf < *(uint *)(param_1 + 0x14)) {
      pbVar2 = *(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
                param_1;
    }
    if (param_3 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = param_3 - param_2;
    }
    if (param_2 != 0) {
      param_2 = param_2 - (int)pbVar2;
    }
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::replace
              (param_1,param_2,uVar1,param_4,(int)param_5 - (int)param_4);
    return param_1;
  }
  pbVar2 = param_1;
  if (0xf < *(uint *)(param_1 + 0x14)) {
    pbVar2 = *(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
              param_1;
  }
  if (param_3 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = param_3 - param_2;
  }
  if (param_2 != 0) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
              (param_1,param_2 - (int)pbVar2,uVar1);
    return param_1;
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
            (param_1,0,uVar1);
  return param_1;
}

