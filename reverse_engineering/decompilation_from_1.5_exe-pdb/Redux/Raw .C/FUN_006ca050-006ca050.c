
basic_ostream<char,struct_std::char_traits<char>_> * __thiscall
FUN_006ca050(basic_ostream<char,struct_std::char_traits<char>_> *param_1,uint param_2,int param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852779;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_3 != 0) {
    *(undefined ***)param_1 = &PTR_008963ec;
    std::basic_ios<char,struct_std::char_traits<char>_>::
    basic_ios<char,struct_std::char_traits<char>_>
              ((basic_ios<char,struct_std::char_traits<char>_> *)(param_1 + 0x50));
    local_8 = 0;
  }
  std::basic_ostream<char,struct_std::char_traits<char>_>::
  basic_ostream<char,struct_std::char_traits<char>_>
            (param_1,(basic_streambuf<char,struct_std::char_traits<char>_> *)(param_1 + 4),false);
  local_8 = 1;
  *(undefined ***)(param_1 + *(int *)(*(int *)param_1 + 4)) =
       std::basic_ostringstream<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
       vftable;
  *(int *)(param_1 + *(int *)(*(int *)param_1 + 4) + -4) = *(int *)(*(int *)param_1 + 4) + -0x50;
  FUN_00574560(param_2 | 2);
  ExceptionList = local_10;
  return param_1;
}

