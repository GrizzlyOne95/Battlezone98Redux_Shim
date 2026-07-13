
basic_ostream<char,struct_std::char_traits<char>_> * __thiscall
FUN_0076ef40(basic_ostream<char,struct_std::char_traits<char>_> *param_1,undefined4 param_2,
            uint param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085dda4;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_5 != 0) {
    *(undefined ***)param_1 = &PTR_008966dc;
    std::basic_ios<char,struct_std::char_traits<char>_>::
    basic_ios<char,struct_std::char_traits<char>_>
              ((basic_ios<char,struct_std::char_traits<char>_> *)(param_1 + 0x60));
    local_8 = 0;
  }
  std::basic_ostream<char,struct_std::char_traits<char>_>::
  basic_ostream<char,struct_std::char_traits<char>_>
            (param_1,(basic_streambuf<char,struct_std::char_traits<char>_> *)(param_1 + 4),false);
  local_8 = 1;
  *(undefined ***)(param_1 + *(int *)(*(int *)param_1 + 4)) =
       std::basic_ofstream<char,struct_std::char_traits<char>_>::vftable;
  *(int *)(param_1 + *(int *)(*(int *)param_1 + 4) + -4) = *(int *)(*(int *)param_1 + 4) + -0x60;
  FUN_004230e0(0);
  local_8 = CONCAT31(local_8._1_3_,2);
  iVar1 = FUN_00423150(param_2,param_3 | 2,param_4);
  if (iVar1 == 0) {
    std::basic_ios<char,struct_std::char_traits<char>_>::setstate
              ((basic_ios<char,struct_std::char_traits<char>_> *)
               (param_1 + *(int *)(*(int *)param_1 + 4)),2,false);
  }
  ExceptionList = local_10;
  return param_1;
}

