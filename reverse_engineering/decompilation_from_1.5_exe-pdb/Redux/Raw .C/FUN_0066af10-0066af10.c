
basic_iostream<char,struct_std::char_traits<char>_> * __thiscall
FUN_0066af10(basic_iostream<char,struct_std::char_traits<char>_> *param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e949;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_2 != 0) {
    *(undefined ***)param_1 = &PTR_008924b0;
    *(undefined ***)(param_1 + 0x10) = &PTR_008715f8;
    std::basic_ios<char,struct_std::char_traits<char>_>::
    basic_ios<char,struct_std::char_traits<char>_>
              ((basic_ios<char,struct_std::char_traits<char>_> *)(param_1 + 0x78));
    local_8 = 0;
  }
  std::basic_iostream<char,struct_std::char_traits<char>_>::
  basic_iostream<char,struct_std::char_traits<char>_>
            (param_1,(basic_streambuf<char,struct_std::char_traits<char>_> *)(param_1 + 0x18));
  local_8 = 1;
  *(undefined ***)(param_1 + *(int *)(*(int *)param_1 + 4)) =
       std::basic_fstream<char,struct_std::char_traits<char>_>::vftable;
  *(int *)(param_1 + *(int *)(*(int *)param_1 + 4) + -4) = *(int *)(*(int *)param_1 + 4) + -0x78;
  FUN_004230e0(0);
  ExceptionList = local_10;
  return param_1;
}

