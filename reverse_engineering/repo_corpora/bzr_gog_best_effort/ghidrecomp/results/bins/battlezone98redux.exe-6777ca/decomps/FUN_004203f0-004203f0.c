
basic_iostream<char,struct_std::char_traits<char>_> * __thiscall
FUN_004203f0(basic_iostream<char,struct_std::char_traits<char>_> *param_1,undefined4 param_2,
            undefined4 param_3,int param_4)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008451e9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_4 != 0) {
    *(undefined ***)param_1 = &PTR_008715f8;
    *(undefined **)(param_1 + 0x10) = &DAT_00871600;
    std::basic_ios<char,struct_std::char_traits<char>_>::
    basic_ios<char,struct_std::char_traits<char>_>
              ((basic_ios<char,struct_std::char_traits<char>_> *)(param_1 + 0x68));
    local_8 = 0;
  }
  std::basic_iostream<char,struct_std::char_traits<char>_>::
  basic_iostream<char,struct_std::char_traits<char>_>
            (param_1,(basic_streambuf<char,struct_std::char_traits<char>_> *)(param_1 + 0x18));
  local_8 = 1;
  *(undefined ***)(param_1 + *(int *)(*(int *)param_1 + 4)) =
       std::basic_stringstream<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
       vftable;
  *(int *)(param_1 + *(int *)(*(int *)param_1 + 4) + -4) = *(int *)(*(int *)param_1 + 4) + -0x68;
  FUN_00422f90(param_2,param_3);
  ExceptionList = local_10;
  return param_1;
}

